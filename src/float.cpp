/*
Copyright 2020 BHC-IT

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include "blc/float.hpp"

#include <iostream>

blc::math::Float::Float() : _nb(0), _E(0) {
}

blc::math::Float::Float(double i) : _nb(i), _E(0) {
	if (i == 0)
		return;
	if (this->_nb > 1 || this->_nb < -1) {
		for (; this->_nb >= 10 || this->_nb <= -10;) {
			this->_E++;
			this->_nb /= 10;
		}
	} else {
		for (; this->_nb < 1 && this->_nb > -1;) {
			this->_E--;
			this->_nb *= 10;
		}
	}
}

blc::math::Float::Float(double i, int E) : _nb(i), _E(E) {
	if (this->_nb == 0)
		return;
	if (this->_nb > 1 || this->_nb < -1) {
		for (; this->_nb >= 10 || this->_nb <= -10;) {
			this->_E++;
			this->_nb /= 10;
		}
	} else {
		for (; this->_nb < 1 && this->_nb > -1;) {
			this->_E--;
			this->_nb *= 10;
		}
	}
}

blc::math::Float::Float(const blc::math::Float &other) : _nb(other.getNb()), _E(other.getE()) {
}

blc::math::Float::Float(blc::math::Float &&other) : _nb(other.getNb()), _E(other.getE()) {
	other.setNb(0);
	other.setE(0);
}

blc::math::Float &blc::math::Float::operator=(double i) {
	this->_nb = i;
	this->_E = 0;

	if (this->_nb == 0)
		return (*this);
	if (this->_nb > 1 || this->_nb < -1) {
		for (; this->_nb >= 10 || this->_nb <= -10;) {
			this->_E++;
			this->_nb /= 10;
		}
	} else {
		for (; this->_nb < 1 && this->_nb > -1;) {
			this->_E--;
			this->_nb *= 10;
		}
	}
	return (*this);
}

blc::math::Float &blc::math::Float::operator=(const blc::math::Float &other) {
	this->_nb = other.getNb();
	this->_E = other.getE();
	return (*this);
}

blc::math::Float &blc::math::Float::operator=(blc::math::Float &&other) {
	this->_nb = other.getNb();
	this->_E = other.getE();

	other.setNb(0);
	other.setE(0);
	return (*this);
}

blc::math::Float blc::math::Float::operator+(double i) const {
	blc::math::Float fl(i);
	blc::math::Float ret;

	ret = *this + fl;
	return (ret);
}

blc::math::Float blc::math::Float::operator+(const blc::math::Float &i) const {
	int diff = this->_E - i.getE();
	double tmp = i.getNb();

	while (diff != 0) {
		if (diff < 0) {
			tmp *= 10;
			diff++;
		} else {
			tmp /= 10;
			diff--;
		}
	}
	blc::math::Float ret = blc::math::Float(this->_nb + tmp, this->_E);
	return (ret);
}

blc::math::Float blc::math::Float::operator-(double i) const {
	blc::math::Float ret;
	blc::math::Float fl(i);

	ret = *this - fl;
	return (ret);
}

blc::math::Float blc::math::Float::operator-(const blc::math::Float &i) const {
	blc::math::Float ret;
	int diff = this->_E - i.getE();
	double tmp = i.getNb();

	while (diff != 0) {
		if (diff < 0) {
			tmp *= 10;
			diff++;
		} else {
			tmp /= 10;
			diff--;
		}
	}
	ret = blc::math::Float(this->_nb - tmp, this->_E);
	return (ret);
}

blc::math::Float blc::math::Float::operator*(double i) const {
	blc::math::Float ret;
	blc::math::Float fl(i);

	ret = *this * fl;
	return (ret);
}

blc::math::Float blc::math::Float::operator*(const blc::math::Float &i) const {
	blc::math::Float ret;
	int diff = this->_E - i.getE();
	double tmp = i.getNb();

	while (diff != 0) {
		if (diff < 0) {
			tmp *= 10;
			diff++;
		} else {
			tmp /= 10;
			diff--;
		}
	}
	ret = blc::math::Float(this->_nb * tmp, this->_E);
	return (ret);
}

blc::math::Float blc::math::Float::operator/(double i) const {
	blc::math::Float ret;
	blc::math::Float fl(i);

	ret = *this / fl;
	return (ret);
}

blc::math::Float blc::math::Float::operator/(const blc::math::Float &i) const {
	blc::math::Float ret;
	int diff = this->_E - i.getE();
	double tmp = i.getNb();

	while (diff != 0) {
		if (diff < 0) {
			tmp *= 10;
			diff++;
		} else {
			tmp /= 10;
			diff--;
		}
	}
	ret = blc::math::Float(this->_nb / tmp, this->_E);
	return (ret);
}

bool blc::math::Float::operator==(double i) const {
	if (this->calculate() == i)
		return (true);
	return (false);
}

bool blc::math::Float::operator==(const blc::math::Float &i) const {
	return (this->_nb == i.getNb() && this->_E == i.getE());
}

bool blc::math::Float::operator!=(double i) const {
	if (*this == i)
		return (false);
	return (true);
}

bool blc::math::Float::operator!=(const blc::math::Float &i) const {
	if (*this == i)
		return (false);
	return (true);
}

bool blc::math::Float::operator<(double i) const {
	return (this->calculate() < i);
}

bool blc::math::Float::operator<(const blc::math::Float &i) const {
	return (this->calculate() < i.calculate());
}

bool blc::math::Float::operator>(double i) const {
	return (i < this->calculate());
}

bool blc::math::Float::operator>(const blc::math::Float &i) const {
	return (i < *this);
}

bool blc::math::Float::operator<=(double i) const {
	return !(*this > i);
}

bool blc::math::Float::operator<=(const blc::math::Float &i) const {
	return !(*this > i);
}

bool blc::math::Float::operator>=(double i) const {
	return !(*this < i);
}

bool blc::math::Float::operator>=(const blc::math::Float &i) const {
	return !(*this < i);
}

double blc::math::Float::operator()() const {
	return (this->calculate());
}

double blc::math::Float::getNb() const {
	return (this->_nb);
}

void blc::math::Float::setNb(double nb) {
	this->_nb = nb;
}

int blc::math::Float::getE() const {
	return (this->_E);
}

void blc::math::Float::setE(int E) {
	this->_E = E;
}

double blc::math::Float::calculate() const {
	int	tmp = this->_E;
	double	ret = this->_nb;

	while (tmp != 0) {
		if (tmp < 0) {
			ret /= 10;
			tmp++;
		} else {
			ret *= 10;
			tmp--;
		}
	}
	return (ret);
}

void blc::math::Float::align() {
	if (this->_nb > 1 || this->_nb < -1) {
		for (; this->_nb >= 10 || this->_nb <= -10;) {
			this->_E++;
			this->_nb /= 10;
		}
	} else {
		for (; this->_nb < 1 && this->_nb > -1;) {
			this->_E--;
			this->_nb *= 10;
		}
	}
}

void blc::math::Float::align(int nb) {
	if (nb > 0) {
		while (nb != 0) {
			this->_nb *= 10;
			this->_E--;
			nb--;
		}
	} else {
		while (nb != 0) {
			this->_nb /= 10;
			this->_E++;
			nb++;
		}
	}
}

std::string blc::math::Float::serialize() const {
	return ("");
}

void blc::math::Float::unserialize(const std::string &str) {
}
