#pragma once

#include "Event.h"

namespace COG {

	class COG_API WindowResizeEvent : public Event {
		
		private:
		unsigned m_width, m_height;

		public:
		WindowResizeEvent(unsigned wide, unsigned high) noexcept 
			: m_width(wide), m_height(high) {}
		
		
		inline unsigned width() const noexcept { return m_width; }
		inline unsigned height() const noexcept { return m_height; }
		
		inline virtual std::string str() const override {
			  std::stringstream stream("WindowResizeEvent: ");
			  stream << m_width << ", " << m_height;
			  return stream.str();
		}
		
		inline static EventType static_type() noexcept { return EventType::WindowResize; } 
		inline virtual EventType type() const override { return static_type(); }
		inline virtual const char* name() const override { return "WindowResize"; }
		
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class COG_API WindowCloseEvent : public Event {
		public:
		WindowCloseEvent() noexcept {}
		
		inline static EventType static_type() noexcept { return EventType::WindowClose; }
		inline virtual EventType type() const override { return static_type(); }
		inline virtual const char* name() const override { return "WindowClose"; }
		
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class COG_API AppTickEvent : public Event {
		public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	
	class COG_API AppUpdateEvent : public Event {
		public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
	
	class COG_API AppRenderEvent : public Event {
		public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
