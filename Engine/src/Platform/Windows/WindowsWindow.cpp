#include "precomp/precomp.h"

#include "WindowsWindow.h"
#include "COG/Log.h"

#include "COG/Events/AppEvent.h"

namespace COG {
	
	static bool glfw_ready = false;

	static void glfw_error_callback(int error, const char * const desc){
		
		std::stringstream print("GLFW Error #");
		print << std::showbase << std::hex << error << " : " << desc;
		error_internal(print.str());
	}
	
	WindowsWindow::WindowsWindow(const WindowDetails& details_in) {
		
		data = details_in;

		info_internal("Creating window labeled " + data.title + "...");
		
		if(!glfw_ready){
			COG_ASSERT_INTERNAL(glfwInit(), "Could not init GLFW!");
			glfwSetErrorCallback(glfw_error_callback);
			glfw_ready = true;
		}

		info_internal("GLFW is ready.");

		window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		COG_ASSERT_INTERNAL(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress), "Failed to init GLAD!");
		glfwSetWindowUserPointer(window, &data);
		set_vsync();

		info_internal("Setting callbacks...");

		glfwSetWindowSizeCallback(window, [](auto* win, int width, int height) -> void {
			auto* data = (WindowData*)glfwGetWindowUserPointer(win);
			data->height = height;
			data->width = width;

			WindowResizeEvent ev(width, height);
			data->event_callback(ev);
		});

		glfwSetWindowCloseCallback(window, [](auto* win) -> void {
			auto* data = (WindowData*)glfwGetWindowUserPointer(win);
		
			warn_internal("Closing...");

			WindowCloseEvent ev;
			data->event_callback(ev);
		});

		//TODO: Setup other callbacks
	}

	void WindowsWindow::destroy() {
		//glfwDestroyWindow(window);
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	
	void WindowsWindow::on_update() {
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	void WindowsWindow::set_vsync(bool enable) {
		glfwSwapInterval(enable?1:0);
		data.vsync = enable;
	}
}