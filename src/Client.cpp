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
#include "blc/Client.hpp"

blc::network::Client::Client(int socket, struct sockaddr addr) : Socket()
{
	 struct sockaddr_in data;

	data = *((struct sockaddr_in*)(&addr));
	this->_socket = socket;
	this->_address = inet_ntoa(data.sin_addr);
	this->_port = ntohs(data.sin_port);
	this->_opened = true;
}

void blc::network::Client::open()
{
	return;
}