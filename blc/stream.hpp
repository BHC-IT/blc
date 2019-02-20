#pragma once

#include <iostream>

namespace blc {
	/// stream abstraction to construct stream in the blc fashion
	class stream {
	public:
		stream() = default;
		~stream() = default;
		//virtual void		write(const std::string &str) = 0;
		//virtual std::string	read() = 0;
		virtual void		close() = 0;
		virtual bool		readable() const = 0;
		virtual bool		writable() const = 0;
		virtual bool		isClosed() const = 0;
	private:
	};
}

//std::ostream &operator<<(std::ostream &ostream, blc::stream &socket);
