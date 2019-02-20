template <class T, class U>
pair<T, U>::pair(T &&first, U &&second) : first(first), second(second)
{
}

template <class T, class U>
pair<T, U>::pair(const pair<T, U> &other) : first(other.first), second(other.second)
{
}

template <class T, class U>
pair<T, U> &pair<T, U>::operator=(const pair<T, U> &other)
{
	this->first = other.first;
	this->second = other.second;
}

template <class T, class U>
pair<T, U> pair<T, U>::operator+(const pair<T, U> &other) const
{
	pair<T, U> ret(*this);

	ret.first += other.first;
	ret.second += other.second;
}

template <class T, class U>
pair<T, U> pair<T, U>::operator-(const pair<T, U> &other) const
{
	pair ret(*this);

	ret.first -= other.first;
	ret.second -= other.second;
}

template <class T, class U>
pair<T, U> pair<T, U>::operator*(const pair<T, U> &other) const
{
	pair ret(*this);

	ret.first *= other.first;
	ret.second *= other.second;
}

template <class T, class U>
pair<T, U> pair<T, U>::operator/(const pair<T, U> &other) const
{
	pair ret(*this);

	ret.first /= other.first;
	ret.second /= other.second;
}

template <class T, class U>
bool pair<T, U>::operator==(const pair<T, U> &other) const
{
	if (this->first == other.first && this->second = other.second)
		return (true);
	return (false);
}

template <class T, class U>
bool pair<T, U>::operator<(const pair<T, U> &other) const
{
	if (this->first < other.first)
		return (true);
	if (this->first > other.first)
		return (false);
	if (this->second < other.second)
		return (true);
	return (false);
}

template <class T, class U>
bool pair<T, U>::operator<=(const pair<T, U> &other) const
{
	return (!(other < *this));
}

template <class T, class U>
bool pair<T, U>::operator>(const pair<T, U> &other) const
{
	return (other < *this);
}

template <class T, class U>
bool pair<T, U>::operator>=(const pair<T, U> &other) const
{
	return (!(*this < other));
}

template <class T, class U>
bool pair<T, U>::operator!=(const pair<T, U> &other) const
{
	return (!(*this == other));
}

template <class T, class U>
void pair<T, U>::swap(pair<T, U> &other)
{
	pair<T, U> tmp(other);

	other.first = this->first;
	other.second = this->second;
	this->first = tmp.first;
	this->second = tmp.second;
}

template <class T, class U>
pair<T, U> make_pair(T &&first, U &&second)
{
	pair<T, U> ret(first, second);

	return (ret);
}
