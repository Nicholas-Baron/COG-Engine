#pragma once

#include "precomp/precomp.h"

#include "RenderUtil.h"

#include "glad/glad.h"

namespace COG {

	class Texture {
		private:
		unsigned id;
		std::string path;
		unsigned char* local_buffer;
		int m_width, m_height, bpp;
		bool kept;

		public:
		Texture(const std::string& path, bool linear_filter = false, bool keep_local = false);
		~Texture();

		 void bind(unsigned slot = 0) const;
		 inline void unbind() const { GLCALL(glBindTexture(GL_TEXTURE_2D, 0)); }

		 inline int width() const { return m_width; }
		 inline int height() const { return m_height; }
	};

}
