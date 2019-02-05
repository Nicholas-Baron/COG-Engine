#include "precomp/precomp.h"

#include "Texture.h"

#include "COG/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace COG {

	Texture::Texture(const std::string& file, bool linear_filter, bool keep) 
		: path(file), local_buffer(nullptr), m_width(0), m_height(0), bpp(0), kept(keep) {

		stbi_set_flip_vertically_on_load(1);

		local_buffer = stbi_load(path.c_str(), &m_width, &m_height, &bpp, 4);

		GLCALL(glGenTextures(1, &id));
		GLCALL(glBindTexture(GL_TEXTURE_2D, id));

		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

		//[POSSIBLE] May later be a problem if loading multiple textures
		if(!linear_filter) {
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		} else {
			GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		}
		
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer));
		unbind();

		if(local_buffer && !kept) stbi_image_free(local_buffer);
	}

	Texture::~Texture() {
		GLCALL(glDeleteTextures(1, &id));
		if(kept) {
			delete[] local_buffer;
		}
	}

	void Texture::bind(unsigned slot) const {
		if(slot >= 32) {
			error_internal("Texture slot #" + std::to_string(slot) + " does not exist!");
		}
	
		GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
		GLCALL(glBindTexture(GL_TEXTURE_2D, id));
	}

}