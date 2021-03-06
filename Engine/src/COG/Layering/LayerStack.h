#pragma once

#include "precomp/precomp.h"
#include "COG/Core.h"
#include "Layer.h"

namespace COG{
	class LayerStack {
		private:
		//Begin = bottom (render first), end = top (render last)
		std::vector<std::shared_ptr<Layer>> layers;

		using iterator = decltype(layers)::iterator;
		iterator insert;

		public:
		LayerStack() : insert(layers.begin()){}
		~LayerStack() {
			for(auto i = begin(); i != end(); i++) {
				(*i)->on_detach();
			}
		}

		COG_API void push_layer(std::shared_ptr<Layer> layer);
		COG_API void push_overlay(std::shared_ptr<Layer> layer);

		COG_API void remove_layer(std::shared_ptr<Layer> layer);
		COG_API void remove_overlay(std::shared_ptr<Layer> layer);

		COG_API iterator begin() { return layers.begin(); }
		COG_API iterator end() { return layers.end(); }
		
		void update_sweep(double delta);
	};

}