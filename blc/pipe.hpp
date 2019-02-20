#pragma once

#include <string>
#include <mutex>
#include "blc/nonCopyable.hpp"
#include "blc/stream.hpp"

namespace blc {
	namespace tools {
		/// virtual abstraction of pipe usable in multiple thread. use a master and slave end. default constructor create a master. note : try as much as possible to close after a thread.join()
		class pipe : public stream {
		public:
			pipe(); ///< construct a default pipe. allocate memorie on heap
			pipe(bool state, bool block = false); ///< construct a pipe were state is the master/slave commuter and block is the blocking/non-blocking interface. allocate memorie on heap
			pipe(const pipe &other); ///< default copy constructor. dont allocate memorie
			pipe(const pipe &other, bool state); ///< copy constructor setting the commutor to state. dont allocate memorie
			pipe(const pipe &other, bool state, bool block); ///< copy constructor setting the commutor to state and the blocking/none-blocking pipe. dont allocate memorie
			~pipe(); ///< destructor. delete _closed if true
			pipe		getSlave() const; ///< return the slave end of the pipe
			pipe		getMaster() const; ///< return the master end of the pipe
			bool		getBlock() const; ///< return the blocking state
			bool		getState() const; ///< return the _state (master/slave)
			std::string	*getIn(); ///< return a pointer on the _in string. hazardous
			std::string	*getOut(); ///< return a pointer on the _out string. hazardous
			std::mutex	*getInMut(); ///< return a pointer on the _in mutex. hazardous
			std::mutex	*getOutMut(); ///< return a pointer on the _in mutex. hazardous
			bool		*getClosed(); ///< return a pointer on the _closed boolean. hazardous
			void		setBlock(bool block); ///< set the blocking state
			bool		switchState(); ///< switch the commuter between slave/master
			std::string	read(); /**< the string used depend on commuter state. */ ///< read the pipe, C read-like.
			void		write(const std::string &str); /**< the string used depend on commuter state. */ ///< write on pipe, C read-like.
			void		close(); /**< destroy all pointer except _closed and set it to true */ ///< close the pipe.
			bool		readable() const; ///< return true if the pipe is readable, false otherwise
			bool		writable() const; ///< return true if the pipe is writable, false otherwise
			bool		isClosed() const; ///< return true if the pipe is close, false otherwise
			pipe		&waitRead(int usec);
			pipe		&waitWrite(int usec); ///< wait for the pipe to be writable. check evry usec, else sleep
			pipe 		&operator=(const pipe &other); ///< wait for the pipe to be readable. check evry usec, else sleep
			pipe 		&operator<<(const std::string &str); ///< write from string to pipe
			pipe 		&operator>>(std::string &str); ///< read from pipe to string
		protected:
			bool		push_on(std::string *target, const std::string &str, std::mutex *locker) const; // push the str on *target and lock/unlock locker. inner working wth security test
			bool		push_out(std::string *target, std::string &str, std::mutex *locker) const; // pull the str from *target and lock/unlock locker. inner working wth security test
			bool		check_block(std::mutex *mutex) const; // proper check if mutex is used
		private:
			std::string	*_in;
			std::mutex	*_inMut;
			std::string	*_out;
			std::mutex	*_outMut;
			bool		_master;
			bool		_block;
			bool		*_closed;
		};
	}
}