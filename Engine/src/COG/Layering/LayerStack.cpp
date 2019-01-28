#include "precomp/precomp.h"
#include "LayerStack.h"

 namespace COG{
	
	void LayerStack::push_layer(std::shared_ptr<Layer> layer){
		insert = layers.emplace(insert, layer);
		layer->attach();
	}

	void LayerStack::push_overlay(std::shared_ptr<Layer> overlay) {
		layers.emplace_back(overlay);
		overlay->attach();
	}
	
	void LayerStack::remove_layer(std::shared_ptr<Layer> layer) {

		auto loc = std::find(layers.begin(), layers.end(), layer);
		if(loc != layers.end()) {
			loc->operator->()->detach();
			layers.erase(loc);
			insert--;
		}
	}
	
	void LayerStack::remove_overlay(std::shared_ptr<Layer> overlay) {
	
		auto loc = std::find(layers.begin(), layers.end(), overlay);
		if(loc != layers.end()) {
			loc->operator->()->detach();
			layers.erase(loc);
		}
	}
	
	void LayerStack::update_sweep() {

		for(auto& layer : layers){
			layer.operator->()->update();
		}
	}
}