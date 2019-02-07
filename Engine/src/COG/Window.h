#pragma once

#include "precomp/precomp.h"

#include "Core.h"
#include "Events/Event.h"

namespace COG {

	struct WindowDetails {
		std::string title;
		unsigned height, width;

		WindowDetails(const std::string& name = "Test Window Please Ignore", 
					  unsigned wide = 800, unsigned high = 600) 
					 :title(name), width(wide), height(high) {}
	};

	class Window{
		
		public:
		
		virtual ~Window(){}
		virtual inline bool vsync() const noexcept = 0;
		virtual void set_vsync(bool enable = true) = 0;
		virtual void on_update() = 0;
		virtual void destroy() = 0;

		using callback = std::function<void(Event&)>;
		inline virtual void set_callback(const callback& callback) = 0;

		inline virtual unsigned width() const noexcept = 0;
		inline virtual unsigned height() const noexcept = 0;

		inline double aspect_ratio() const noexcept { 
			return static_cast<double>(width()) / height();
		}
	};

}
