#include "blc/client2way.hpp"

blc::network::client2way::client2way() : _comm(), _data()
{
}

blc::network::client2way::client2way(std::string addresse, int port, bool block, int mode, int type) :	_comm(addresse, port, block, mode, type),
_data(addresse, port, block, mode, type)
{
}

blc::network::client2way::~client2way()
{
}

blc::network::Socket &blc::network::client2way::getComm()
{
	return (this->_comm);
}

blc::network::Socket &blc::network::client2way::getData()
{
	return (this->_data);
}

std::string blc::network::client2way::getAddress() const
{
	return (this->_comm.getAddress());
}

int blc::network::client2way::getPort() const
{
	return (this->_comm.getPort());
}

bool blc::network::client2way::getBlock() const
{
	return (this->_comm.getBlock());
}

int blc::network::client2way::getMode() const
{
	return (this->_comm.getMode());
}

int blc::network::client2way::getType() const
{
	return (this->_comm.getType());
}

std::string blc::network::client2way::getAddressData() const
{
	return (this->_data.getAddress());
}

int blc::network::client2way::getPortData() const
{
	return (this->_data.getPort());
}

bool blc::network::client2way::getBlockData() const
{
	return (this->_data.getBlock());
}

int blc::network::client2way::getModeData() const
{
	return (this->_data.getMode());
}

int blc::network::client2way::getTypeData() const
{
	return (this->_data.getType());
}

void blc::network::client2way::setAddress(const std::string &add)
{
	this->_comm.setAddress(add);
}

void blc::network::client2way::setPort(int port)
{
	this->_comm.setPort(port);
}

void blc::network::client2way::setBlock(bool block)
{
	this->_comm.setBlock(block);
}

void blc::network::client2way::setMode(int mode)
{
	this->_comm.setMode(mode);
}

void blc::network::client2way::setType(int type)
{
	this->_comm.setType(type);
}

void blc::network::client2way::setAddressData(const std::string &add)
{
	this->_data.setAddress(add);
}

void blc::network::client2way::setPortData(int port)
{
	this->_data.setPort(port);
}

void blc::network::client2way::setBlockData(bool block)
{
	this->_data.setBlock(block);
}

void blc::network::client2way::setModeData(int mode)
{
	this->_data.setMode(mode);
}

void blc::network::client2way::setTypeData(int type)
{
	this->_data.setType(type);
}

void blc::network::client2way::write(const std::string &str) const
{
	this->_comm.write(str);
}

void blc::network::client2way::writeData(const std::string &str) const
{
	this->_data.write(str);
}

std::string blc::network::client2way::read() const
{
	return (this->_comm.read());
}

std::string blc::network::client2way::readData() const
{
	return (this->_data.read());
}

void blc::network::client2way::closeComm()
{
	this->_comm.close();
}

void blc::network::client2way::closeData()
{
	this->_data.close();
}

void blc::network::client2way::close()
{
	this->closeComm();
	this->closeData();
}

void blc::network::client2way::openComm()
{
	this->_comm.open();
}

void blc::network::client2way::openData()
{
	this->_data.open();
}

void blc::network::client2way::open()
{
	this->openComm();
	this->openData();
}

bool blc::network::client2way::readableComm() const
{
	return (this->_comm.readable());
}

bool blc::network::client2way::readableData() const
{
	return (this->_data.readable());
}

bool blc::network::client2way::writeableComm() const
{
	return (this->_comm.writable());
}

bool blc::network::client2way::writeableData() const
{
	return (this->_data.writable());
}

bool blc::network::client2way::waitReadComm(int usec) const
{
	return (this->_comm.waitRead(usec));
}

bool blc::network::client2way::waitReadData(int usec) const
{
	return (this->_data.waitRead(usec));
}

bool blc::network::client2way::waitWriteComm(int usec) const
{
	return (this->_comm.waitWrite(usec));
}

bool blc::network::client2way::waitWriteData(int usec) const
{
	return (this->_data.waitWrite(usec));
}
