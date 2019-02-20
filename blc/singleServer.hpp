#pragma once

#include "blc/Server.hpp"
#include "blc/Client.hpp"

namespace blc {
	namespace network {
		/// server that will host only one connection. useful for handeling data connection
		class singleServer : public Server {
		public:
			singleServer(unsigned int port);
			~singleServer();
			void run(void *userData); /**< just the implementation, will probably not be used */
			void run(blc::network::Client &client); /**< take a client in charge. In the context, this is the communication client for wich a data socket is needed */ ///< launch the server with a reference to a client
			void run(); /**< take a client in charge. In the context, this is the communication client for wich a data socket is needed */ ///< launch the server with a reference to a client
			void handle(std::function<void(blc::network::Client &client, blc::network::Client &data)> function); /**< the client is the same one given to run(). the data client is created from the accepted socket by run() */ ///< take the function to be called when a client arise
			void handle(std::function<void(blc::network::Client &client)> function); /**< the client is the same one given to run(). the data client is created from the accepted socket by run() */ ///< take the function to be called when a client arise
		private:
			std::function<void(blc::network::Client &client, blc::network::Client &data)>	_advancedHandler;
			std::function<void(blc::network::Client &client)>				_advancedHandler2;
		};
	}
}