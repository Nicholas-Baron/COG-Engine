#include "precomp/precomp.h"
#include "VertexBuffer.h"

#include "../RenderUtil.h"

COG::VertexBuffer::VertexBuffer(void * data, unsigned size) {
	GLCALL(glGenBuffers(1, &renderer_id));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

COG::VertexBuffer::~VertexBuffer() {
	GLCALL(glDeleteBuffers(1, &renderer_id));
}

void COG::VertexBuffer::bind() const {
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
}

inline void COG::VertexBuffer::unbind() const {
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
