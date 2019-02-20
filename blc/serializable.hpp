#pragma once

#include <string>


namespace blc {
	namespace tools {
		/// class that permeted inherited object to be seen as, and serialize or be constructed from a serialized string.
		class serializable {
		public:
			serializable() = default;
			static std::string	hexToString(const std::string &str); ///< convert char in a string to hexadecimal
			static std::string	stringToHex(const std::string &str); ///< convert hexa in a string to char
			virtual std::string	serialize() const = 0; ///< serialize the object. must be implemented in child
			virtual void		unserialize(const std::string &str) = 0; ///< unserialize a string and construct the object. must be implemented in child
			static std::string	cut(std::string &str, char cut);
			static std::string	cut(std::string &&str, char cut);
		};
	}
}