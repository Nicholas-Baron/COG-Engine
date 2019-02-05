#pragma once

#include "COG/Log.h"

namespace COG {

	struct VertexElement {
		unsigned type, count;
		bool normalized;

		VertexElement(unsigned type_in, unsigned count_in, bool normed)	noexcept
			: type(type_in), count(count_in), normalized(normed) {}

		static unsigned size_of_type(unsigned type);
	};

	class VertexBufferLayout {
		private:
		std::vector<VertexElement> m_elements;
		unsigned m_stride = 0;
		
		public:
		
		template<typename T>
		void push(unsigned count);
		
		inline const std::vector<VertexElement>& elements() const noexcept { 
			return m_elements;
		}

		inline unsigned stride() const noexcept { return m_stride; }
	};

}
