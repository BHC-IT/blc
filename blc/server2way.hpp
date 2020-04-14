/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <map>
#include <thread>
#include "blc/pipe.hpp"
#include "blc/client.hpp"
#include "blc/server.hpp"

namespace blc {
	namespace network {
		/// host a 2 way server accepting a connection from a blc::network::client2way. run child in their dedicated thread
		class server2way : public Server {
		public:
			server2way(unsigned int maxClient, unsigned int port);
			~server2way();
			void				addPipe(tools::pipe pipe);
			///< add a main pipe to communicate between master thread and the server dedicated thread. close the previous one

			tools::pipe			getPipe() const;
			///< return by copy the main pipe

			std::map<int, tools::pipe>	getMap();
			///< return by copy the map of pipe used to communicate with child

			void				addFunc(std::function<void(const Client &, const Client &, const tools::pipe &)> func);
			///< add a function called by child to handle the network communication

			std::thread			start();
			///< launch the main two way server in is own thread

			tools::pipe			retrivePipe(const std::string &str) const;
			tools::pipe			retrivePipe(int id) const;
			bool				isIn(int id) const;
			///< verify the presence of the pipe in the map.

			std::map<int, tools::pipe>	&getChilds();
			///< return the map of pipe.

			void				runThreaded();
			///< hook function member to run the handle function in his own thread

			void				run(void *userData);
			///< function not implmented

		private:
			void				parsePipe(const std::string &str);
			void				finalize2way(const blc::network::Client &client, const blc::network::Client &data);
			void				setUp2way(int sock, struct sockaddr addr, void *data);

			std::function<void(const Client &, const Client &, const tools::pipe &)>	_func;
			blc::tools::pipe								_pipe;
			std::map<int, tools::pipe>							_childPipe;
		};

	}  // namespace network

}  // namespace blc
