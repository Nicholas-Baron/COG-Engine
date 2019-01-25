#pragma once

#include "Event.h"

namespace COG {
	
	class COG_API MouseMovedEvent : public Event {
		public:
		MouseMovedEvent(float x, float y) noexcept
			: mouseX(x), mouseY(y) {}

		inline float x() const noexcept { return mouseX; }
		inline float y() const noexcept { return mouseY; }

		inline virtual std::string string() const override {
			std::stringstream ss("MouseMovedEvent: ");
			ss << mouseX << ", " << mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		private:
		float mouseX, mouseY;
	};

	class COG_API MouseScrolledEvent : public Event {
		public:
		MouseScrolledEvent(float xOffset, float yOffset) noexcept
			: xOff(xOffset), yOff(yOffset) {}

		inline float xOffset() const noexcept { return xOff; }
		inline float yOffset() const noexcept { return yOff; }

		inline virtual std::string string() const override {
			std::stringstream ss("MouseScrolledEvent: ");
			ss << xOffset() << ", " << yOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		private:
		float xOff, yOff;
	};

	class COG_API MouseButtonEvent : public Event {
		public:
		inline int GetMouseButton() const noexcept { return button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		protected:
		MouseButtonEvent(int button_in) noexcept
			: button(button_in) {}

		int button;
	};

	class COG_API MouseButtonPressedEvent : public MouseButtonEvent {
		public:
		MouseButtonPressedEvent(int button)	noexcept
			: MouseButtonEvent(button) {}

		inline virtual std::string string() const override {
			return "MouseButtonPressedEvent: " + std::to_string(button);
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class COG_API MouseButtonReleasedEvent : public MouseButtonEvent {
		public:
		MouseButtonReleasedEvent(int button) noexcept
			: MouseButtonEvent(button) {}

		inline virtual std::string string() const override {
			return "MouseButtonReleasedEvent: " std::to_string(button);
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
