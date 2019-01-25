#pragma once

#include "Event.h"

namespace COG {

	class COG_API WindowResizeEvent : public Event {
		public:
		WindowResizeEvent(unsigned wide, unsigned high) noexcept
			: m_width(wide), m_height(high){}
		
		
		inline unsigned width() const { return m_width; }
		inline unsigned height() const { return m_height; }
		
		inline virtual std::string string() const override {
			  std::stringstream stream("WindowResizeEvent: ");
			  stream << m_width << ", " << m_height;
			  return stream.str();
		}
		
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		private:
		  unsigned m_width, m_height;
	};

	class COG_API WindowCloseEvent : public Event {
		public:
		WindowCloseEvent() noexcept {}
		
		EVENT_CLASS_TYPE(WindowClose)
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
