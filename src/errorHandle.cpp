/*
** EPITECH PROJECT, 2017
**
** File description:
**	error
*/

#include <string>
#include <sstream>
#include "blc/errorHandle.hpp"

blc::error::exception::exception(std::string msg) : _msg(msg), _file("ND"), _func("ND"), _line(-1), _time(-1)
{
	std::ostringstream oss;

	oss << "Error : " << msg;
	this->_msg = oss.str();
}

blc::error::exception::exception(std::string msg, std::string file, std::string func, int line, std::time_t time) : _msg(msg), _file(file), _func(func), _line(line), _time(time)
{
	std::ostringstream oss;

	oss << msg;
	this->_msg = oss.str();
}