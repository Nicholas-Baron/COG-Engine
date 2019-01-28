#include "precomp/precomp.h"

#include "WindowsWindow.h"
#include "COG/Log.h"

#include "COG/Events/AppEvent.h"
#include "COG/Events/KeyEvent.h"
#include "COG/Events/MouseEvent.h"

namespace COG {
	
	static bool glfw_ready = false;

	static void glfw_error_callback(int error, const char * const desc){
		
		std::stringstream print("GLFW Error #");
		print << std::showbase << std::hex << error << " : " << desc;
		error_internal(print.str());
	}
	
	static inline WindowData* data_cast(GLFWwindow* win) {
		return static_cast<WindowData*>(glfwGetWindowUserPointer(win));
	};

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
		set_vsync();

		info_internal("Setting callbacks...");
		
		glfwSetWindowUserPointer(window, &data);
		
		glfwSetWindowSizeCallback(window, [](auto* win, int width, int height) -> void {
			auto* data = data_cast(win);
			data->height = height;
			data->width = width;

			WindowResizeEvent ev(width, height);
			data->event_callback(ev);
		});

		glfwSetWindowCloseCallback(window, [](auto* win) -> void {
			auto* data = data_cast(win);
		
			warn_internal("Closing...");

			WindowCloseEvent ev;
			data->event_callback(ev);
		});

		glfwSetKeyCallback(window, [](auto* win, int key, int code, int action, int mods){
			auto* data = data_cast(win);

			switch(action) {
				case GLFW_PRESS:{ 
					KeyPressedEvent ev(key, 0);
					data->event_callback(ev);
					break;
				}
				case GLFW_RELEASE:{
					KeyReleasedEvent ev(key);
					data->event_callback(ev);
					break;
				}
				case GLFW_REPEAT:{
					KeyPressedEvent ev(key, 1);
					data->event_callback(ev);
					break;
				}
				default:
					info_internal("Unsupported keyboard action!");
					break;
			}
		});

		glfwSetCharCallback(window, [](auto* win, unsigned code){
			auto* data = data_cast(win);
			KeyTypedEvent ev(code);
			data->event_callback(ev);
		});

		glfwSetMouseButtonCallback(window, [](auto* win, int button, int action, int mods){
			auto* data = data_cast(win);

			switch(action) {
				case GLFW_PRESS:{
					MouseButtonPressedEvent ev(button);
					data->event_callback(ev);
					break;
				}
				case GLFW_RELEASE:{
					MouseButtonReleasedEvent ev(button);
					data->event_callback(ev);
					break;
				}
				default:
					info_internal("Unsupported mouse action!");
					break;
			}
		});

		glfwSetScrollCallback(window, [](auto* win, double x_off, double y_off){
			auto* data = data_cast(win);

			MouseScrolledEvent ev(x_off, y_off);
			data->event_callback(ev);
		});

		glfwSetCursorPosCallback(window, [](auto* win, double x, double y){
			auto* data = data_cast(win);
		
			MouseMovedEvent ev(x, y);
			data->event_callback(ev);
		});
	}

	void WindowsWindow::destroy() {
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