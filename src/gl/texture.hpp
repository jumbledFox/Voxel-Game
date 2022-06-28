#pragma once

#include <string>

#include <glad/glad.h>

#include "stb_image.h"

namespace gl {
	class Texture {
	public:
		// Constructor
		Texture() {}
		// Constructor, loads an image
		Texture(std::string path, ::GLint type);

		// Loads an image
		void loadImage(std::string path, ::GLint type);

		// Binds the image to a given slot
		void bind(unsigned int slot);
		// Binds the image to slot 0
		void bind();

	private:
		unsigned int m_ID = 0;
		int m_width = 0;
		int m_height = 0;
		int m_nrChannels = 0;
	};
}