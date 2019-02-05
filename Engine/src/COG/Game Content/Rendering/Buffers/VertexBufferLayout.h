#pragma once

#include "COG/Log.h"

#include "glad/glad.h"

namespace COG {

	struct VertexElement {
		unsigned type, count;
		bool normalized;

		VertexElement(unsigned type_in, unsigned count_in, bool normed)	noexcept
			: type(type_in), count(count_in), normalized(normed) {}

		static unsigned size_of_type(unsigned type){
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
	};

	class VertexBufferLayout {
		private:
		std::vector<VertexElement> m_elements;
		unsigned m_stride = 0;
		
		public:
		
		template<typename T>
		void push(unsigned count){ 
			static_assert(false, "Unsupported type in VertexBufferLayout");
		}
		
		template<>
		void push<float>(unsigned count){
			m_elements.emplace_back(GL_FLOAT, count, false);
			m_stride += VertexElement::size_of_type(GL_FLOAT) * count;
		}

		template<>
		void push<unsigned>(unsigned count) {
			m_elements.emplace_back(GL_UNSIGNED_INT, count, false);
			m_stride += VertexElement::size_of_type(GL_UNSIGNED_INT) * count;
		}
		
		template<>
		void push<unsigned char>(unsigned count) {
			m_elements.emplace_back(GL_UNSIGNED_BYTE, count, false);
			m_stride += VertexElement::size_of_type(GL_UNSIGNED_BYTE) * count;
		}

		inline const std::vector<VertexElement>& elements() const noexcept { 
			return m_elements;
		}

		inline unsigned stride() const noexcept { return m_stride; }
	};

}
