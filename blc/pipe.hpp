/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <string>
#include <mutex>
#include "blc/nonCopyable.hpp"
#include "blc/stream.hpp"

namespace blc {
	namespace tools {
		/// virtual abstraction of pipe usable in multiple thread. use a master and slave end. default constructor create a master.
		/** note : try as much as possible to close after a thread.join() */
		class pipe : public stream {
		public:
			pipe();
			///< construct a default pipe. allocate memorie on heap

			explicit pipe(bool state, bool block = false);
			///< construct a pipe were state is the master/slave commuter and block is the blocking/non-blocking interface. allocate memorie on heap

			pipe(const pipe &other);
			///< default copy constructor. dont allocate memorie

			pipe(const pipe &other, bool state);
			///< copy constructor setting the commutor to state. dont allocate memorie

			pipe(const pipe &other, bool state, bool block);
			///< copy constructor setting the commutor to state and the blocking/none-blocking pipe. dont allocate memorie

			~pipe();
			///< destructor. delete _closed if true

			pipe		getSlave() const;
			///< return the slave end of the pipe

			pipe		getMaster() const;
			///< return the master end of the pipe

			bool		getBlock() const;
			///< return the blocking state

			bool		getState() const;
			///< return the _state (master/slave)

			std::string	*getIn();
			///< return a pointer on the _in string. hazardous

			std::string	*getOut();
			///< return a pointer on the _out string. hazardous

			std::mutex	*getInMut();
			///< return a pointer on the _in mutex. hazardous

			std::mutex	*getOutMut();
			///< return a pointer on the _in mutex. hazardous

			bool		*getClosed();
			///< return a pointer on the _closed boolean. hazardous

			void		setBlock(bool block);
			///< set the blocking state

			bool		switchState();
			///< switch the commuter between slave/master

			void		write(const std::string &str) const; /**< the string used depend on commuter state. */
			///< write on pipe, C read-like.

			std::string	read() const; /**< the string used depend on commuter state. */
			///< read the pipe, C read-like.

			std::string	read(int n) const; /**< the string used depend on commuter state. */
			///< read the pipe, C read-like.

			void		close(); /**< destroy all pointer except _closed and set it to true */
			///< close the pipe.

			bool		readable() const;
			///< return true if the pipe is readable, false otherwise

			bool		writable() const;
			///< return true if the pipe is writable, false otherwise

			bool		isClosed() const;
			///< return true if the pipe is close, false otherwise

			void 		waitRead(int usec) const;
			///< wait for the pipe to be readable.

			void 		waitWrite(int usec) const;
			///< wait for the pipe to be writable.

			pipe 		&operator=(const pipe &other);
			///< assignement operator

			pipe 		&operator<<(const std::string &str);
			///< write from string to pipe

			pipe 		&operator>>(std::string &str);
			///< read from pipe to string

		protected:
			bool		push_on(std::string *target, const std::string &str, std::mutex *locker) const;
			// push the str on *target and lock/unlock locker. inner working wth security test

			bool		push_out(std::string *target, std::string *str, std::mutex *locker) const;
			// pull the str from *target and lock/unlock locker. inner working wth security test

			bool		check_block(std::mutex *mutex) const;
			// proper check if mutex is used

		private:
			std::string	*_in;
			std::mutex	*_inMut;
			std::string	*_out;
			std::mutex	*_outMut;
			bool		_master;
			bool		_block;
			bool		*_closed;
		};

	}  // namespace tools

}  // namespace blc
