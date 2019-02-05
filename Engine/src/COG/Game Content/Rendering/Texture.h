#pragma once

#include "precomp/precomp.h"





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
		 void unbind() const;

		 inline int width() const { return m_width; }
		 inline int height() const { return m_height; }
	};

}
