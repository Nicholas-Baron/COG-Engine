#pragma once

namespace COG {
	class VertexBuffer {
		public:
		VertexBuffer(void* data, unsigned size);
		~VertexBuffer();

		void bind() const;
		inline void unbind() const;

		private:
		unsigned renderer_id;
	};
}