#include "precomp/precomp.h"
#include "VertexBufferLayout.h"

#include "glad/glad.h"

namespace COG{
	
	unsigned VertexElement::size_of_type(unsigned type) {
		switch(type) {
			case GL_FLOAT:
				return sizeof(GLfloat);
			case GL_UNSIGNED_BYTE:
				return sizeof(GLubyte);
			case GL_UNSIGNED_INT:
				return sizeof(GLuint);
			default:
				COG_ASSERT_INTERNAL(false, "Vertex type not supported!");
				return 0;
		}
	}

	template<>
	void VertexBufferLayout::push<float>(unsigned count) {
		m_elements.emplace_back(GL_FLOAT, count, false);
		m_stride += VertexElement::size_of_type(GL_FLOAT) * count;
	}

	template<>
	void VertexBufferLayout::push<unsigned>(unsigned count) {
		m_elements.emplace_back(GL_UNSIGNED_INT, count, false);
		m_stride += VertexElement::size_of_type(GL_UNSIGNED_INT) * count;
	}

	template<>
	void VertexBufferLayout::push<unsigned char>(unsigned count) {
		m_elements.emplace_back(GL_UNSIGNED_BYTE, count, false);
		m_stride += VertexElement::size_of_type(GL_UNSIGNED_BYTE) * count;
	}
}