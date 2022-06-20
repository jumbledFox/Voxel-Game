#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace gl {
	class Shader {
	public:
		// The ID of the program
		unsigned int ID;

		// Constructor - Reads and builds the shader
		Shader(const char* vertexPath, const char* fragmentPath);

		// Activates the shader
		void use();

		// -- Uniforms -- //
		// Gets a uniform location from a given name
		unsigned int getUniform(const std::string& name);
	private:
		// Check for compile errors
		void checkCompileErrors(unsigned int shader, std::string type);
	};
}