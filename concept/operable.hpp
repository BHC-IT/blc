#pragma once

#include "blc/concept.hpp"

namespace blc {
	namespace concept {
		template <typename T>
		class operable : public blc::concept::concept {
		public:
			operable(){
				// static_assert(T i + T j, "not operable");
			};
			bool predicat(){
				T i;
				T j;
				i + j;
				// static_assert(T i + T j, "not operable");
				return (true);
			};
		};
	}
}