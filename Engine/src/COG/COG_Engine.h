#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/AppEvent.h"

namespace COG{
	
	class COG_API COG_Engine {
		
		private:
		
		static COG_Engine* instance;
		
		std::unique_ptr<Window> window;
		bool running;

		public:
		COG_Engine(const WindowDetails& details = WindowDetails());
		
		inline bool on_window_close(WindowCloseEvent& e);
		
		void on_event(Event& e);
		void run();
	};
}