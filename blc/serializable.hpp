/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <tuple>
#include <string>


namespace blc {
	namespace tools {
		/// class that permeted inherited object to be seen as, and serialize or be constructed from a serialized string.
		class serializable {
		public:
			serializable() = default;
			static std::string				hexToString(const std::string &str);
			///< convert char in a string to hexadecimal

			static std::string				stringToHex(const std::string &str);
			///< convert hexa in a string to char

			virtual std::string				serialize() const = 0;
			///< serialize the object. must be implemented in child

			virtual void					unserialize(const std::string &str) = 0;
			///< unserialize a string and construct the object. must be implemented in child

			static std::tuple<std::string, std::string>	cut(const std::string &str, char cut);
			///< first string is before the cut param, second including and after the cut param

		};

	}  // namespace tools

}  // namespace blc
