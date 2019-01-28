#pragma once

#include "COG/Window.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace COG {
	
	struct WindowData {
		std::string title;
		unsigned width, height;
		bool vsync;

		Window::callback event_callback;

		inline void operator=(const WindowDetails& rhs) {
			title = rhs.title;
			width = rhs.width;
			height = rhs.height;
		}
	};
	
	class WindowsWindow : public Window {
		public:
		WindowsWindow(const WindowDetails& details);
		virtual inline ~WindowsWindow(){ }
		virtual inline bool vsync() const noexcept override{ return data.vsync; }
		
		virtual void on_update() override;
		virtual void destroy() override;
		virtual void set_vsync(bool enable = true) override;
		inline virtual void set_callback(const callback& callback) override { 
			data.event_callback = callback;
		}

		virtual inline unsigned width() const noexcept { return data.width; }
		virtual inline unsigned height() const noexcept { return data.height; }

		private:
		GLFWwindow* window;

		WindowData data;
	};

	

}