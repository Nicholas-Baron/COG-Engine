#pragma once

#include "Event.h"

namespace COG {

	class COG_API KeyEvent : public Event {
		public:
		
		inline int keycode() const noexcept { return code; }

		virtual inline int category_flags() const override final { 
			return EventCategoryKeyboard | EventCategoryInput;
		}

		protected:
		KeyEvent(int keycode) : code(keycode) {}

		int code;
	};

	class COG_API KeyPressedEvent : public KeyEvent {
		public:
		KeyPressedEvent(int keycode, unsigned repeatCount)
			: KeyEvent(keycode), repeats(repeatCount) {}

		inline unsigned repeat_count() const noexcept { return repeats; }

		inline virtual std::string str() const override {
			std::stringstream ss("KeyPressedEvent: ");
			ss << code << " (" << repeats << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

		inline static EventType static_type() noexcept { return EventType::KeyPressed; } 
		inline virtual EventType type() const override { return static_type(); }

		private:
		unsigned repeats;
	};

	class COG_API KeyReleasedEvent : public KeyEvent {
		public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		inline virtual std::string str() const override {
			return "KeyReleasedEvent: "	+ std::to_string(code);
		}

		EVENT_CLASS_TYPE(KeyReleased)

		inline static EventType static_type() noexcept { return EventType::KeyReleased; }
		inline virtual EventType type() const override { return static_type(); }
	};

	class COG_API KeyTypedEvent : public KeyEvent {
		public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		inline virtual std::string str() const override {
			return "KeyTypedEvent: " + std::to_string(code);
		}

		EVENT_CLASS_TYPE(KeyTyped)

		inline static EventType static_type() noexcept { return EventType::KeyTyped; }
		inline virtual EventType type() const override { return static_type(); }
	};

}