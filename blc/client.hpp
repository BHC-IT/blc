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
			Client(int socket, struct sockaddr); /**< be aware not to use the same socket in multiple client as this may disrupt the logic of the application */ /// construct the client object from an already open socket.
		private:
			Client() = delete;
			void open(); ///< the socket is already opened in the context.
		};
	}
}