/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <string>
#include <functional>
#include <mutex>
#include "blc/nonCopyable.hpp"

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
#ifndef SOCK_NONBLOCK
	#ifndef O_NONBLOCK
		#define SOCK_NONBLOCK 0
	#else
		#define SOCK_NONBLOCK O_NONBLOCK
	#endif
#endif
#ifndef MSG_NOSIGNAL
	#ifdef SO_NOSIGPIPE
		#define MSG_NOSIGNAL SO_NOSIGPIPE
		#define CEPH_USE_SO_NOSIGPIPE
	# else
		#define MSG_NOSIGNAL 0
	#endif
#endif

#ifndef MSG_DONTWAIT
	#define MSG_DONTWAIT 0
#endif

#ifndef EINPROGRESS
	#ifdef WSAEINPROGRESS
		#define EINPROGRESS WSAEINPROGRESS
	#else
		#error no in progress error
	#endif
#endif

#ifndef SOCKET
	#define SOCKET int
#endif

namespace blc {
	namespace network {
		/// server object. the run function must be implemented in the child.
		class Server : virtual public symbole::nonCopyable {
		public:
			Server(unsigned int maxClient, unsigned int port, bool block = true, int mode = SOCK_STREAM, int type = AF_INET);
			///< set server information needed to run

			~Server();
			void		setMaxClient(unsigned int maxClient);
			///< change the number of maximum client opened. may need a restart

			unsigned int	getMaxClient() const;
			///< return the number of maximum client.

			unsigned int	getOpenedClient() const;
			///< reurn the number of client beeing alive.

			int		getSock() const;
			///< return the socket used to listen for client.

			int		getPort() const;
			///< return the port use.

			bool		getBlock() const;
			///< return the type of socket (blocking/non-blocking)

			void		listen();
			///< start to listen.

			void		handle(std::function<void(int, struct sockaddr, int)> handle);
			///< spécifie the function to be called when a client open communication.
			///< the parameters are : the client socket, the client socket, and a pointer too a user data (may be a nullptr)

			virtual void	run(void *userData) = 0;
			///< start the server. need to be implemented by a child.
			///< the method to handle client, call the handle function, stop, wait, kill and track open clients are up to this funcion

			void		stop();
			///< stop the server and prevent him to handle new client.

			void		resume();
			///< resume the server.

			void		wait(unsigned int wait);
			///< wait for specified µsec and dont open new client.

			void		kill();
			///< kill the server.

			int		accept(struct sockaddr *client);
			void		close();

		protected:
			unsigned int						_openedClient;
			///< track the number of opened client

			struct ::sockaddr_in					_addr;
			///< data about the server connection

			unsigned int						_port;
			///< port being usedby the server

			bool							_stop;
			///< use to stop the server

			bool							_kill;
			///< use to kill the server

			unsigned int						_wait;
			///< use to make the server wait

			std::mutex						_mutex;
			///< use to dialogate thread-safely with the server

			std::function<void(int, struct sockaddr, int)>		_handle;
			///< handle function beeing called by the server when a client connect.

			SOCKET							_sock;
			///< the file descriptor of the socket


		private:
			Server();
			///< the server cant be default created

			unsigned int						_maxClient;
			///< the maximum number of client that can connect at the same time

			bool							_block;
			///< state of the server (blocking/non-blocking)

			int							_mode;
			int							_type;
		};

	}  // namespace network

}  // namespace blc
