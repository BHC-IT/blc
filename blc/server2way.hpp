#pragma once

#include <map>
#include <thread>
#include "blc/pipe.hpp"
#include "blc/client.hpp"
#include "blc/server.hpp"

namespace blc {
	namespace network {
		/// host a 2 way server accepting a connection from a blc::network::client2way. run child in their dedicated thread
		class server2way : public Server{
		public:
			server2way(unsigned int maxClient, unsigned int port);
			~server2way();
			void				addPipe(tools::pipe pipe); ///< add a main pipe to communicate between master thread and the server dedicated thread. close the previous one
			tools::pipe			getPipe() const; ///< return by copy the main pipe
			std::map<int, tools::pipe>	getMap(); ///< return by copy the map of pipe used to communicate with child
			void				addFunc(std::function<void(Client &, Client &, tools::pipe &)> func); ///< add a function called by child to handle the network communication
			std::thread			start();
			tools::pipe			retrivePipe(const std::string &str) const;
			tools::pipe			retrivePipe(int id) const;
			bool				isIn(int id) const; ///< verify the presence of the pipe in the map.
			std::map<int, tools::pipe>	&getChilds(); ///< return the map of pipe.
			void				runThreaded(); ///< hook function member to run the server in his own thread
			void				run(void *userData); ///< function not implmented
		private:
			void				launchThread(int &port, int sock, struct sockaddr client);
			void				parsePipe(const std::string &str);
			void				finalize2way(blc::network::Client &client, blc::network::Client &data);
			void				setUp2way(int sock, struct sockaddr addr, void *data);
			std::function<void(Client &, Client &, tools::pipe &)>	_func;
			blc::tools::pipe					_pipe;
			std::map<int, tools::pipe>				_childPipe;
		};
	}
}