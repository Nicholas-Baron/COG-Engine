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
		COG_API virtual ~Layer() {}

		COG_API virtual void on_attach(){}
		COG_API virtual void on_detach(){}
		COG_API virtual void on_update(double delta){}
		COG_API virtual void on_event(Event& e){}

		COG_API inline const std::string& name() const noexcept {
			return debug_name;
		}
	};

	
}
