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

blc::network::singleServer::singleServer(unsigned int port) : Server(1, port, true)
{
	this->listen();
}

blc::network::singleServer::~singleServer()
{
}

void blc::network::singleServer::run(void *userData)
{
	(void)userData;
}

void blc::network::singleServer::run(blc::network::Client &client)
{
	socklen_t	size = sizeof(struct sockaddr);
	struct sockaddr	addr;
	int		sock;

	if (this->_advancedHandler == nullptr)
		throw blc::error::exception("handle function not specified");
	sock = ::accept(this->getSock(), &addr, &size);
	if (sock > 0){
		blc::network::Client data(sock, addr);
		this->_advancedHandler(client, data);
	}
}

void blc::network::singleServer::run()
{
	socklen_t	size = sizeof(struct sockaddr);
	struct sockaddr	addr;
	int		sock;

	while (this->_kill == false){
		if (this->_advancedHandler2 == nullptr)
			throw blc::error::exception("handle function not specified");
		sock = ::accept(this->getSock(), &addr, &size);
		if (sock > 0){
			blc::network::Client client(sock, addr);
			this->_advancedHandler2(client);
		}
	}
}

void blc::network::singleServer::handle(std::function<void(blc::network::Client &client, blc::network::Client &data)> function)
{
	this->_mutex.lock();
	this->_advancedHandler = function;
	this->_mutex.unlock();
}

void blc::network::singleServer::handle(std::function<void(blc::network::Client &client)> function)
{
	this->_mutex.lock();
	this->_advancedHandler2 = function;
	this->_mutex.unlock();
}
