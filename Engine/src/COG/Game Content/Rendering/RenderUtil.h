#pragma once

#include "precomp/precomp.h"

#include "COG/Log.h"

#include "glad/glad.h"

#define GLCALL(x) gl_clean_errors();x;\
COG::COG_ASSERT_INTERNAL(gl_check_error(#x, __FILE__, __LINE__))

inline void gl_clean_errors() { while(glGetError() != GL_NO_ERROR); }

inline bool gl_check_error(std::string_view func, std::string_view file, const unsigned line) {
	auto no_errors = true;
	while(auto error = glGetError()) {
		using namespace std;
		cout << "[OpenGL Error] #" << error << " from " << func << " in " << file << " on line " << line << endl;
		no_errors = false;
	}
	return no_errors;
}