#pragma once

namespace blc {
	namespace math {
		/// vector of 2 dimension used for mathematical work
		template <typename T>
		class vecteur2 {
		public:
			vecteur2() = default; ///< default constructor
			vecteur2(T &&xP, T &&yP); ///< by value constructor
			vecteur2(const vecteur2<T> &other); ///< copy constructor
			~vecteur2() = default;

			vecteur2	&operator=(const vecteur2<T> &other); ///< assignement operator
			vecteur2	operator+(const vecteur2<T> &other) const; ///< sum operator
			vecteur2	operator-(const vecteur2<T> &other) const; ///< minus operator
			vecteur2	operator*(const vecteur2<T> &other) const; ///< mult operator
			vecteur2	operator/(const vecteur2<T> &other) const; ///< div operator

			bool		operator==(const vecteur2<T> &other) const; ///< comparaison operator
			bool		operator!=(const vecteur2<T> &other) const; ///< comparaison operator
			bool		operator<(const vecteur2<T> &other) const; ///< comparaison operator
			bool		operator<=(const vecteur2<T> &other) const; ///< comparaison operator
			bool		operator>(const vecteur2<T> &other) const; ///< comparaison operator
			bool		operator>=(const vecteur2<T> &other) const; ///< comparaison operator

			T		sum() const; ///< sum the value
			T		minus() const; ///< minus the value
			T		minusInv() const; ///< minus the value in reversed order
			T		prod() const; ///< multiplie the value
			T		div() const; ///< div the value
			T		divInv() const; ///< div the value in reversed order

			T		avg() const; ///< calculate the avrage value
			T		norme() const; ///< calculate the norme of the vector
			T		norme(const vecteur2<T> &other) const; ///< calculate the norme between the 2 vector
			T		min() const; ///< return the lowest value
			T		max() const; ///< calculate the maximum value
			//vecteur2<T>	getDistance() const

			void		minimize(); ///< PGCD of the value
			void		swap(); ///< swap the two value
			void		swap(vecteur2<T> &other); ///< swap the two vector

			T x;
			T y;
		};
		#include "blc/vecteur2.tpp"
	}
}