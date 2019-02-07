#pragma once

#include "precomp/precomp.h"

#include "COG/Core.h"

namespace COG {

	struct ShaderProgramSource {
		std::string fragment, vertex;
	};

	class Shader {
		private:
		unsigned shader_id;
		bool use_mvp;
		std::unordered_map<std::string, int> uniform_cache;
		
		ShaderProgramSource parse(const std::string& file_path);
		unsigned compile(unsigned type, const std::string& src);
		unsigned create(const ShaderProgramSource& src);
		
		public:
		Shader(const std::string& filename, bool mvp);
		~Shader();

		COG_API void use() const;

		COG_API void setUniform1f(const std::string& name, float val = 0);
		COG_API void setUniform1i(const std::string& name, int val = 0);
		COG_API void setUniform4f(const std::string& name, float a, float b, float c, float d);

		int uniform_loc(const std::string& name);
		inline bool uses_mvp() const noexcept { return use_mvp; }
		inline unsigned renderer_id() const { return shader_id; }
	};

}
