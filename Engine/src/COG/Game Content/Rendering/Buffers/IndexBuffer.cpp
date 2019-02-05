#include "precomp/precomp.h"
#include "IndexBuffer.h"

#include "COG/Log.h"
#include "../RenderUtil.h"

#include "glad/glad.h"

namespace COG {
	IndexBuffer::IndexBuffer(unsigned * data, unsigned count) : m_count(count) {
		COG_ASSERT_INTERNAL(sizeof(unsigned) == sizeof(GLuint));
		COG_ASSERT_INTERNAL(m_count > 0);

		GLCALL(glGenBuffers(1, &renderer_id));
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
		GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned), data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer() {
		GLCALL(glDeleteBuffers(1, &renderer_id));
	}

	void IndexBuffer::bind() const { 
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
	}

	void IndexBuffer::unbind() const { 
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}