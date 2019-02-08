#include "precomp/precomp.h"

#include "COG_Engine.h"
#include "Log.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Version.h"

namespace COG {
	
	template<typename T>
	static inline std::unique_ptr<T> create_window(const WindowDetails& details) {

		static_assert(std::is_base_of<Window, T>(), "Cannot create a window due to a bad template!");
		return std::make_unique<T>(details);
	}

	static inline std::unique_ptr<Window> create_window(const WindowDetails& details) {

#ifdef COG_PLATFORM_WINDOWS
		 return create_window<WindowsWindow>(details);
#else 
#error COG currently supports the following: Windows
#endif // COG_PLATOFRM_WINDOWS

	}

	COG_Engine* COG_Engine::instance = nullptr;
	
	COG_Engine::COG_Engine(const WindowDetails& details) {
		
		Log::init(details.title);
		
		info_internal("COG Version: " + version_print());

		COG_ASSERT_INTERNAL(instance == nullptr, "Multiple instances of the COG Engine found!");
		instance = this;
		running = true;
		
		window = create_window(details);

		debug_internal("Setting main event callback...")	;
		window->set_callback(std::bind(&COG_Engine::on_event, this, std::placeholders::_1));

		set_clear_color(0, .5, 1);
		
		debug_internal("Starting engine...");

		start = time_now();
	}
	
	void COG_Engine::on_event(Event & e) {
	
		EventDispatcher dispatch(e);
		dispatch.dispatch<WindowCloseEvent>(std::bind(&COG_Engine::on_window_close, this, std::placeholders::_1));

		auto it = layers.end();

		while(it != layers.begin() && !e.handled) {
			(*--it)->on_event(e);
		}

	}
	
	void COG_Engine::run() {
		
		unsigned frame_count = 0;
		double previous_time = glfwGetTime(), last_update = glfwGetTime();

		while(running) {
			  glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
			  glClear(GL_COLOR_BUFFER_BIT);

			  const double current_time = glfwGetTime();

			  layers.update_sweep(current_time - last_update);
			  last_update = current_time;

			  window->on_update();
			  frame_count++;

			  if(current_time-previous_time>=1) {
				  
				  std::stringstream stream("FPS: ");
				  stream << frame_count << " | FrameTime: " << (1000.0 / frame_count) << "ms";
				  info_internal(stream.str());

				  last_second_frames = frame_count;
				  frame_count = 0;

				  previous_time = current_time;
			  }
		}
		
	}

	inline bool COG_Engine::on_window_close(WindowCloseEvent & e) {
		running = false;
		return true;
	}
}