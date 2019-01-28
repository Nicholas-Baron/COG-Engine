#pragma once

#include "precomp/precomp.h"

#include "COG/Core.h"

namespace COG {

	enum struct EventType : unsigned {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MousePress, MouseRelease, MouseMove, MouseScroll
	 };

	enum EventCategory : unsigned {
		None = 0,
		EventCategoryApplication = bit(0),
		EventCategoryInput = bit(1),
		EventCategoryKeyboard = bit(2),
		EventCategoryMouse = bit(3),
		EventCategoryMouseButton = bit(4)
	};

#define EVENT_CLASS_TYPE(type) virtual const char* name() const override { return #type; } 	
#define EVENT_CLASS_CATEGORY(category) virtual int category_flags() const override { return category; }

	class COG_API Event {
		public:
		bool handled = false;

		virtual inline EventType type() const = 0;
		virtual const char* name() const { return "None"; }
		virtual int category_flags() const = 0;
		virtual inline std::string str() const { return name();  }
		
		inline operator std::string() const { return str(); }
		inline bool in_category(EventCategory category) const { 
			return category_flags() & category;
		}
	};

	class EventDispatcher {
		public:
		EventDispatcher(Event& e_in) : e(e_in) {}
		
		template<typename T>
		using EventFn = std::function<bool(T&)>;
		
		template<typename T>
		bool dispatch(EventFn<T> func){
			
			static_assert(std::is_base_of<Event, T>(), "Using EventDispatcher::dispatch on a non-Event child?");

			if(e.type() == T::static_type()) {
				e.handled = func(*reinterpret_cast<T*>(&e));
				return true;
			}
			
			return false;
		}

		private:
		Event& e;
	};

}

namespace std {
	
	inline std::string to_string(const COG::Event& e){
		return e.str();
	}
}

template<COG::EventType type>
inline std::ostream& operator<<(std::ostream& lhs, const COG::Event& rhs){
	return lhs << std::to_string(rhs);
}
