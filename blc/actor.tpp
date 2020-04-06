#include "errorHandle.hpp"

blc::tools::actor::actor() {
}

void blc::tools::actor::start() {
	if (&Derived::lifeCycle)
		throw blc::error::exception("the actor '" + typeid(Derived).name() + "'' is illfromed");

	std::thread thread(&Derived::lifeCycle, dynamic_cast<Derived *>(this));
	this->_thread = std::move(thread);
	this->_thread.detach();
};