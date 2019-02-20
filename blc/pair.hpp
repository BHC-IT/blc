#pragma once

#include "blc/serializable.hpp"

namespace blc {
	namespace tools {
		/// pair like std::pair but in the blc fashion
		template <class T, class U>
		class pair {
		public:
			pair() = default; ///< default constructor
			pair(T &&first, U &&second); ///< by value constructor
			pair(const pair<T, U> &other); ///< copy constructor
			~pair() = default;

			pair<T, U>	&operator=(const pair<T, U> &other); ///< assignement operator
			pair<T, U>	operator+(const pair<T, U> &other) const; ///< sum operator
			pair<T, U>	operator-(const pair<T, U> &other) const; ///< minus operator
			pair<T, U>	operator*(const pair<T, U> &other) const; ///< mult operator
			pair<T, U>	operator/(const pair<T, U> &other) const; ///< div operator

			bool		operator==(const pair<T, U> &other) const; ///< comparaison operator
			bool		operator<(const pair<T, U> &other) const; ///< comparaison operator
			bool		operator<=(const pair<T, U> &other) const; ///< comparaison operator
			bool		operator>(const pair<T, U> &other) const; ///< comparaison operator
			bool		operator>=(const pair<T, U> &other) const; ///< comparaison operator
			bool		operator!=(const pair<T, U> &other) const; ///< comparaison operator

			void		swap(pair<T, U> &other); ///< exchange the content of this with the other pair

			T first;
			U second;
		};
		template <class T, class U>
		pair<T, U>		make_pair(T &&first, U &&second); ///< create a pair by value deducing the template
		#include "blc/pair.tpp"
	}
}
