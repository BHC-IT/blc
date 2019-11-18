#pragma once

#include <functional>
#include <thread>
#include <mutex>
#include "blc/errorHandle.hpp"

template <typename T>
using resolver = std::function<void(T)>;

using rejecter = std::function<void(blc::error::exception)>;

namespace blc {
	namespace tools {
		template <typename T>
		class promise {
		public:
			promise() = delete;
			promise(const promise &other) = delete;
			promise(promise &&other);
			// promise(std::function<void(promise &)> func);
			promise(std::function<void(std::function<void(T)>, std::function<void(blc::error::exception)>)> func);
			~promise();

			promise &then(std::function<void(T)> func);
			promise &catcher(std::function<void(blc::error::exception)> func);

			void resolve(T value);
			void reject(blc::error::exception code);
		private:
			void engage();

			T 											_value;
			std::thread										_thread;
			std::function<void(std::function<void(T)>, std::function<void(blc::error::exception)>)>	_func;
			std::function<void(T)>									_res;
			std::function<void(blc::error::exception)>						_rej;
			std::mutex										_resStop;
			std::mutex										_resErr;
		};
	}
}

template <typename T>
blc::tools::promise<T>::promise(std::function<void(std::function<void(T)>, std::function<void(blc::error::exception)>)> func)
{
	this->_func = func;
	this->_resStop.lock();
	this->_resErr.lock();
	this->_thread = std::thread(&blc::tools::promise<T>::engage, this);
}

template <typename T>
blc::tools::promise<T>::~promise()
{
	this->_thread.join();
}

template <typename T>
void blc::tools::promise<T>::resolve(T value)
{
	this->_value = value;
	this->_resStop.lock();
	this->_res(this->_value);
}

template <typename T>
void blc::tools::promise<T>::reject(blc::error::exception code)
{
	this->_rej(code);
}

template <typename T>
blc::tools::promise<T> &blc::tools::promise<T>::then(std::function<void(T)> func)
{
	this->_res = func;
	this->_resStop.unlock();
	return (*this);
}

template <typename T>
blc::tools::promise<T> &blc::tools::promise<T>::catcher(std::function<void(blc::error::exception)> func)
{
	this->_rej = func;
	this->_resErr.unlock();
	return (*this);
}

template <typename T>
void blc::tools::promise<T>::engage()
{
	using namespace std::placeholders;
	std::function<void(T)> res = std::bind(&blc::tools::promise<T>::resolve, this, _1);
	std::function<void(blc::error::exception)> rej = std::bind(&blc::tools::promise<T>::reject, this, _1);
	this->_func(res, rej);
}
