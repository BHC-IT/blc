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
	#include <sys/socket.h>
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

#include "blc/socket.hpp"
#include "blc/errorHandle.hpp"

blc::network::Socket::Socket() : _address(""), _port(0), _block(false), _opened(false) {
}

blc::network::Socket::Socket(std::string address, int port, bool block, int mode, int type) :	_socket(0),
												_address(address),
												_port(port),
												_block(block),
												_mode(mode),
												_type(type),
												_opened(false) {
}

blc::network::Socket::~Socket() {
	if (this->_opened)
		::close(this->_socket);
}

void blc::network::Socket::setAddress(const std::string &str) {
	this->_address = str;
}

void blc::network::Socket::setPort(int port) {
	this->_port = port;
}

void blc::network::Socket::setBlock(bool block) {
	int ret;

	this->_block = block;
	#ifdef __linux__
		ret = fcntl(this->_socket, F_SETFD, this->_mode | (SOCK_NONBLOCK * (1 - this->_block)));
	#elif __WIN32
		u_long mode = !block;
		ret = ioctlsocket(this->_socket, FIONBIO, &mode);
	#else
		ret = fcntl(this->_socket, F_SETFD, this->_mode | (SOCK_NONBLOCK * (1 - this->_block)));
	#endif
	if (ret == -1)
		throw blc::error::exception(strerror(errno));
}

void blc::network::Socket::setMode(int mode) {
	this->_mode = mode;
}

void blc::network::Socket::setType(int type) {
	this->_type = type;
}

std::string blc::network::Socket::getAddress() const {
	return (this->_address);
}

int blc::network::Socket::getPort() const {
	return (this->_port);
}

bool blc::network::Socket::getBlock() const {
	return (this->_block);
}

int blc::network::Socket::getMode() const {
	return (this->_mode);
}

int blc::network::Socket::getType() const {
	return (this->_type);
}

void blc::network::Socket::open() {
	struct sockaddr_in addr;

	if (this->_address == "" || this->_port == 0)
		throw blc::error::exception("non set connection");
	else if (this->_opened == true)
		return;
	this->_socket = socket(this->_type, this->_mode | (SOCK_NONBLOCK * (1 - this->_block)), 0);
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
	while (this->writable() == false) continue;
	this->_opened = true;
}

void blc::network::Socket::close() {
	if (this->_opened == true)
		::close(this->_socket);
	this->_opened = false;
	this->_socket = 0;
}

bool blc::network::Socket::isOpen() const {
	return (this->_opened);
}

bool blc::network::Socket::isClosed() const {
	return (!this->_opened);
}

void blc::network::Socket::write(const std::string &request) const {
	if (this->_opened == false)
		return;
	if (::send(this->_socket, request.c_str(), request.size(), MSG_NOSIGNAL) == -1)
		throw blc::error::exception(strerror(errno));
}

std::string blc::network::Socket::read() const {
	std::string	str;
	char		tmp;
	int		ret;

	if (this->_opened == false)
		throw blc::error::exception("not opened");
	while ((ret = recv(this->_socket, &tmp, 1, 0)) > 0) {
		if (tmp == '\n' || tmp == '\0')
			break;
		str += tmp;
	}
	return (str);
}

std::string blc::network::Socket::read(int n) const {
	std::string	str;
	char		tmp[n];
	int		ret;

	if (this->_opened == false)
		throw blc::error::exception("not opened");
	int size = recv(this->_socket, &tmp, n, 0);
	return (std::string(tmp, tmp + size));
}

bool blc::network::Socket::readable() const {
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
		const_cast<blc::network::Socket *>(this)->close();
		return (false);
	}
	return (true);
}

bool blc::network::Socket::writable() const {
	fd_set fds;
	struct timeval timeout = {0, 0};

	FD_ZERO(&fds);
	FD_SET(this->_socket, &fds);
	if (select(this->_socket + 1, 0, &fds, 0, &timeout) <= 0)
		return (false);
	return (true);
}

bool blc::network::Socket::waitRead(unsigned int usec) const {
	fd_set fds;
	struct timeval timeout = {0, reinterpret_cast<unsigned int>(usec)};

	FD_ZERO(&fds);
	FD_SET(this->_socket, &fds);
	if (select(this->_socket + 1, &fds, 0, 0, &timeout) <= 0)
		return (false);
	return (true);
}

bool blc::network::Socket::waitWrite(unsigned int usec) const {
	fd_set fds;
	struct timeval timeout = {0, reinterpret_cast<unsigned int>(usec)};

	FD_ZERO(&fds);
	FD_SET(this->_socket, &fds);
	if (select(this->_socket + 1, 0, &fds, 0, &timeout) <= 0)
		return (false);
	return (true);
}

blc::network::Socket &blc::network::Socket::operator<<(const std::string &str) {
	this->write(str);
	return (*this);
}

blc::network::Socket &blc::network::Socket::operator>>(std::string &str) {
	str = this->read();
	return (*this);
}

std::ostream &operator<<(std::ostream &ostream, blc::network::Socket &socket) {
	ostream << socket.read();
	return (ostream);
}
