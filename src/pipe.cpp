/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <thread>
#include <iostream>

#include "blc/pipe.hpp"

blc::tools::pipe::pipe() : _closed(new bool(false)) {
	this->_in = new std::string;
	this->_out = new std::string;
	this->_inMut = new std::mutex;
	this->_outMut = new std::mutex;
	this->_master = true;
	this->_block = false;
}

blc::tools::pipe::pipe(bool state, bool block) : _closed(new bool(false)) {
	this->_in = new std::string;
	this->_out = new std::string;
	this->_inMut = new std::mutex;
	this->_outMut = new std::mutex;
	this->_master = state;
	this->_block = block;
}

blc::tools::pipe::pipe(const pipe &other) {
	this->_in = const_cast<blc::tools::pipe &>(other).getIn();
	this->_out = const_cast<blc::tools::pipe &>(other).getOut();
	this->_inMut = const_cast<blc::tools::pipe &>(other).getInMut();
	this->_outMut = const_cast<blc::tools::pipe &>(other).getOutMut();
	this->_master = const_cast<blc::tools::pipe &>(other).getState();
	this->_block = const_cast<blc::tools::pipe &>(other).getBlock();
	this->_closed = const_cast<blc::tools::pipe &>(other).getClosed();
}

blc::tools::pipe::pipe(const pipe &other, bool state) {
	this->_in = const_cast<blc::tools::pipe &>(other).getIn();
	this->_out = const_cast<blc::tools::pipe &>(other).getOut();
	this->_inMut = const_cast<blc::tools::pipe &>(other).getInMut();
	this->_outMut = const_cast<blc::tools::pipe &>(other).getOutMut();
	this->_block = const_cast<blc::tools::pipe &>(other).getBlock();
	this->_closed = const_cast<blc::tools::pipe &>(other).getClosed();
	this->_master = state;
}

blc::tools::pipe::pipe(const pipe &other, bool state, bool block) {
	this->_in = const_cast<blc::tools::pipe &>(other).getIn();
	this->_out = const_cast<blc::tools::pipe &>(other).getOut();
	this->_inMut = const_cast<blc::tools::pipe &>(other).getInMut();
	this->_outMut = const_cast<blc::tools::pipe &>(other).getOutMut();
	this->_closed = const_cast<blc::tools::pipe &>(other).getClosed();
	this->_block = block;
	this->_master = state;
}


blc::tools::pipe::~pipe() {
}

blc::tools::pipe blc::tools::pipe::getSlave() const {
	return (blc::tools::pipe(*this, false));
}

blc::tools::pipe blc::tools::pipe::getMaster() const {
	return (blc::tools::pipe(*this, true));
}

bool blc::tools::pipe::getBlock() const {
	return (this->_block);
}

bool blc::tools::pipe::getState() const {
	return (this->_master);
}

std::string *blc::tools::pipe::getIn() {
	return (this->_in);
}

std::string *blc::tools::pipe::getOut() {
	return (this->_out);
}

std::mutex *blc::tools::pipe::getInMut() {
	return (this->_inMut);
}

std::mutex *blc::tools::pipe::getOutMut() {
	return (this->_outMut);
}

std::shared_ptr<bool> blc::tools::pipe::getClosed() {
	return (this->_closed);
}


void blc::tools::pipe::setBlock(bool block) {
	this->_block = block;
}

bool blc::tools::pipe::switchState() {
	this->_master = !this->_master;
	return (this->_master);
}

void blc::tools::pipe::write(const std::string &str) const {
	if (*(this->_closed))
		return;
	if (this->_block == true)
		this->waitWrite(1000);
	if (this->_master)
		this->push_on(this->_in, str, this->_inMut);
	else
		this->push_on(this->_out, str, this->_outMut);
}

std::string blc::tools::pipe::read() const {
	std::string str("");

	if (this->_block == true)
		this->waitRead(1000);
	if (this->_master)
		this->push_out(this->_out, &str, this->_outMut);
	else
		this->push_out(this->_in, &str, this->_inMut);
	return (str);
}

std::string blc::tools::pipe::read(int n) const {
	return (this->read());
}

void blc::tools::pipe::close() {
	this->_outMut->lock();
	this->_inMut->lock();
	*(this->_closed) = true;
	this->_outMut->unlock();
	this->_inMut->unlock();
	delete this->_in;
	delete this->_out;
	delete this->_inMut;
	delete this->_outMut;
	this->_in = nullptr;
	this->_out = nullptr;
	this->_outMut = nullptr;
	this->_inMut = nullptr;
}

bool blc::tools::pipe::readable() const {
	if (this->_closed == nullptr || this->_in == nullptr || this->_out == nullptr)
		return (false);
	if (*(this->_closed))
		return (false);
	if (this->_master) {
		if (this->_out->size() > 0)
			return (true);
	} else {
		if (this->_in->size() > 0)
			return (true);
	}
	return (false);
}

bool blc::tools::pipe::writable() const {
	if (this->_closed == nullptr || this->_in == nullptr || this->_out == nullptr)
		return (false);
	if (*(this->_closed))
		return (false);
	if (this->_master) {
		if (this->_in->size() == 0)
			return (true);
	} else {
		if (this->_out->size() == 0)
			return (true);
	}
	return (false);
}

bool blc::tools::pipe::isClosed() const {
	if (this->_closed == nullptr)
		return (false);
	return (*(this->_closed));
}

void blc::tools::pipe::waitWrite(int usec) const {
	if (this->isClosed())
		return;
	while (this->writable() == false) {
		std::this_thread::sleep_for(std::chrono::microseconds(usec));
	}
}

void blc::tools::pipe::waitRead(int usec) const {
	if (this->isClosed())
		return;
	while (this->readable() == false) {
		std::this_thread::sleep_for(std::chrono::microseconds(usec));
	}
}

blc::tools::pipe &blc::tools::pipe::operator=(const pipe &other) {
	this->_in = const_cast<blc::tools::pipe &>(other).getIn();
	this->_out = const_cast<blc::tools::pipe &>(other).getOut();
	this->_inMut = const_cast<blc::tools::pipe &>(other).getInMut();
	this->_outMut = const_cast<blc::tools::pipe &>(other).getOutMut();
	this->_master = const_cast<blc::tools::pipe &>(other).getState();
	this->_block = const_cast<blc::tools::pipe &>(other).getBlock();
	this->_closed = const_cast<blc::tools::pipe &>(other).getClosed();
	return (*this);
}

blc::tools::pipe &blc::tools::pipe::operator<<(const std::string &str) {
	this->write(str);
	return (*this);
}

blc::tools::pipe &blc::tools::pipe::operator>>(std::string &str) {
	str = this->read();
	return (*this);
}

bool blc::tools::pipe::push_on(std::string *target, const std::string &str, std::mutex *locker) const {
	if (target == nullptr || locker == nullptr)
		return (false);
	if (this->isClosed())
		return (false);
	if (this->_block == false) {
		if (locker->try_lock() == false)
			return (false);
	} else {
		locker->lock();
	}
	*target += str;
	*target += "\0";
	locker->unlock();
	return (true);
}


bool blc::tools::pipe::push_out(std::string *target, std::string *str, std::mutex *locker) const {
	unsigned int i;

	if (target == nullptr || locker == nullptr)
		return (false);
	if (this->isClosed())
		return (false);
	if (this->_block == false) {
		if (locker->try_lock() == false)
			return (false);
	} else {
		locker->lock();
	}
	(*str).clear();
	for (i = 0; target->size() > i; i++) {
		if ((*target)[i] == '\n')
			break;
		(*str).resize((*str).size() + 1);
		(*str)[i] = (*target)[i];
	}
	target->erase(0, i + 1);
	locker->unlock();
	return (true);
}

bool blc::tools::pipe::check_block(std::mutex *mutex) const {
	if (mutex->try_lock() == false)
		return (true);
	mutex->unlock();
	return (false);
}
