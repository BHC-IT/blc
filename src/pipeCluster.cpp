#include "blc/pipeCluster.hpp"

std::vector<blc::tools::pipe> blc::tools::pipeCluster::getCluster() const
{
	return (this->_cluster);
}

void blc::tools::pipeCluster::setCluster(const std::vector<blc::tools::pipe> &cluster)
{
	this->_cluster = cluster;
}

void blc::tools::pipeCluster::pushBack(const blc::tools::pipe &pipe)
{
	this->_cluster.push_back(pipe);
}

void blc::tools::pipeCluster::writeToAll(const std::string &str)
{
	for (blc::tools::pipe &pipe : this->_cluster){
		pipe.write(str);
	}
}


blc::tools::pipe blc::tools::pipeCluster::operator[](int i)
{
	return (this->_cluster[i]);
}

