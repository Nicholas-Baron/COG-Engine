#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/AppEvent.h"

namespace COG{
	
	class COG_Engine {
		
		private:
		
		static COG_Engine* instance;
		
		std::unique_ptr<Window> window;
		bool running;
		unsigned last_second_frames;

		public:
		COG_API COG_Engine(const WindowDetails& details = WindowDetails());
		
		COG_API inline unsigned frame_count() const noexcept { return last_second_frames; }
		inline bool on_window_close(WindowCloseEvent& e);
		
		void on_event(Event& e);
		COG_API void run();
	};
}