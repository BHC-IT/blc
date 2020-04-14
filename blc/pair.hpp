/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include "blc/serializable.hpp"

namespace blc {
	namespace tools {
		/// pair like std::pair but in the blc fashion
		template <class T, class U>
		class pair {
		public:
			pair() = default;  ///< default constructor
			pair(T &&first, U &&second);  ///< by value constructor
			pair(const pair<T, U> &other);  ///< copy constructor
			~pair() = default;

			pair<T, U>	&operator=(const pair<T, U> &other);  ///< assignement operator
			pair<T, U>	operator+(const pair<T, U> &other) const;  ///< sum operator
			pair<T, U>	operator-(const pair<T, U> &other) const;  ///< minus operator
			pair<T, U>	operator*(const pair<T, U> &other) const;  ///< mult operator
			pair<T, U>	operator/(const pair<T, U> &other) const;  ///< div operator

			bool		operator==(const pair<T, U> &other) const;  ///< comparaison operator
			bool		operator<(const pair<T, U> &other) const;  ///< comparaison operator
			bool		operator<=(const pair<T, U> &other) const;  ///< comparaison operator
			bool		operator>(const pair<T, U> &other) const;  ///< comparaison operator
			bool		operator>=(const pair<T, U> &other) const;  ///< comparaison operator
			bool		operator!=(const pair<T, U> &other) const;  ///< comparaison operator

			void		swap(pair<T, U> &other);  ///< exchange the content of this with the other pair

			T first;
			U second;
		};
		template <class T, class U>
		pair<T, U>		make_pair(T &&first, U &&second);  ///< create a pair by value deducing the template

		#include "blc/pair.tpp"

	}  // namespace tools

}  // namespace blc
