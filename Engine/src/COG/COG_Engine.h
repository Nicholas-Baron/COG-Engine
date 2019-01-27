#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/AppEvent.h"

namespace COG{
	
	inline auto time_now() noexcept { return std::chrono::high_resolution_clock::now(); }

	class COG_Engine {
		
		private:
		
		static COG_Engine* instance;
		std::chrono::high_resolution_clock::time_point start;
		bool running;

		//Visual stuff

		std::unique_ptr<Window> window;
		std::array<float, 4> clear_color;
		unsigned last_second_frames;
		
		public:
		COG_API COG_Engine(const WindowDetails& details = WindowDetails());
		
		COG_API inline unsigned frame_count() const noexcept { 
			return last_second_frames;
		}
		
		COG_API inline double time() const noexcept { 
			using namespace std::chrono;
			using milliD = duration<double, std::milli>;
			return duration_cast<milliD>(time_now() - start).count();
		}

		COG_API void set_clear_color(float red, float green, float blue, float alpha = 1) noexcept{
			clear_color = {red, green, blue, alpha};
		}

		COG_API void run();

		inline bool on_window_close(WindowCloseEvent& e);
		void on_event(Event& e);
	};

}