/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include "blc/server.hpp"
#include "blc/client.hpp"

namespace blc {
	namespace network {
		/// server that will host only one connection. useful for handeling data connection
		class singleServer : public Server {
		public:
			explicit singleServer(unsigned int port);
			~singleServer();
			void run(void *userData);
			/**< just the implementation, will probably not be used */

			void run(const blc::network::Client &client);
			///< launch the server with a reference to a client
			/**< take a client in charge. In the context, this is the communication client for wich a data socket is needed */

			void run();
			///< launch the server with a reference to a client
			/**< take a client in charge. In the context, this is the communication client for wich a data socket is needed */

			void handle(std::function<void(const blc::network::Client &client, const blc::network::Client &data)> function);
			///< take the function to be called when a client arise
			/**< the client is the same one given to run(). the data client is created from the accepted socket by run() */

			void handle(std::function<void(const blc::network::Client &client)> function);
			///< take the function to be called when a client arise
			/**< the client is the same one given to run(). the data client is created from the accepted socket by run() */

		private:
			std::function<void(const blc::network::Client &client, const blc::network::Client &data)>	_advancedHandler;
			std::function<void(const blc::network::Client &client)>						_advancedHandler2;
		};

	}  // namespace network

}  // namespace blc
