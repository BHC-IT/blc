/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#pragma once

#include <type_traits>
#include <string>
#include <thread>
#include "blc/errorHandle.hpp"

#ifndef void_t
	#define void_t __void_t
#endif

namespace blc {
	namespace tools {

		namespace impl {
			template<typename T, typename = std::void_t<decltype(T::lifeCycle)>>
			constexpr std::true_type has_lifeCycle() noexcept { return std::true_type{}; }
			template<typename T>
			constexpr std::false_type has_lifeCycle() noexcept { return std::false_type{}; }
		}  // namespace impl

		template<typename T>
		constexpr static bool has_lifeCycle = blc::tools::impl::has_lifeCycle<T>();

		template <typename Derived>
		class actor {
		 public:
			actor() {}
			actor(const actor &other) = delete;
			virtual void	lifeCycle() = 0;
			std::thread	&getThread() {return (this->_thread);}

		 protected:
			void start() {
				std::thread thread(&Derived::lifeCycle, dynamic_cast<Derived *>(this));
				this->_thread = std::move(thread);
				this->_thread.detach();
			}

		 private:
			std::thread::id	_id;
			std::thread	_thread;
		};

	}  // namespace tools

}  // namespace blc
