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
		}
		template<typename T>
		constexpr static bool has_lifeCycle = blc::tools::impl::has_lifeCycle<T>();

		template <typename Derived>
		class actor {
		public:
			actor(){};
			actor(const actor &other) = delete;
			virtual void	lifeCycle() = 0;
			std::thread	&getThread(){return (this->_thread);};
		protected:
			void start(){
				std::thread thread(&Derived::lifeCycle, dynamic_cast<Derived *>(this));
				this->_thread = std::move(thread);
				this->_thread.detach();
			};
		private:
			std::thread::id	_id;
			std::thread	_thread;
		};
	}
}