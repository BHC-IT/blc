/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#include "blc/stream.hpp"
#include "blc/errorHandle.hpp"
#include "blc/stringOp.hpp"

namespace blc {
	namespace Process {
		class spawn : public blc::stream {
		public:
			spawn() = delete;
			explicit spawn(std::string command) : _command(command), _opened(true), _alive(true) {
				this->run();
			}

			spawn(std::string command, std::vector<std::string> args) : _command(command), _opened(true), _alive(true) {
				this->_command += std::string(" ") + blc::tools::merge(args);
				this->run();
			}

			~spawn() { if (this->_alive) this->kill(); }

			spawn(const spawn &other) = delete;
			spawn(spawn &&other) = default;

			spawn &operator=(const spawn &other) = delete;
			spawn &operator=(spawn &&other) = default;

			void		write(const std::string &str) const;
			std::string	read() const;
			std::string	read(int n) const;
			std::string	readError() const;
			std::string	readError(int n) const;
			void		close();
			void		kill();

			bool		readable() const;
			bool		writable() const;
			bool		isClosed() const;
			bool		isAlive() const;

			std::string	getCommand() const;
			pid_t		getChildPid() const;

		private:
			void run();

			std::string	_command;
			pid_t		_c_pid;
			int		_pipe_to[2];
			int		_pipe_from[2];
			int		_pipe_error[2];
			bool 		_opened;
			bool		_alive;
		};


		inline void spawn::run() {
			if (::pipe(this->_pipe_to) == -1)
				throw blc::error::exception("Error creating pipe");

			if (::pipe(this->_pipe_from) == -1)
				throw blc::error::exception("Error creating pipe");

			if (::pipe(this->_pipe_error) == -1)
				throw blc::error::exception("Error creating pipe");

			pid_t c_pid = ::fork();

			if (c_pid == 0) {
				// in child

				if (::dup2(this->_pipe_to[0], 0) == -1)
					perror("dup");
				if (::dup2(this->_pipe_from[1], 1) == -1)
					perror("dup");
				if (::dup2(this->_pipe_error[1], 2) == -1)
					perror("dup");

				::close(this->_pipe_to[0]);
				::close(this->_pipe_to[1]);
				::close(this->_pipe_from[0]);
				::close(this->_pipe_from[1]);
				::close(this->_pipe_error[0]);
				::close(this->_pipe_error[1]);


				std::vector<std::string> strings {blc::tools::cut(this->_command, ' ')};
				std::vector<char *> cstrings;
				cstrings.reserve(strings.size());

				for (unsigned int i = 0; i < strings.size(); i++)
					cstrings.push_back(const_cast<char *>(strings[i].c_str()));
				cstrings.push_back(static_cast<char *>(nullptr));

				if (execvpe(cstrings[0], &cstrings[0], {}) == -1)
					perror("");

				exit(0);
			} else {
				// in parent
				::close(this->_pipe_to[0]);
				::close(this->_pipe_from[1]);
				::close(this->_pipe_error[1]);

				int status;
				this->_c_pid = c_pid;
				return;
			}
		}

		inline void spawn::write(const std::string &str) const {
			::write(this->_pipe_to[1], str.c_str(), str.size());
		}

		inline std::string spawn::read() const {
			std::string	str;
			char		tmp;
			int		ret;

			if (this->_opened == false)
				throw blc::error::exception("not opened");
			while ((ret = ::read(this->_pipe_from[0], &tmp, 1)) > 0) {
				if (tmp == '\n' || tmp == '\0')
					break;
				str += tmp;
			}
			return (str);
		}

		inline std::string spawn::read(int n) const {
			char	tmp[n];
			int	size;

			if (this->_opened == false)
				throw blc::error::exception("not opened");
			size = ::read(this->_pipe_from[0], &tmp, n);
			if (size == -1)
				throw new blc::error::exception("read error");
			return (std::string(tmp, tmp + size));
		}

		inline std::string spawn::readError() const {
			std::string	str;
			char		tmp;
			int		ret;

			if (this->_opened == false)
				throw blc::error::exception("not opened");
			while ((ret = ::read(this->_pipe_error[0], &tmp, 1)) > 0) {
				if (tmp == '\n' || tmp == '\0')
					break;
				str += tmp;
			}
			return (str);
		}

		inline std::string spawn::readError(int n) const {
			char	tmp[n];
			int	size;

			if (this->_opened == false)
				throw blc::error::exception("not opened");
			size = ::read(this->_pipe_error[0], &tmp, n);
			return (std::string(tmp, tmp + size));
		}

		inline void spawn::close() {
			::close(this->_pipe_from[0]);
			::close(this->_pipe_to[1]);
			::close(this->_pipe_error[1]);
			this->_opened = false;
		}

		inline void spawn::kill() {
			if (!this->isClosed())
				this->close();

			if (::kill(this->_c_pid, SIGKILL) == -1) {
				if (errno != ESRCH) {
					throw blc::error::exception("not killed");
				}
			}
			this->_alive = false;
			this->_c_pid = 0;
		}

		inline bool spawn::readable() const {
			return true;
		}

		inline bool spawn::writable() const {
			return true;
		}

		inline bool spawn::isClosed() const {
			return !this->_opened;
		}


		inline bool spawn::isAlive() const {
			return this->_alive;
		}


		inline std::string spawn::getCommand() const {
			return this->_command;
		}

		inline pid_t spawn::getChildPid() const {
			return this->_c_pid;
		}


	}  // namespace Process
}  // namespace blc
