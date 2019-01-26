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

	class COG_API Window{
		
		public:
		
		virtual ~Window(){}
		virtual inline bool vsync() const noexcept = 0;
		virtual void set_vsync(bool enable = true) = 0;
		virtual void on_update() = 0;
		virtual void destroy() = 0;

		using callback = std::function<void(Event&)>;
		
		inline virtual void set_callback(const callback& callback) = 0;

		virtual inline unsigned width() const noexcept = 0;
		virtual inline unsigned height() const noexcept = 0;
	};

	template<typename T>
	inline std::unique_ptr<T> create_window(const WindowDetails& details){
		
		static_assert(std::is_base_of<Window, T>(), "T need to be a type of window!");

		return std::make_unique<T>(details);
	}

}
