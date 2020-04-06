/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifdef __WIN32__
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
#include <iostream>
#include <unistd.h>
#include "blc/errorHandle.hpp"
#include "blc/singleServer.hpp"

#ifdef __WIN32__
	#define socklen_t int
#endif

blc::network::singleServer::singleServer(unsigned int port) : Server(1, port, true) {
	this->listen();
}

blc::network::singleServer::~singleServer() {
}

void blc::network::singleServer::run(void *userData) {
	(void)userData;
}

void blc::network::singleServer::run(const blc::network::Client &client) {
	socklen_t	size = sizeof(struct sockaddr);
	struct sockaddr	addr;
	int		sock;

	if (this->_advancedHandler == nullptr)
		throw blc::error::exception("handle function not specified");
	sock = ::accept(this->getSock(), &addr, &size);
	if (sock > 0) {
		blc::network::Client data(sock, addr);
		this->_advancedHandler(client, data);
	}
}

void blc::network::singleServer::run() {
	socklen_t	size = sizeof(struct sockaddr);
	struct sockaddr	addr;
	int		sock;

	while (this->_kill == false) {
		if (this->_advancedHandler2 == nullptr)
			throw blc::error::exception("handle function not specified");
		sock = ::accept(this->getSock(), &addr, &size);
		if (sock > 0) {
			blc::network::Client client(sock, addr);
			this->_advancedHandler2(client);
		}
	}
}

void blc::network::singleServer::handle(std::function<void(const blc::network::Client &client, const blc::network::Client &data)> function) {
	this->_mutex.lock();
	this->_advancedHandler = function;
	this->_mutex.unlock();
}

void blc::network::singleServer::handle(std::function<void(const blc::network::Client &client)> function) {
	this->_mutex.lock();
	this->_advancedHandler2 = function;
	this->_mutex.unlock();
}
