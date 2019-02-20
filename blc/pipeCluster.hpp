#pragma once

#include <vector>
#include <string>
#include "blc/pipe.hpp"

namespace blc {
	namespace tools {
		class pipeCluster {
		public:
			pipeCluster() = default;
			~pipeCluster() = default;
			std::vector<pipe>	getCluster() const;
			void			setCluster(const std::vector<pipe> &cluster);
			void			pushBack(const pipe &pipe);
			void			writeToAll(const std::string &str);
			pipe			operator[](int i);
		private:
			std::vector<pipe> _cluster;
		};
	}
}