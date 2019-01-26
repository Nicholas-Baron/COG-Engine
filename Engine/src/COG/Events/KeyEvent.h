#pragma once

#include "Event.h"

namespace COG {

	template<EventType type>
	class COG_API KeyEvent : public Event<type> {
		public:
		
		inline int keycode() const noexcept { return code; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		protected:
		KeyEvent(int keycode) : code(keycode) {}

		int code;
	};

	class COG_API KeyPressedEvent : public KeyEvent<EventType::KeyPressed> {
		public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), repeats(repeatCount) {}

		inline int GetRepeatCount() const { return repeats; }

		inline virtual std::string str() const override {
			std::stringstream ss("KeyPressedEvent: ");
			ss << code << " (" << repeats << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
		private:
		int repeats;
	};

	class COG_API KeyReleasedEvent : public KeyEvent<EventType::KeyReleased> {
		public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		inline virtual std::string str() const override {
			return "KeyReleasedEvent: "	+ std::to_string(code);
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class COG_API KeyTypedEvent : public KeyEvent<EventType::KeyTyped> {
		public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		inline virtual std::string str() const override {
			return "KeyTypedEvent: " + std::to_string(code);
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}