/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#ifdef __WIN32__
	#include <winsock2.h>
#elif __linux__
	#include <netdb.h>
#else
	#include <netdb.h>
#endif
#include "blc/socket.hpp"

namespace blc {
	namespace network {
		/// a class that can be built with the information provided by the accept function or the data passed to the handle function.
		class Client : public Socket {
		public:
			Client(int socket, struct sockaddr);
			///< construct the client object from an already open socket.
			/**< be aware not to use the same socket in multiple client as this may disrupt the logic of the application */

		private:
			Client() = delete;
			void open();
			///< the socket is already opened in the context.
		};

	}  // namespace network

}  // namespace blc
