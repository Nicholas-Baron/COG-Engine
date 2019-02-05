#pragma once

#include "Buffers/VertexBuffer.h"
#include "Buffers/VertexBufferLayout.h"

namespace COG {

	class VertexArray {
		private:
		unsigned render_id;
		
		public:
		VertexArray();
		~VertexArray();

		void add_buffer(const VertexBuffer* vb, const VertexBufferLayout* layout);
		inline void bind() const;
		inline void unbind() const;
	};

}
