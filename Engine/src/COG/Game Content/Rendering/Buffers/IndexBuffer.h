#pragma once

namespace COG {

	class IndexBuffer {
		public:
		IndexBuffer(unsigned* data, unsigned count);
		~IndexBuffer();

		void bind() const;
		void unbind() const;

		inline unsigned count() const noexcept { return m_count; }

		private:
		unsigned renderer_id; 
		unsigned m_count;
	};

}