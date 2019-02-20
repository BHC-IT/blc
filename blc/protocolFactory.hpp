#pragma once

#include <vector>
#include "blc/protocolCaps.hpp"

namespace blc {
	namespace tools {
		/// instanciate multiple blc::tools::protocolCaps to map out a full and functionnal protocole
		template <typename T, typename U>
		class protocolFactory {
		public:
			protocolFactory() = default; ///< default empty constructor
			~protocolFactory() = default; ///< default destructor
			protocolFactory(const protocolFactory<T, U> &other); ///< copy constructor
			void													add(const protocolCaps<T, U> &cap); ///< add a premade capsule
			void													add(const T &code, const std::function<int(U)> &callback); ///< create and add a new capsule
			bool													erase(const T &code); ///< erase a capsule from its code
			bool													erase(const protocolCaps<T, U> &cap); ///< find and erase a copy of this capsule
			bool													erase(typename std::vector<protocolCaps<T, U>>::iterator it); ///< find and erase the capsule corresponding to the iterator
			typename std::vector<protocolCaps<T, U>>::iterator		begin(); ///< return an iterator pointing on the first capsule
			typename std::vector<protocolCaps<T, U>>::iterator		end(); ///< return an iterator pointing after the last capsule
			const protocolCaps<T, U>								&find(const T &code) const; ///< return the capsule with the corresponding code
			const protocolCaps<T, U>								&find(const protocolCaps<T, U> &cap) const; ///< return the capsule corresponding to the parameter
			const protocolCaps<T, U>								&find(typename std::vector<protocolCaps<T, U>>::iterator it) const; ///< return the capsule corresponding to the iterator
			bool													replace(const T &code, const std::function<int(U)> &callback); ///< change the callback of the capsule corresponding to the code
			bool													replace(const protocolCaps<T, U> &cap, const std::function<int(U)> &callback); ///< replace the callback of the capsule
			int														activate(const T &code, const U &param) const; ///< active the callback of the capsule corresponding to the code.
			void													clear(); ///< clear all the capsule
			unsigned int											size() const; ///< return the number of capsule
			bool													empty() const; ///< return true if there is no capsule, false otherwise
			protocolFactory											&operator=(const protocolFactory &other); ///< assignement operator
			const protocolCaps<T, U>								&operator[](int i) const; ///< parsing operator
			protocolFactory											operator+(const protocolCaps<T, U> &cap){this->add(cap); return(*this);};
		private:
			typename std::vector<protocolCaps<T, U>> _caps;
		};
	}
}

#include "blc/protocolFactory.tpp"