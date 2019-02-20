#pragma once

#include "blc/Server.hpp"
#include "blc/Client.hpp"

namespace blc {
	namespace network {
		/// the server track the number of opened client but dont open a thread by its own. a server forking and calling the handle function in child process
		class ForkServer : public Server {
		public:
			ForkServer(unsigned int maxClient, unsigned int port);
			~ForkServer();
			void run(void *userData); /**the server will fork at each new client connecting */ /**<a handler function need to be specified before */ ///< start the server
			void handle(std::function<void(blc::network::Client &client)> function); /**< the client is the same one given to run(). the data client is created from the accepted socket by run() */ ///< take the function to be called when a client arise
			void run(); /**< take a client in charge. In the context, this is the communication client for wich a data socket is needed */ ///< launch the server with a reference to a client
		private:
			std::function<void(blc::network::Client &client)>				_advancedHandler;
		};
	}
}