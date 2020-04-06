/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include "serializable.hpp"

namespace blc {
	namespace math {
		class Float : public blc::tools::serializable {
		public:
			Float();
			explicit Float(double i);
			Float(double i, int E);
			Float(const Float &other);
			Float(Float &&other);

			Float	&operator=(double i);
			Float	&operator=(const Float &other);
			Float	&operator=(Float &&other);

			Float	&operator+(double i);
			Float	&operator+(const Float &i);
			Float	&operator-(double i);
			Float	&operator-(const Float &i);
			Float	&operator*(double i);
			Float	&operator*(const Float &i);
			Float	&operator/(double i);
			Float	&operator/(const Float &i);

			bool	operator==(double i);
			bool	operator==(const Float &i);
			bool	operator>(double i);
			bool	operator>(const Float &i);
			bool	operator<(double i);
			bool	operator<(const Float &i);
			bool	operator>=(double i);
			bool	operator>=(const Float &i);
			bool	operator<=(double i);
			bool	operator<=(const Float &i);

			double	operator()() const;

			double	getNb() const;
			void	setNb(double nb);

			int	getE() const;
			void	setE(int E);

			double	calculate() const;
			void	align();
			void	align(int nb);

			std::string	serialize() const;
			void		unserialize(const std::string &str);

		private:
			double	_nb;
			int	_E;
		};

	}  // namespace math

}  // namespace blc
