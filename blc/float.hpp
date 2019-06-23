#pragma once

#include "serializable.hpp"

namespace blc {
	namespace math {
		class Float : public blc::tools::serializable {
		public:
			Float();
			Float(double i);
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
	}
}