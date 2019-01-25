#pragma once

#include "COG/Window.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace COG {

	class WindowsWindow : public Window {
		public:
		WindowsWindow(const WindowDetails& details);
		virtual ~WindowsWindow();

		virtual inline bool vsync() const noexcept override{ return data.vsync; }
		
		virtual void on_update() override;
		virtual void set_vsync(bool enable = true) override;
		inline virtual void set_callback(const callback& callback){ 
			data.event_callback = callback;
		}

		private:
		GLFWwindow* window;

		struct WindowData {
		   std::string title;
		   unsigned width, height;
		   bool vsync;

		   callback event_callback;
		} data;
	};

	

}