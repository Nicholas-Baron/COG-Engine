#pragma once

#include "Event.h"

#include "COG/Utils/Vec2d.h"

namespace COG {
	
	class COG_API MouseMovedEvent : public Event {
		public:
		MouseMovedEvent(double x, double y) noexcept
			: pos(x, y) {}

		inline const Vec2d& position() const noexcept { return pos; }
		inline double x_val() const noexcept { return pos.x_val(); }
		inline double y_val() const noexcept { return pos.y_val(); }

		inline virtual std::string str() const override final {
			return "MouseMovedEvent: " + std::to_string(pos);
		}

		EVENT_CLASS_TYPE(MouseMove)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		inline static EventType static_type() noexcept { return EventType::MouseMove; } 
		inline virtual EventType type() const override { return static_type(); }
		
		private:
		Vec2d pos;
	};

	class COG_API MouseScrolledEvent : public Event {
		
		public:
		MouseScrolledEvent(double x_offset, double y_offset) noexcept
			: offset_val(x_offset, y_offset) {}

		inline const Vec2d& offset() const noexcept {return offset_val; }
		inline double x_offset() const noexcept { return offset_val.x_val(); }
		inline double y_offset() const noexcept { return offset_val.y_val(); }

		inline virtual std::string str() const override {
			return "MouseScrolledEvent: " + std::to_string(offset_val);
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		
		inline static EventType static_type() noexcept { return EventType::MouseScroll; } 
		inline virtual EventType type() const override final { return static_type(); }
		
		private:
		Vec2d offset_val;
	};

	class COG_API MouseButtonEvent : public Event {
		public:
		inline int mouse_button() const noexcept { return button; }

		inline virtual int category_flags() const override final {
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

		inline static EventType static_type() noexcept { return EventType::MousePress; } 
		inline virtual EventType type() const override { return static_type(); }
	};

	class COG_API MouseButtonReleasedEvent : public MouseButtonEvent {
		public:
		MouseButtonReleasedEvent(int button) noexcept
			: MouseButtonEvent(button) {}

		inline virtual std::string str() const override {
			return "MouseButtonReleasedEvent: " + std::to_string(button);
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)

		inline static EventType static_type() noexcept { return EventType::MouseRelease; } 
		inline virtual EventType type() const override { return static_type(); }
	};
}
