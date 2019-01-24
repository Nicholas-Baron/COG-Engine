#include "precomp/precomp.h"

#include "WindowsWindow.h"
#include "COG/Log.h"

namespace COG {
	
	static bool glfw_ready = false;

	static void glfw_error_callback(int error, const char * const desc){
		error_internal("GLFW Error " + std::to_string(error) + " : " + desc);
	}
	
	WindowsWindow::WindowsWindow(const WindowDetails& details_in) {
		this->details = details_in;

		info_internal("Creating window " + details.title);

		if(!glfw_ready){
			auto success = glfwInit();
			COG_ASSERT_INTERNAL(success, "Could not init GLFW!");
			glfwSetErrorCallback(glfw_error_callback);
			glfw_ready = true;
		}

		window = glfwCreateWindow(details.width, details.height, details.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		auto status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		COG_ASSERT_INTERNAL(status, "Failed to init GLAD!");
		glfwSetWindowUserPointer(window, &details);
		set_vsync();
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
		vsync_on = enable;
	}
}