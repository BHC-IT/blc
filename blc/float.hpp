#pragma once

#include "serializable.hpp"

namespace blc {
	namespace math {
		class Float : public blc::tools::serializable {
		public:
			Float();
			Float(float i);
			Float(float i, int E);
			Float(const Float &other);
			Float(Float &&other);

			Float	&operator=(float i);
			Float	&operator=(const Float &other);
			Float	&operator=(Float &&other);

			Float	&operator+(float i);
			Float	&operator+(const Float &i);
			Float	&operator-(float i);
			Float	&operator-(const Float &i);
			Float	&operator*(float i);
			Float	&operator*(const Float &i);
			Float	&operator/(float i);
			Float	&operator/(const Float &i);

			bool	operator==(float i);
			bool	operator==(const Float &i);
			bool	operator>(float i);
			bool	operator>(const Float &i);
			bool	operator<(float i);
			bool	operator<(const Float &i);
			bool	operator>=(float i);
			bool	operator>=(const Float &i);
			bool	operator<=(float i);
			bool	operator<=(const Float &i);

			float	operator()() const;

			float	getNb() const;
			void	setNb(float nb);

			int	getE() const;
			void	setE(int E);

			float	calculate() const;
			void	align();
			void	align(int nb);

			std::string	serialize() const;
			void		unserialize(const std::string &str);
		private:
			float	_nb;
			int	_E;
		};
	}
}