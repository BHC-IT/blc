#pragma once

namespace blc {
	/// test if a template class instanciation respecte all needed concept. do construct this in your constructor for better error output.
	namespace concept {
		template <typename... args>
		class constraint {
		private:
			template <typename U>
			bool unitary_test(U &&u){
				return (u.predicat());
			}
			template <typename... test>
			bool testAll(test&&... i){
				return (i && ...);
			}
			bool testConstraint(){
				return testAll(unitary_test(args())...);
			}
		protected:
			constraint() {
				// this->testConstraint();
			}
		public:
		};
	}
}