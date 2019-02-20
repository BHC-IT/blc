#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>

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

#ifndef socklen_t
	#define socklen_t int
#endif

#include "blc/errorHandle.hpp"
#include "blc/ForkServer.hpp"

blc::network::ForkServer::ForkServer(unsigned int maxClient, unsigned int port) : Server(maxClient, port, true)
{
}

blc::network::ForkServer::~ForkServer()
{
}

void blc::network::ForkServer::run(void *userData)
{
	pid_t 		child;
	int		status;
	socklen_t	size = sizeof(struct sockaddr);
	struct sockaddr	client;
	int		sock;

	if (this->_handle == nullptr)
		throw blc::error::exception("handle function not specified");
	while (this->_kill == false){
		sock = ::accept(this->getSock(), &client, &size);
		if (sock > 0){
			child = fork();
			if (child == 0){
				this->_handle(sock, client, userData);
				::close(sock);
				exit(0);
			} else {
				::close(sock);
				this->_openedClient += 1;
			}
		}
		if (::waitpid(0, &status, WNOHANG) > 0)
			this->_openedClient -= 1;
		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(5));
	}
}

void blc::network::ForkServer::handle(std::function<void(blc::network::Client &client)> function)
{
	this->_mutex.lock();
	this->_advancedHandler = function;
	this->_mutex.unlock();
}

void blc::network::ForkServer::run()
{
	pid_t 		child;
	int		status;
	socklen_t	size = sizeof(struct sockaddr);
	struct sockaddr	addr;
	int		sock;

	if (this->_advancedHandler == nullptr)
		throw blc::error::exception("handle function not specified");
	while (this->_kill == false){
		sock = ::accept(this->getSock(), &addr, &size);
		if (sock > 0){
			child = fork();
			if (child == 0){
				blc::network::Client client(sock, addr);
				this->_advancedHandler(client);
				::close(sock);
				exit(0);
			} else {
				::close(sock);
				this->_openedClient += 1;
			}
		}
		if (::waitpid(0, &status, WNOHANG) > 0)
			this->_openedClient -= 1;
		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(5));
	}
}