#include "precomp/precomp.h"
#include "RenderResourceManager.h"

namespace COG {

	using RRM = RenderResourceManager;

	std::unordered_map<std::string, std::shared_ptr<Model>> RRM::models_loaded{};
	std::unordered_map<std::string, std::shared_ptr<Shader>> RRM::shaders_loaded{};
	std::unordered_map<std::string, std::shared_ptr<Texture>> RRM::textures_loaded{};

	void RRM::load_model(const std::string& source, const std::string& name) {
		models_loaded.emplace(name, std::make_shared<Model>(source));
	}
	void RRM::load_shader(const std::string& source, const std::string& name) {
		shaders_loaded.emplace(name, std::make_shared<Shader>(source));
	}
	void RRM::load_texture(const std::string& source, const std::string& name) {
		textures_loaded.emplace(name, std::make_shared<Texture>(source));
	}

	std::shared_ptr<Model> RRM::get_model(const std::string& name) {
		return models_loaded.at(name);
	}
	std::shared_ptr<Shader> RRM::get_shader(const std::string& name) {
		return shaders_loaded.at(name);
	}
	std::shared_ptr<Texture> RRM::get_texture(const std::string& name) {
		return textures_loaded.at(name);
	}

	size_t RRM::unload_model(const std::string& name) {
		return models_loaded.erase(name);
	}
	size_t RRM::unload_shader(const std::string& name) {
		return shaders_loaded.erase(name);
	}
	size_t RRM::unload_texture(const std::string& name) {
		return textures_loaded.erase(name);
	}

}