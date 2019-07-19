#pragma once

#include <functional>
#include <thread>
#include "blc/errorHandle.hpp"

namespace blc {
	namespace tools {
		template <typename T>
		class promise {
		public:
			promise() = delete;
			promise(const promise &other) = delete;
			promise(promise &&other);
			promise(std::function<void(std::function<void(T)>, std::function<void(blc::error::exception)>)>);

			promise &then(std::function<void(T)> func);
			promise &catcher(std::function<void(blc::error::exception)> func);

			class resolve : public std::function<void(T)>{
			};
			class reject : public std::function<void(blc::error::exception)>{
			};

		private:
			void engage();
			void resolve(T value);
			void reject(blc::error::exception code);

			T value;
			std::thread thread;
		};
	}
}

template <typename T>
blc::tools::promise<T>::promise(std::function<void(std::function<void(T)>, std::function<void(blc::error::exception)>)>)
{
}