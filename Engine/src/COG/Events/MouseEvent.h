#pragma once

#include "Event.h"

#include "COG/Utils/Vec2d.h"

namespace COG {
	
	class COG_API MouseMovedEvent : public Event {
		public:
		MouseMovedEvent(float x, float y) noexcept
			: mouseX(x), mouseY(y) {}

		inline float x() const noexcept { return mouseX; }
		inline float y() const noexcept { return mouseY; }

		inline virtual std::string str() const override {
			std::stringstream ss("MouseMovedEvent: ");
			ss << mouseX << ", " << mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMove)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

			static EventType static_type() { return EventType::MouseMove; } 
			virtual EventType type() const override { return static_type(); }
		private:
		float mouseX, mouseY;
	};

	class COG_API MouseScrolledEvent : public Event {
		public:
		MouseScrolledEvent(double xOffset, double yOffset) noexcept
			: offset(xOffset, yOffset) {}

		inline float xOffset() const noexcept { return offset.x_val(); }
		inline float yOffset() const noexcept { return offset.y_val(); }

		inline virtual std::string str() const override {
			std::stringstream ss("MouseScrolledEvent: ");
			ss << xOffset() << ", " << yOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		static EventType static_type() { return EventType::MouseScroll; } 
		virtual EventType type() const override final { return static_type(); }
		private:
		Vec2d offset;
	};

	class COG_API MouseButtonEvent : public Event {
		public:
		inline int GetMouseButton() const noexcept { return button; }

		virtual inline int category_flags() const override final {
			return EventCategoryMouse | EventCategoryInput;
		}
		
		protected:
		MouseButtonEvent(int button_in) noexcept
			: button(button_in) {}

		int button;
	};

	class COG_API MouseButtonPressedEvent : public MouseButtonEvent {
		public:
		MouseButtonPressedEvent(int button)	noexcept
			: MouseButtonEvent(button) {}

		inline virtual std::string str() const override {
			return "MouseButtonPressedEvent: " + std::to_string(button);
		}

		EVENT_CLASS_TYPE(MousePress)

		static EventType static_type() { return EventType::MousePress; } 
		virtual EventType type() const { return static_type(); }
	};

	class COG_API MouseButtonReleasedEvent : public MouseButtonEvent {
		public:
		MouseButtonReleasedEvent(int button) noexcept
			: MouseButtonEvent(button) {}

		inline virtual std::string str() const override {
			return "MouseButtonReleasedEvent: " + std::to_string(button);
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

		static EventType static_type() { return EventType::MouseRelease; } 
		virtual EventType type() const override { return static_type(); }
	};
}
