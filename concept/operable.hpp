#pragma once

#include "blc/concept.hpp"

namespace blc {
	namespace concept {
		template <typename T>
		class operable : public blc::concept::concept {
		public:
			operable(){
			};
			bool predicat(){
				T i;
				T j;
				i + j;
				return (true);
			};
		};
	}
}