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
#include <thread>
#include <cstdlib>
#include <ctime>
#include "blc/server2way.hpp"
#include "blc/client.hpp"
#include "blc/singleServer.hpp"
#include "blc/errorHandle.hpp"
#include "blc/bindTest.hpp"

#ifdef __WIN32__
	#define socklen_t int
#endif

blc::network::server2way::server2way(unsigned int maxClient, unsigned int port) : Server(maxClient, port)
{
	this->handle([this](int sock, struct sockaddr addr, void *data){
		int				port = *(int *)data;
		blc::network::Client		client(sock, addr);

		port = findFreePort();
		blc::network::singleServer	serv(port);

		client << std::to_string(port) + "\n";
		serv.handle([this](blc::network::Client &client, blc::network::Client &data){
			int randPipe = std::rand();
			blc::tools::pipe pipe;

			this->_childPipe.emplace(randPipe, pipe.getSlave());
			this->_pipe.write(std::to_string(randPipe) + "\n");
			this->_func(client, data, pipe);
			pipe.close();
			this->_childPipe.erase(randPipe);
		});
		serv.run(client);
		this->_openedClient--;
	});
}

blc::network::server2way::~server2way()
{
	for (auto it = this->_childPipe.begin(); it != this->_childPipe.end(); it++){
		it->second.close();
	}
}


void blc::network::server2way::addPipe(tools::pipe pipe)
{
	this->_pipe.close();
	this->_pipe = pipe;
}

blc::tools::pipe blc::network::server2way::getPipe() const
{
	return (this->_pipe);
}

std::map<int, blc::tools::pipe> blc::network::server2way::getMap()
{
	return (this->_childPipe);
}


void blc::network::server2way::addFunc(std::function<void(blc::network::Client &, blc::network::Client &, blc::tools::pipe &)> func)
{
	this->_func = func;
}

void blc::network::server2way::parsePipe(const std::string &str)
{
	if (str == "kill")
		this->kill();
}

std::thread blc::network::server2way::start()
{
	return (std::move(std::thread(&blc::network::server2way::runThreaded, this)));
}

blc::tools::pipe blc::network::server2way::retrivePipe(const std::string &str) const
{
	int id = std::stoi(str);

	return (blc::tools::pipe(this->_childPipe.at(id)));
}

blc::tools::pipe blc::network::server2way::retrivePipe(int id) const
{
	return (blc::tools::pipe(this->_childPipe.at(id)));
}

std::map<int, blc::tools::pipe> &blc::network::server2way::getChilds()
{
	return (this->_childPipe);
}

bool blc::network::server2way::isIn(int id) const
{
	if (this->_childPipe.find(id) == this->_childPipe.end())
		return (false);
	return (true);
}

void blc::network::server2way::launchThread(int &port, int sock, struct sockaddr client)
{
	try {
		std::thread thread(this->_handle, sock, client, &port);
		thread.detach();
	} catch (const blc::error::exception &e) {
		if (std::string(e.what()) == std::string("Address already in use")){
			port = 1000 * ((std::rand() % 10) + 1) + 100 * ((std::rand() % 10) + 1) + 10 * ((std::rand() % 10) + 1) + 1 * ((std::rand() % 10) + 1);
			this->launchThread(port, sock, client);
		} else {
			throw blc::error::exception(std::string("s2w: ") + e.what());
		}
	}
}

void blc::network::server2way::runThreaded()
{
	socklen_t	size = sizeof(struct sockaddr);
	struct sockaddr	client;
	int		sock;
	int		port = this->getPort() + 100;

	std::srand(std::time(nullptr));
	if (this->_handle == nullptr)
		throw blc::error::exception("handle function not specified");
	while (this->_kill == false){
		if (this->_pipe.readable())
			this->parsePipe(this->_pipe.read());
		sock = ::accept(this->getSock(), &client, (socklen_t *)&size);
		if (sock > 0){
			this->_openedClient++;
			std::thread thread(this->_handle, sock, client, &port);
			thread.detach();
			// this->launchThread(port, sock, client);
			port++;
		}
		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(5));
	}
	::close(this->getSock());
}

void blc::network::server2way::run(void *userData)
{
	(void)userData;
}