#pragma once

#include "precomp/precomp.h"

#include "Core.h"

namespace COG {

	struct WindowDetails {
		std::string title;
		unsigned height, width;

		WindowDetails(const std::string& name = "Test Window Please Ignore", 
					  unsigned wide = 800, unsigned high = 600) 
					 :title(name), width(wide), height(high) {}
	};

	class COG_API Window{
		
		protected:
		WindowDetails details;
		bool vsync_on;
		
		public:
		
		virtual ~Window(){}
		virtual void set_vsync(bool enable = true) = 0;
		virtual void on_update() = 0;

		using callback = std::function<void()>;
		virtual void set_callback(const callback& callback)=0;

		static std::unique_ptr<Window> create(const WindowDetails& details = WindowDetails());
		
		inline unsigned width() const noexcept { return details.width; }
		inline unsigned height() const noexcept { return details.height; }
		inline bool vsync() const noexcept { return vsync_on; }
	};

}
