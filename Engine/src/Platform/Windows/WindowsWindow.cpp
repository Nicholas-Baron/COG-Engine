#include "precomp/precomp.h"

#include "WindowsWindow.h"
#include "COG/Log.h"

#include "COG/Events/AppEvent.h"

namespace COG {
	
	static bool glfw_ready = false;

	static void glfw_error_callback(int error, const char * const desc){
		error_internal("GLFW Error " + std::to_string(error) + " : " + desc);
	}
	
	WindowsWindow::WindowsWindow(const WindowDetails& details_in) {
		details = details_in;

		info_internal("Creating window " + details.title);

		if(!glfw_ready){
			auto success = glfwInit();
			COG_ASSERT_INTERNAL(success, "Could not init GLFW!");
			glfwSetErrorCallback(glfw_error_callback);
			glfw_ready = true;
		}

		window = glfwCreateWindow(details.width, details.height, details.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		auto status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		COG_ASSERT_INTERNAL(status, "Failed to init GLAD!");
		glfwSetWindowUserPointer(window, &details);
		set_vsync();

		glfwSetWindowSizeCallback(window, [](GLFWwindow* win, int width, int height){
			auto& data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(win));
			data.height = height;
			data.width = width;

			WindowResizeEvent ev(width, height);
			data.event_callback(ev);
		});

		//TODO: Setup other callbacks
	}

	WindowsWindow::~WindowsWindow() {
		glfwDestroyWindow(window);
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