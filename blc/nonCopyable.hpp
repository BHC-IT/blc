#pragma once


namespace blc {
	namespace tools {
		/// set the copy constructor and copy operator to private to get a compilation error when copied in code. inherite this to class that dont be sensfully copied
		class nonCopyable {
		public:
			nonCopyable();
		private:
			nonCopyable(const nonCopyable &other);
			nonCopyable &operator=(const nonCopyable &other);
		};
	}
}