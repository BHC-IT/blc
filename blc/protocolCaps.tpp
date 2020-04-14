template <typename T, typename U>
blc::tools::protocolCaps<T, U>::protocolCaps(const T &code, const std::function<int(U)> &callback) : _code(code), _callback(callback) {
}

template <typename T, typename U>
blc::tools::protocolCaps<T, U>::protocolCaps(const protocolCaps<T, U> &cap) {
	this->_code = cap.getCode();
	this->_callback = cap.getCallback();
}

template <typename T, typename U>
blc::tools::protocolCaps<T, U>::protocolCaps(protocolCaps<T, U> &&cap) {
	this->_code = cap.getCode();
	cap.setCode(0);
	this->_callback = cap.getCallback();
	cap.setCallback([](U val){return (-1);});
}

template <typename T, typename U>
void blc::tools::protocolCaps<T, U>::setCode(const T &code) {
	this->_code = code;
}

template <typename T, typename U>
void blc::tools::protocolCaps<T, U>::setCallback(const std::function<int(U)> &callback) {
	this->_callback = callback;
}

template <typename T, typename U>
T blc::tools::protocolCaps<T, U>::getCode() const
{
	return (this->_code);
}

template <typename T, typename U>
std::function<int(U)> blc::tools::protocolCaps<T, U>::getCallback() const
{
	return (this->_callback);
}

template <typename T, typename U>
bool blc::tools::protocolCaps<T, U>::check(const T &code) const
{
	return (this->_code == code);
}

template <typename T, typename U>
int blc::tools::protocolCaps<T, U>::activate(const U &param) const
{
	return (this->_callback(param));
}

template <typename T, typename U>
int blc::tools::protocolCaps<T, U>::checkAndActive(const T &code, const U &param) const
{
	if (this->check(code) == true)
		return (this->activate(param));
	return (-1);
}

template <typename T, typename U>
blc::tools::protocolCaps<T, U> &blc::tools::protocolCaps<T, U>::operator=(const protocolCaps<T, U> &cap) {
	this->_code = cap.getCode();
	this->_callback = cap.getCallback();
	return (*this);
}

template <typename T, typename U>
blc::tools::protocolCaps<T, U> &blc::tools::protocolCaps<T, U>::operator=(const std::function<int(U)> &callback) {
	this->_callback = callback;
	return (*this);
}

template <typename T, typename U>
blc::tools::protocolCaps<T, U> &blc::tools::protocolCaps<T, U>::operator=(const T &code) {
	this->_code = code;

	return (*this);
}

template <typename T, typename U>
bool blc::tools::protocolCaps<T, U>::operator==(const protocolCaps<T, U> &cap) {
	return (this->_code == cap.getCode());
}

template <typename T, typename U>
blc::tools::protocolCaps<T, U> &blc::tools::protocolCaps<T, U>::operator<<(const T &param) {
	this->activate(param);
	return (*this);
}
