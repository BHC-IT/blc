#pragma once

#include <iostream>

namespace blc {
	/// stream abstraction to construct stream in the blc fashion
	class stream {
	public:
		stream() = default;
		~stream() = default;
		virtual void		write(const std::string &str) const = 0;
		virtual std::string	read() const = 0;
		virtual std::string	read(int n) const = 0;
		virtual void		close() = 0;
		virtual bool		readable() const = 0;
		virtual bool		writable() const = 0;
		virtual bool		isClosed() const = 0;
		stream			&operator<<(const std::string &str);
		stream			&operator<<(char str[]);
		stream			&operator<<(int nb);
		stream			&operator<<(double nb);
		stream			&operator<<(char c);
		stream			&operator>>(std::string &str);
		stream			&operator>>(int &nb);
		stream			&operator>>(double &nb);
	private:
	};
}

//std::ostream &operator<<(std::ostream &ostream, blc::stream &socket);
