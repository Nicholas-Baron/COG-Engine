#include "precomp/precomp.h"

#include "COG_Engine.h"
#include "Log.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Version.h"

namespace COG {
	
	COG_Engine* COG_Engine::instance = nullptr;
	
	COG_Engine::COG_Engine(const WindowDetails& details) {
		
		Log::init(details.title);
		
		info_internal("COG Version: " + version_print());

		COG_ASSERT_INTERNAL(instance == nullptr, "Multiple instances of the COG Engine found!");
		instance = this;
		running = true;
		
		
#ifdef COG_PLATFORM_WINDOWS
		window = create_window<WindowsWindow>(details);
#else
		#error Only Windows is currently supported!
#endif
		window->set_callback(std::bind(&COG_Engine::on_event, this, std::placeholders::_1));

		set_clear_color(0, .5, 1);
		
		start = time_now();
	}
	void COG_Engine::on_event(Event & e) {
	
		info_internal("Dispatching " + e.str() + "...");
		
		EventDispatcher dispatch(e);
		dispatch.dispatch<WindowCloseEvent>(std::bind(&COG_Engine::on_window_close, this, std::placeholders::_1));

	}
	
	void COG_Engine::run() {
		
		unsigned frame_count = 0;
		double previous_time = glfwGetTime();

		while(running) {
			  glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
			  glClear(GL_COLOR_BUFFER_BIT);

			  window->on_update();
			  frame_count++;
			  const double current_time = glfwGetTime();

			  if(current_time-previous_time>=1) {
				  
				  std::stringstream stream("FPS: ");
				  stream << frame_count << " | FrameTime: " << (1000.0 / frame_count) << "ms";
				  info_internal(stream.str());

				  last_second_frames = frame_count;
				  frame_count = 0;

				  previous_time = current_time;
			  }
		}
		window->destroy();
	}

	inline bool COG_Engine::on_window_close(WindowCloseEvent & e) {
		running = false;
		return true;
	}
}