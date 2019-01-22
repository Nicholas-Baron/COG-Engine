#pragma once

#include "Core.h"

#include <iostream>

namespace COG{
	
	class COG_API COG_Engine {
		public:
		COG_Engine();
		~COG_Engine();

		inline void test_print() const {
			std::cout << "welcome to COG Engine" << std::endl;
		}
	};
}