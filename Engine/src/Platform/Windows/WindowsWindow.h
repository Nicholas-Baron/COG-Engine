#pragma once

#include "COG/Window.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace COG {

	class WindowsWindow : public Window {
		public:
		WindowsWindow(const WindowDetails& details);
		virtual ~WindowsWindow();

		virtual void on_update() override;
		virtual void set_vsync(bool enable = true) override;

		private:
		GLFWwindow* window;
	};

}