/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <string>
#include <functional>

namespace blc {
	namespace tools {
		/// low level encapsulation of an activation code and response logic unit
		template <typename T, typename U>
		class protocolCaps {
		public:
			protocolCaps(const T &code, const std::function<int(U)> &callback);
			///< construct a capsule with the code and callback

			protocolCaps(const protocolCaps<T, U> &other);
			///< copy constructor

			~protocolCaps() = default;

			void			setCode(const T &code);
			///< set the code of he capsule

			void			setCallback(const std::function<int(U)> &callback);
			///< set the callback of the capsule

			T			getCode() const;
			///< return the code of the capsule

			std::function<int(U)>	getCallback() const;
			///< return the callback of the capsule

			bool			check(const T &code) const;
			///< give a code to the capsule and verify the similarity

			int			activate(const U &param) const;
			///< activate the callback function

			int			checkAndActive(const T &code, const U &param) const;
			///< check the given code. If it match the capsule's code, activate the callback.

			protocolCaps		&operator=(const protocolCaps<T, U> &other);
			///< assignation operator

			protocolCaps		&operator=(const std::function<int(U)> &callback);
			///< assignate a callback

			protocolCaps		&operator=(const T &code);
			///< assignate a code

			bool			operator==(const protocolCaps<T, U> &cap);
			///< comparaison operator

			protocolCaps		&operator<<(const T &param);
			///< push a parameter and call activate()

		private:
			protocolCaps() = default;
			T			_code;
			std::function<int(U)>	_callback;
		};

	}  // namespace tools

}  // namespace blc


#include "blc/protocolCaps.tpp"
