#include "texture.hpp"

namespace gl {
	Texture::Texture(std::string path, ::GLint type) {
		loadImage(path, type);
	}

	void Texture::loadImage(std::string path, ::GLint type) {
		unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_nrChannels, 0);
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, type, m_width, m_height, 0, type, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}

	void Texture::bind(unsigned int slot) {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture::bind() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}