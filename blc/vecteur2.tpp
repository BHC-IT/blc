#include <cmath>

template <typename T>
vecteur2<T>::vecteur2(T &&xP, T &&yP) : x(xP), y(yP)
{
}

template <typename T>
vecteur2<T>::vecteur2(const vecteur2<T> &other) : x(other.x), y(other.y)
{
}

template <typename T>
vecteur2 &vecteur2<T>::operator=(const vecteur2<T> &other)
{
	this->x = other.x;
	this->y = other.y;
}

template <typename T>
vecteur2 vecteur2<T>::operator+(const vecteur2<T> &other) const
{
	vecteur2 ret(*this);

	ret.x += other.x;
	ret.y += other.y;
	return (ret);
}

template <typename T>
vecteur2 vecteur2<T>::operator-(const vecteur2<T> &other) const
{
	vecteur2 ret(*this);

	ret.x -= other.x;
	ret.y -= other.y;
	return (ret);
}

template <typename T>
vecteur2 vecteur2<T>::operator*(const vecteur2<T> &other) const
{
	vecteur2 ret(*this);

	ret.x *= other.x;
	ret.y *= other.y;
	return (ret);
}

template <typename T>
vecteur2 vecteur2<T>::operator/(const vecteur2<T> &other) const
{
	vecteur2 ret(*this);

	ret.x /= other.x;
	ret.y /= other.y;
	return (ret);
}

template <typename T>
bool vecteur2<T>::operator==(const vecteur2<T> &other) const
{
	if (this->x == other.x && this->y == other.y)
		return (true);
	return (false);
}

template <typename T>
bool vecteur2<T>::operator!=(const vecteur2<T> &other) const
{
	return (!(*this == other));
}

template <typename T>
bool vecteur2<T>::operator<(const vecteur2<T> &other) const
{
	if (this->x < other.x)
		return (true);
	if (this->x > other.x)
		return (false);
	if (this->y < other.y)
		return (true);
	return (false);
}

template <typename T>
bool vecteur2<T>::operator<=(const vecteur2<T> &other) const
{
	return (!(other < *this));
}

template <typename T>
bool vecteur2<T>::operator>(const vecteur2<T> &other) const
{
	return (other < *this);
}

template <typename T>
bool vecteur2<T>::operator>=(const vecteur2<T> &other) const
{
	return (!(*this < other));
}

template <typename T>
T vecteur2<T>::sum() const
{
	return (this->x + this->y);
}

template <typename T>
T vecteur2<T>::minus() const
{
	return (this->x - this->y);
}

template <typename T>
T vecteur2<T>::minusInv() const
{
	return (this->y - this->x);
}

template <typename T>
T vecteur2<T>::prod() const
{
	return (this->x * this->y);
}

template <typename T>
T vecteur2<T>::div() const
{
	return (this->x / this->y);
}

template <typename T>
T vecteur2<T>::divInv() const
{
	return (this->y / this->x);
}

template <typename T>
T vecteur2<T>::avg() const
{
	return ((this->x + this->y) / 2);
}

template <typename T>
T vecteur2<T>::norme() const
{
	return (std::sqrt(this->x * this->x + this->y * this->y));
}

template <typename T>
T vecteur2<T>::norme(const vecteur2<T> &other) const
{
	return (std::sqrt(this->x * other.x + this->y * other.y));
}

template <typename T>
T vecteur2<T>::min() const
{
	if (this->x < this->y)
		return (this->x);
	return (this->y);
}

template <typename T>
T vecteur2<T>::max() const
{
	if (this->x > this->y)
		return (this->x);
	return (this->y);
}

template <typename T>
void vecteur2<T>::minimize()
{
	return (this->x);
}

template <typename T>
void vecteur2<T>::swap()
{
	T temp;

	temp = this->x;
	this->x = this->y;
	this->y = temp;
}

template <typename T>
void vecteur2<T>::swap(vecteur2<T> &other)
{
	vecteur2<T> temp(*this);

	this->x = other.x;
	this->y = other.y;
	other.x = temp.x;
	other.y = temp.y;
}


