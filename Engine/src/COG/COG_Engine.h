#pragma once

#include "Core.h"
#include "Window.h"

namespace COG{
	
	class COG_API COG_Engine {
		
		private:
		std::unique_ptr<Window> window;

		public:
		COG_Engine(const WindowDetails& details = WindowDetails());
		~COG_Engine();
	};
}