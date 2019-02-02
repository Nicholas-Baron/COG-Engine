#pragma once

#include "precomp/precomp.h"

#include "RenderUtil.h"

#include "glm/glm.hpp"
#include "glad/glad.h"

namespace COG {

	struct ShaderProgramSource {
		std::string fragment, vertex;
	};

	class Shader {
		private:
		unsigned shader_id;
		std::unordered_map<std::string, int> uniform_cache;
		
		ShaderProgramSource parse(const std::string& file_path);
		unsigned compile(unsigned type, const std::string& src);
		unsigned create(const ShaderProgramSource& src);
		int uniform_loc(const std::string& name);

		public:
		Shader(const std::string& filename);
		inline ~Shader() { glDeleteProgram(shader_id); }

		inline void use() const { GLCALL(glUseProgram(shader_id)); }

		void setUniform1f(const std::string& name, float val = 0);
		void setUniform1i(const std::string& name, int val = 0);
		void setUniform4f(const std::string& name, float a, float b, float c, float d);
		void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

		inline unsigned renderer_id() const { return m_shaderID; }
	};

}
