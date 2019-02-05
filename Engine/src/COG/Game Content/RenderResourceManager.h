#pragma once

#include "precomp/precomp.h"

#include <unordered_map>

#include "Model.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"

namespace COG {

	class RenderResourceManager {
		public:

		COG_API static void load_model(const std::string& source, const std::string& name);
		COG_API static void load_shader(const std::string& source, const std::string& name);
		COG_API static void load_texture(const std::string& source, const std::string& name);
		
		COG_API static std::shared_ptr<Model> get_model(const std::string& name);
		COG_API static std::shared_ptr<Shader> get_shader(const std::string& name);
		COG_API static std::shared_ptr<Texture> get_texture(const std::string& name);
		
		COG_API static size_t unload_model(const std::string& name);
		COG_API static size_t unload_shader(const std::string& name);
		COG_API static size_t unload_texture(const std::string& name);

		private:
		static std::unordered_map<std::string, std::shared_ptr<Model>> models_loaded;
		static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders_loaded;
		static std::unordered_map<std::string, std::shared_ptr<Texture>> textures_loaded;
	};

}