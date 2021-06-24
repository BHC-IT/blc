/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <map>
#include <optional>
#include <variant>

#include "blc/blc.hpp"

namespace blc {
	namespace Process {


		template <class ...Types>
		class env : blc::tools::serializable {
		public:
			env() = default;
			~env() = default;

			env(const env &other) = default;
			env(env &&other) = default;

			env						&operator=(const env &other) = default;
			env						&operator=(env &&other) = default;


			explicit env(const std::map<std::string, std::variant<Types...>> &src_map);
			explicit env(const std::vector<std::string> &c_env);

			static const env				&getFromRegister();
			static env					&getFromRegister_unsafe();

			const std::variant<Types...>			&operator[](const std::string &k) const;
			std::variant<Types...>				&operator[](const std::string &k);

			std::optional<std::variant<Types...>>		find(const std::variant<Types...> &value) const;

			env						&operator+=(const std::pair<std::string, std::variant<Types...>> &value);
			env						&operator-=(const std::string &k);

			bool						emplace(const std::string &k, const std::variant<Types...> &value);
			bool						emplace(const std::pair<std::string, std::variant<Types...>> &arg);

			void						clear();

			unsigned int					size() const;

			void						pullRegister();
			void						_pushRegister_unsafe();

			template<typename T>
			T			begin();

			template<typename T>
			T			begin() const;

			template<typename T>
			T			end();

			template<typename T>
			T			end() const;


			std::string serialize() const;
			void unserialize(const std::string &str);

		private:
			std::map<std::string, std::variant<Types...>>	 	_values;
			static std::map<std::string, std::variant<Types...>> 	_values_register;
		};

		template <class ...Types>
		inline std::map<std::string, std::variant<Types...>> 	env<Types...>::_values_register{};

		template <class ...Types>
		inline env<Types...>::env(const std::map<std::string, std::variant<Types...>> &src_map) : _values(src_map) {}

		template <class ...Types>
		inline env<Types...>::env(const std::vector<std::string> &c_env) {
			for (auto s : c_env) {
				auto c = blc::tools::cut(s, '=');
				*this += std::make_pair(c[0], c.size() >= 2 ? c[1] : "");
			}
		}


		template <class ...Types>
		inline const env<Types...> &env<Types...>::getFromRegister() {
			static env<Types...> e(env::_values_register);

			if (env::_values_register != e.size())
				e._values = e._values_register;

			return e;
		}

		template <class ...Types>
		inline env<Types...> &env<Types...>::getFromRegister_unsafe() {
			static env<Types...> e;

			e._values = e._values_register;

			return e;
		}

		template <class ...Types>
		inline const std::variant<Types...> &env<Types...>::operator[](const std::string &k) const {
			return this->_values.at(k);
		}

		template <class ...Types>
		inline std::variant<Types...> &env<Types...>::operator[](const std::string &k) {
			return this->_values[k];
		}

		template <class ...Types>
		inline std::optional<std::variant<Types...>> env<Types...>::find(const std::variant<Types...> &value) const {
			auto i = this->_values.find(value);
			if (i == this->_values.end()) {
				return {};
			}
			return i->second;
		}

		template <class ...Types>
		inline env<Types...> &env<Types...>::operator+=(const std::pair<std::string, std::variant<Types...>> &value) {
			this->_values.emplace(value);

			return *this;
		}

		template <class ...Types>
		inline env<Types...> &env<Types...>::operator-=(const std::string &k) {
			this->_values.erase(k);

			return *this;
		}

		template <class ...Types>
		inline bool env<Types...>::emplace(const std::string &k, const std::variant<Types...> &value) {
			return this->_values.emplace(k, value).second;
		}

		template <class ...Types>
		inline bool env<Types...>::emplace(const std::pair<std::string, std::variant<Types...>> &arg) {
			return this->_values.emplace(arg).second;
		}

		template <class ...Types>
		inline void env<Types...>::clear() {
			this->_values.clear();
		}


		template <class ...Types>
		inline unsigned int env<Types...>::size() const {
			return this->_values.size();
		}

		template <class ...Types>
		inline void env<Types...>::pullRegister() {
			this->_values = this->_values_register;
		}

		template <class ...Types>
		inline void env<Types...>::_pushRegister_unsafe() {
			this->_values_register = this->_values;
		}

		template <class ...Types>
		template <typename T>
		inline T env<Types...>::begin() {
			return this->_values.begin();
		}

		template <class ...Types>
		template <typename T>
		inline T env<Types...>::begin() const {
			return this->_values.begin();
		}

		template <class ...Types>
		template <typename T>
		inline T env<Types...>::end() {
			return this->_values.end();
		}

		template <class ...Types>
		template <typename T>
		inline T env<Types...>::end() const {
			return this->_values.end();
		}


		template <class ...Types>
		inline std::string env<Types...>::serialize() const {
			return "";
		}

		template <class ...Types>
		inline void env<Types...>::unserialize(const std::string &str) {
		}
	}  // namespace Process
}  // namespace blc
