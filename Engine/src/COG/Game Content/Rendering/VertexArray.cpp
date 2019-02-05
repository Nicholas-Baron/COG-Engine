#include "precomp/precomp.h"
#include "VertexArray.h"

#include "RenderUtil.h"

COG::VertexArray::VertexArray() {
	GLCALL(glGenVertexArrays(1, &render_id));
	GLCALL(glBindVertexArray(render_id));
}

COG::VertexArray::~VertexArray() {
	GLCALL(glDeleteVertexArrays(1, &render_id));
}

void COG::VertexArray::add_buffer(const VertexBuffer * vb, const VertexBufferLayout * layout) {

	bind();
	vb->bind();
	const auto& elements = layout->elements();
	unsigned offset = 0;

	for(unsigned i = 0; i < elements.size(); i++) {
		const auto& e = elements[i];
		GLCALL(glEnableVertexAttribArray(i));
		GLCALL(glVertexAttribPointer(i, e.count, e.type, 
			   e.normalized ? GL_TRUE : GL_FALSE, layout->stride(), 
			   reinterpret_cast<const void*>(offset)));

		offset += e.count * VertexElement::size_of_type(e.type);
	}
}

inline void COG::VertexArray::bind() const {
	GLCALL(glBindVertexArray(render_id));
}

inline void COG::VertexArray::unbind() const {
	GLCALL(glBindVertexArray(0));
}
