/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

template <typename T, typename U>
blc::tools::protocolFactory<T, U>::protocolFactory(const protocolFactory<T, U> &other) {
	for (int i = 0; i != other.size(); i++) {
		this->_caps[i] = other[i];
	}
}

template <typename T, typename U>
void blc::tools::protocolFactory<T, U>::add(const blc::tools::protocolCaps<T, U> &cap) {
	this->_caps.push_back(cap);
}

template <typename T, typename U>
void blc::tools::protocolFactory<T, U>::add(const T &code, const std::function<int(U)> &callback) {
	this->_caps.emplace_back(blc::tools::protocolCaps<T, U>(code, callback));
}

template <typename T, typename U>
bool blc::tools::protocolFactory<T, U>::erase(const T &code) {
	for (auto it = this->_caps.begin(); it != this->_caps.end(); it++) {
		if ((*it).getCode() == code) {
			this->_caps.erase(it);
			return (true);
		}
	}
	return (false);
}

template <typename T, typename U>
bool blc::tools::protocolFactory<T, U>::erase(const blc::tools::protocolCaps<T, U> &cap) {
	for (auto it = this->_caps.begin(); it != this->_caps.end(); it++) {
		if (*it == cap) {
			this->_caps.erase(it);
			return (true);
		}
	}
	return (false);
}

template <typename T, typename U>
bool blc::tools::protocolFactory<T, U>::erase(typename std::vector<blc::tools::protocolCaps<T, U>>::iterator it) {
	try {
		this->_caps.erase(it);
		return (true);
	} catch (const std::exception &e) {
		return (false);
	}
}

template <typename T, typename U>
typename std::vector<blc::tools::protocolCaps<T, U>>::iterator blc::tools::protocolFactory<T, U>::begin() {
	return (this->_caps.begin());
}

template <typename T, typename U>
typename std::vector<blc::tools::protocolCaps<T, U>>::iterator blc::tools::protocolFactory<T, U>::end() {
	return (this->_caps.end());
}

template <typename T, typename U>
const blc::tools::protocolCaps<T, U> &blc::tools::protocolFactory<T, U>::find(const T &code) const {
	for (auto it = this->_caps.begin(); it != this->_caps.end(); it++) {
		if ((*it).getCode() == code)
			return (*it);
	}
	return (*this->_caps.end());
}

template <typename T, typename U>
const blc::tools::protocolCaps<T, U> &blc::tools::protocolFactory<T, U>::find(const blc::tools::protocolCaps<T, U> &cap) const {
	for (auto it = this->_caps.begin(); it != this->_caps.end(); it++) {
		if (*it == cap)
			return (*it);
	}
	return (*this->_caps.end());
}

template <typename T, typename U>
const blc::tools::protocolCaps<T, U> &blc::tools::protocolFactory<T, U>::find(typename std::vector<blc::tools::protocolCaps<T, U>>::iterator it) const {
	for (auto iter = this->_caps.begin(); iter != this->_caps.end(); iter++) {
		if (it == iter)
			return (*iter);
	}
	return (*this->_caps.end());
}

template <typename T, typename U>
bool blc::tools::protocolFactory<T, U>::replace(const T &code, const std::function<int(U)> &callback) {
	for (auto it = this->_caps.begin(); it != this->_caps.end(); it++) {
		if ((*it).getCode() == code) {
			(*it).setCallback(callback);
			return (true);
		}
	}
	return (false);
}

template <typename T, typename U>
bool blc::tools::protocolFactory<T, U>::replace(const blc::tools::protocolCaps<T, U> &cap, const std::function<int(U)> &callback) {
	for (auto it = this->_caps.begin(); it != this->_caps.end(); it++) {
		if (*it == cap) {
			(*it).setCallback(callback);
			return (true);
		}
	}
	return (false);
}


template <typename T, typename U>
int blc::tools::protocolFactory<T, U>::activate(const T &code, const U &param) const {
	for (auto it = this->_caps.begin(); it != this->_caps.end(); it++) {
		if ((*it).getCode() == code) {
			return ((*it).activate(param));
		}
	}
	return (-1);
}

template <typename T, typename U>
void blc::tools::protocolFactory<T, U>::clear() {
	this->_caps.clear();
}

template <typename T, typename U>
unsigned int blc::tools::protocolFactory<T, U>::size() const {
	return (this->_caps.size());
}

template <typename T, typename U>
bool blc::tools::protocolFactory<T, U>::empty() const {
	return (this->_caps.empty());
}


template <typename T, typename U>
blc::tools::protocolFactory<T, U> &blc::tools::protocolFactory<T, U>::operator=(const protocolFactory &other) {
	for (int i = 0; i != other.size(); i++) {
		this->_caps[i] = other[i];
	}
	return (*this);
}

template <typename T, typename U>
const blc::tools::protocolCaps<T, U> &blc::tools::protocolFactory<T, U>::operator[](int i) const {
	return (this->_caps[i]);
}
