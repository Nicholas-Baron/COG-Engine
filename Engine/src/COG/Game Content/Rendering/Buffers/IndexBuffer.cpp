#include "precomp/precomp.h"
#include "IndexBuffer.h"

#include "COG/Log.h"
#include "../RenderUtil.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

namespace COG {

	unsigned IndexBuffer::inst = 0;

	IndexBuffer::IndexBuffer(unsigned * data, unsigned count) : m_count(count) {
		COG_ASSERT_INTERNAL(sizeof(unsigned) == sizeof(GLuint));
		COG_ASSERT_INTERNAL(m_count > 0);

		GLCALL(glGenBuffers(1, &renderer_id));
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
		GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned), data, GL_STATIC_DRAW));
		inst++;
	}

	IndexBuffer::~IndexBuffer() {
		
		if(glfwGetCurrentContext() != nullptr) {
			GLCALL(glDeleteBuffers(1, &renderer_id));
			inst--;
		}
	}

	void IndexBuffer::bind() const { 
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
	}

	void IndexBuffer::unbind() const { 
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}