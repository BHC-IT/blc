#pragma once

#include <string>
#include <exception>
#include <ctime>

#ifndef assertError
	#define assertError(x) std::string(__FILE__) + ": " + __PRETTY_FUNCTION__ + ": " + std::to_string(__LINE__) + ": " + x
#endif

namespace blc {
	namespace error {
		/// class to throw error.
		class exception : public std::exception {
		public:
			exception(std::string msg);
			exception(std::string msg, std::string file, std::string func = "ND", int line = -1, std::time_t time = -1); ///< construct the exception with the error message
			~exception(){}; ///< chain throw
			virtual const char		*what() const throw() {return (this->_msg.c_str());}; ///< return the error message
			virtual const std::string	where() const throw() {return (this->_file);}; ///< return the error message
			virtual const std::string	whom() const throw() {return (this->_func);}; ///< return the error message
			virtual const int		line() const throw() {return (this->_line);}; ///< return the error message
			virtual const std::time_t	when() const throw() {return (this->_time);};
		private:
			std::string	_msg; ///< error message
			std::string	_file;
			std::string	_func;
			int		_line;
			std::time_t	_time;
		};

		// inline std::string assertError(std::string error)
		// {
		// 	std::string ret = std::string("blc> ") + __FILE__ + ": " + __PRETTY_FUNCTION__ + ": " + std::to_string(__LINE__) + ": " + error;

		// 	return (ret);
		// }

		inline exception expInfo(std::string str)
		{
			exception exp(str, __FILE__, __PRETTY_FUNCTION__, __LINE__, std::time(NULL));

			return (exp);
		}
	}
}
