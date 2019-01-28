#pragma once

#include "COG/Events/Event.h"
#include "COG/Core.h"

namespace COG {
	class Layer {
		protected:
		std::string debug_name;
		
		public:
		COG_API Layer(const std::string& name = "Layer")
			: debug_name(name) {}
		virtual COG_API ~Layer() {}

		virtual void COG_API attach(){}
		virtual void COG_API detach(){}
		virtual void COG_API update(){}
		virtual void COG_API on_event(Event& e){}

		inline const COG_API std::string& name() const noexcept {
			return debug_name;
		}
	};
}
