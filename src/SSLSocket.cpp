/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>

#include <openssl/ssl.h>
#include <openssl/err.h>

#ifdef __WIN32
	#include <winsock2.h>
#elif __WIN64
	#include <winsock2.h>
#elif __linux__
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <netdb.h>
#else
	#include <sys/SSLSocket.h>
	#include <sys/select.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <netdb.h>
#endif
#ifndef SOCK_NONBLOCK
	#ifndef O_NONBLOCK
		#define SOCK_NONBLOCK 0
	#else
		#define SOCK_NONBLOCK O_NONBLOCK
	#endif
#endif
#ifndef MSG_NOSIGNAL
	#ifdef SO_NOSIGPIPE
		#define MSG_NOSIGNAL SO_NOSIGPIPE
		#define CEPH_USE_SO_NOSIGPIPE
	# else
		#define MSG_NOSIGNAL 0
	#endif
#endif

#ifndef MSG_DONTWAIT
	#define MSG_DONTWAIT 0
#endif

#ifndef EINPROGRESS
	#ifdef WSAEINPROGRESS
		#define EINPROGRESS WSAEINPROGRESS
	#else
		#error no in progress error
	#endif
#endif

#ifndef INADDR_NONE
	#define INADDR_NONE  -1
#endif

#include "blc/SSLSocket.hpp"
#include "blc/errorHandle.hpp"


static void log_ssl() {
	int err;
	while (err = ERR_get_error()) {
		char *str = ERR_error_string(err, 0);
		if (!str)
			return;
		std::cerr << str << std::endl;
	}
}

SSL_CTX *blc::network::SSLSocket::_ctx{0};
SSL_CTX *blc::network::SSLSocket::_ctx_client{0};

blc::network::SSLSocket::SSLSocket() : _address(""), _port(0), _block(false), _opened(false) {}


blc::network::SSLSocket::SSLSocket(std::string address, int port, bool block, int mode, int type) :	_socket(0),
													_address(address),
													_port(port),
													_block(block),
													_mode(mode),
													_type(type),
													_opened(false) {}

blc::network::SSLSocket::SSLSocket(int socket, struct sockaddr_in addr) : _block(false) {
	this->_socket = socket;
	this->_opened = true;
	this->_ssl = SSL_new(this->_ctx);

	if (!this->_ssl) {
		log_ssl();
		throw blc::error::exception("Error creating SSL");
	}

	SSL_set_fd(this->_ssl, socket);

	this->_address = inet_ntoa(addr.sin_addr);
	this->_port = ntohs(addr.sin_port);

	int ret = SSL_accept(this->_ssl);
	if (ret <= 0) {
		log_ssl();
		throw blc::error::exception("handshake failed");
	}
}

blc::network::SSLSocket::~SSLSocket() {
	if (this->_opened)
		::close(this->_socket);
}

void blc::network::SSLSocket::setAddress(const std::string &str) {
	this->_address = str;
}

void blc::network::SSLSocket::setPort(int port) {
	this->_port = port;
}

void blc::network::SSLSocket::setBlock(bool block) {
	int ret;

	this->_block = block;
	#ifdef __linux__
		ret = fcntl(this->_socket, F_SETFL, this->_mode | (SOCK_NONBLOCK * (1 - this->_block)));
	#elif __WIN32
		u_long mode = !block;
		ret = ioctlSSLSocket(this->_socket, FIONBIO, &mode);
	#else
		ret = fcntl(this->_socket, F_SETFL, this->_mode | (SOCK_NONBLOCK * (1 - this->_block)));
	#endif
	if (ret == -1)
		throw blc::error::exception(strerror(errno));
}

void blc::network::SSLSocket::setMode(int mode) {
	this->_mode = mode;
}

void blc::network::SSLSocket::setType(int type) {
	this->_type = type;
}

std::string blc::network::SSLSocket::getAddress() const {
	return (this->_address);
}

int blc::network::SSLSocket::getPort() const {
	return (this->_port);
}

bool blc::network::SSLSocket::getBlock() const {
	return (this->_block);
}

int blc::network::SSLSocket::getMode() const {
	return (this->_mode);
}

int blc::network::SSLSocket::getType() const {
	return (this->_type);
}

void blc::network::SSLSocket::open() {
	struct sockaddr_in addr;

	if (this->_address == "" || this->_port == 0)
		throw blc::error::exception("non set connection");
	else if (this->_opened == true)
		return;
	this->_socket = ::socket(this->_type, this->_mode | (SOCK_NONBLOCK * (1 - this->_block)), 0);
	if (this->_socket == -1)
		throw blc::error::exception(assertError(strerror(errno)));
	#ifdef __WIN32
		u_long mode = !this->_block;
		ioctlsocket(this->_socket, FIONBIO, &mode);
	#endif
	addr.sin_family = AF_INET;
	addr.sin_port = htons(this->_port);
	addr.sin_addr.s_addr = inet_addr(this->_address.c_str());
	if(inet_addr(this->_address.c_str()) == INADDR_NONE) {
		struct hostent *he;
		struct in_addr **addr_list;
		if ( (he = gethostbyname( this->_address.c_str() ) ) == NULL)
			throw blc::error::exception(assertError(strerror(errno)));
		addr_list = (struct in_addr **) he->h_addr_list;
		for(int i = 0; addr_list[i] != NULL; i++) {
			addr.sin_addr = *addr_list[i];
			break;
		}
	}
	if (connect(this->_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0 && errno != EINPROGRESS)
		throw blc::error::exception(assertError(strerror(errno)));
	this->_opened = true;
	const SSL_METHOD *meth = SSLv23_client_method();
	SSL_CTX *ctx = SSL_CTX_new (meth);
	this->_ssl = SSL_new (ctx);
	if (!this->_ssl) {
		log_ssl();
		throw blc::error::exception("Error creating SSL");
	}
	SSL_get_fd(this->_ssl);
	SSL_set_fd(this->_ssl, this->_socket);
	if (SSL_connect(this->_ssl) <= 0) {
		log_ssl();
		throw blc::error::exception("Error creating SSL connection");
	}
	while (this->writable() == false) continue;
}

void blc::network::SSLSocket::close() {
	if (this->_opened == true)
		::close(this->_socket);
	SSL_shutdown(this->_ssl);
        SSL_free(this->_ssl);
	this->_opened = false;
	this->_socket = 0;
}

bool blc::network::SSLSocket::isOpen() const {
	return (this->_opened);
}

bool blc::network::SSLSocket::isClosed() const {
	return (!this->_opened);
}

void blc::network::SSLSocket::write(const std::string &request) const {
	if (this->_opened == false)
		throw blc::error::exception("not opened");
	if (::SSL_write(this->_ssl, request.c_str(), request.size()) == -1)
		throw blc::error::exception(strerror(errno));
}

std::string blc::network::SSLSocket::read() const {
	std::string	str;
	char		tmp;
	int		ret;

	if (this->_opened == false)
		throw blc::error::exception("not opened");
	while ((ret = SSL_read(this->_ssl, &tmp, 1)) > 0) {
		if (ret == -1)
			throw new blc::error::exception("read error");
		if (tmp == '\n' || tmp == '\0')
			break;
		str += tmp;
		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1));
	}
	return (str);
}

std::string blc::network::SSLSocket::read(int n) const {
	char		tmp[n];
	int		ret;

	if (this->_opened == false)
		throw blc::error::exception("not opened");
	int size = SSL_read(this->_ssl, tmp, n);
	if (size == -1)
		throw new blc::error::exception("read error");
	return (std::string(tmp, tmp + size));
}

bool blc::network::SSLSocket::readable() const {
	fd_set		fds;
	struct timeval	timeout = {0, 0};
	char		tmp;

	if (this->_opened == false)
		return (false);
	FD_ZERO(&fds);
	FD_SET(this->_socket, &fds);
	if (select(this->_socket + 1, &fds, 0, 0, &timeout) <= 0)
		return (false);
	if (::recv(this->_socket, &tmp, 1, MSG_PEEK | MSG_DONTWAIT) == 0) {
		const_cast<blc::network::SSLSocket *>(this)->close();
		return (false);
	}
	return (true);
}

bool blc::network::SSLSocket::writable() const {
	fd_set fds;
	struct timeval timeout = {0, 0};

	if (this->_opened == false)
		return (false);
	FD_ZERO(&fds);
	FD_SET(this->_socket, &fds);
	if (select(this->_socket + 1, 0, &fds, 0, &timeout) <= 0)
		return (false);
	return (true);
}

bool blc::network::SSLSocket::waitRead(unsigned int usec) const {
	fd_set fds;
	#ifdef __WIN32
		struct timeval timeout = {0, static_cast<int32_t>(usec)};
	#elif __APPLE__
		struct timeval timeout = {0, static_cast<int32_t>(usec)};
	#else
		struct timeval timeout = {0, reinterpret_cast<unsigned int>(usec)};
	#endif

	FD_ZERO(&fds);
	FD_SET(this->_socket, &fds);
	if (select(this->_socket + 1, &fds, 0, 0, &timeout) <= 0)
		return (false);
	return (true);
}

bool blc::network::SSLSocket::waitWrite(unsigned int usec) const {
	fd_set fds;
	#ifdef __WIN32
		struct timeval timeout = {0, static_cast<int32_t>(usec)};
	#elif __APPLE__
		struct timeval timeout = {0, static_cast<int32_t>(usec)};
	#else
		struct timeval timeout = {0, reinterpret_cast<unsigned int>(usec)};
	#endif

	FD_ZERO(&fds);
	FD_SET(this->_socket, &fds);
	if (select(this->_socket + 1, 0, &fds, 0, &timeout) <= 0)
		return (false);
	return (true);
}

const blc::network::SSLSocket &blc::network::SSLSocket::operator<<(const std::string &str) const {
	this->write(str);
	return (*this);
}

const blc::network::SSLSocket &blc::network::SSLSocket::operator>>(std::string &str) const {
	str = this->read();
	return (*this);
}

std::ostream &operator<<(std::ostream &ostream, blc::network::SSLSocket &SSLSocket) {
	ostream << SSLSocket.read();
	return (ostream);
}


void blc::network::SSLSocket::setUpSSl(std::string pubKey, std::string privKey) {
	blc::network::SSLSocket sock;

	SSL_load_error_strings();
	SSL_library_init();
	SSLeay_add_ssl_algorithms();
	OpenSSL_add_ssl_algorithms();

	const SSL_METHOD *method;
	const SSL_METHOD *client_method;

	method = SSLv23_server_method();
	client_method = SSLv23_client_method();

	sock._ctx = SSL_CTX_new(method);
	if (!sock._ctx) {
		log_ssl();
		throw blc::error::exception("Unable to create SSL context");
	}

	sock._ctx_client = SSL_CTX_new(client_method);
	if (!sock._ctx_client) {
		log_ssl();
		throw blc::error::exception("Unable to create SSL context");
	}

	SSL_CTX_set_ecdh_auto(sock._ctx, 1);

    /* Set the key and cert */
	if (SSL_CTX_use_certificate_file(sock._ctx, pubKey.c_str(), SSL_FILETYPE_PEM) <= 0) {
		log_ssl();
		throw blc::error::exception("Unable to read pub key");
	}

	if (SSL_CTX_use_PrivateKey_file(sock._ctx, privKey.c_str(), SSL_FILETYPE_PEM) <= 0 ) {
		log_ssl();
		throw blc::error::exception("Unable to read priv key");
	}
}

void blc::network::SSLSocket::cleanSSl() {
	blc::network::SSLSocket sock;
}
