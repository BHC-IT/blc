/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <cstdlib>
#include <iostream>

#ifdef __WIN32
	#include <winsock2.h>
	#pragma comment(lib, "ws2_32.lib")
#elif __WIN64
	#include <winsock2.h>
	#pragma comment(lib, "ws2_32.lib")
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

#include "blc/bindTest.hpp"

bool blc::network::isPortFree(int port) {
	struct ::sockaddr_in addr;
		int sock = socket(PF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		if (::bind(sock, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1) {
			close(sock);
			return (false);
		}
		close(sock);
		return (true);
}

int blc::network::findFreePort() {
	int port = 1000 * ((std::rand() % 7) + 3) + 100 * ((std::rand() % 9) + 1) + 10 * ((std::rand() % 9) + 1) + 1 * ((std::rand() % 9) + 1);

	while (isPortFree(port) == false) {
		port = 1000 * ((std::rand() % 7) + 3) + 100 * ((std::rand() % 9) + 1) + 10 * ((std::rand() % 9) + 1) + 1 * ((std::rand() % 9) + 1);
	}
	return (port);
}
