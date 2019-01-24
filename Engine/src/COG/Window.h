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
		
		public:
		
		virtual ~Window(){}
		virtual void set_vsync(bool enable = true) = 0;
		virtual void on_update() = 0;

		using callback = std::function<void()>;
		inline void set_callback(const callback& callback){ callfn = callback; }

		inline unsigned width() const noexcept { return details.width; }
		inline unsigned height() const noexcept { return details.height; }
		inline bool vsync() const noexcept { return vsync_on; }
	
		protected:
		WindowDetails details;
		bool vsync_on;
		callback callfn;
	};

	template<typename T>
	inline std::unique_ptr<T> create_window(const WindowDetails& details){
		
		static_assert(std::is_base_of<Window, T>(), "T need to be a type of window!");

		return std::make_unique<T>(details);
	}

}
