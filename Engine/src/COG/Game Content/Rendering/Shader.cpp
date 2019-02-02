#include "precomp/precomp.h"
#include "Shader.h"

#include "COG/Utils/TextUtil.h"

namespace COG {

	Shader::Shader(const std::string& filename) {
		auto source = parse(filename);
		shader_id = create(source);

		info_internal("Shader created from " + filename);
	}

	int Shader::uniform_loc(const std::string& name) {
		const auto got = uniform_cache.find(name);

		if(got != uniform_cache.end()) {
			return got->second;
		}

		GLCALL(int location = glGetUniformLocation(shader_id, name.c_str()));
		COG_ASSERT_INTERNAL(location != -1);

		uniform_cache[name] = location;

		return location;
	}

	void Shader::setUniform1f(const std::string & name, float val) {
		GLCALL(glUniform1f(uniform_loc(name), val));
	}

	void Shader::setUniform1i(const std::string & name, int val) {
		GLCALL(glUniform1i(uniform_loc(name), val));
	}

	void Shader::setUniform4f(const std::string& name, float a, float b, float c, float d) {
		GLCALL(glUniform4f(uniform_loc(name), a, b, c, d));
	}

	void Shader::setUniformMat4f(const std::string & name, const glm::mat4 & matrix) {
		GLCALL(glUniformMatrix4fv(uniform_loc(name), 1, GL_FALSE, &matrix[0][0]));
	}

	ShaderProgramSource Shader::parse(const std::string& file_path) {
		using namespace std;
		vector<string> shaderText;
		if(!loadTextFromFile(file_path, shaderText)) {
			error_internal("Could not find file " + file_path);
			throw "SHADER NOT FOUND";
		}

		enum READ_MODE : short {
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		} current = READ_MODE::NONE;

		stringstream shaders[2];
		for(const auto& line : shaderText) {
			if(line.find("#shader") != string::npos) {
				if(line.find("vertex") != string::npos) {
					current = READ_MODE::VERTEX;
				} else if(line.find("fragment") != string::npos) {
					current = READ_MODE::FRAGMENT;
				}
			} else {
				shaders[current] << line << endl;

				if(line.find("version") != string::npos) {
					if(current == READ_MODE::VERTEX) {
						cout << "Vertex shader using GLSL Version " << line.substr(9) << endl;
					} else if(current == READ_MODE::FRAGMENT) {
						cout << "Fragment shader using GLSL Version " << line.substr(9) << endl;
					}
				}
			}
		}

		return ShaderProgramSource{
			shaders[READ_MODE::FRAGMENT].str(), shaders[READ_MODE::VERTEX].str()
		};
	}

	unsigned Shader::compile(unsigned type, const std::string& source) {
		auto id = glCreateShader(type);

		/*
		This points to the same section of data as the source string.
		It will be deleted with the struct.
		*/
		const auto src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if(result == GL_FALSE) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			auto message = new char[length];
			glGetShaderInfoLog(id, length, &length, message);
			std::cerr << "Compilation error in the " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << std::endl << message << std::endl;
			delete[] message;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	unsigned Shader::create(const ShaderProgramSource& source) {
		auto program = glCreateProgram();
		auto vs = compile(GL_VERTEX_SHADER, source.vertex);
		auto fs = compile(GL_FRAGMENT_SHADER, source.fragment);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
}