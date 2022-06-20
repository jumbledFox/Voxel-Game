#include "Shader.hpp"

namespace gl {
	Shader::Shader(const char* vertexPath, const char* fragmentPath) {
		// -- Load shaders -- //

		// Variables
		struct ShaderVars {
			std::string name;
			int shaderType;
			const char* path;
			std::string code_string;
			const char* code_cstr;
			std::ifstream file;
			unsigned int shader;
		};

		ShaderVars shaders[] = {
			{ "Vertex", GL_VERTEX_SHADER, vertexPath },
			{ "Fragment", GL_FRAGMENT_SHADER, fragmentPath }
		};


		// For both shaders, fragment and vertex:
		for (int i = 0; i < 2; i++) {
			// Ensure ifstream can throw exceptions
			shaders[i].file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			try {
				// Open file
				shaders[i].file.open(shaders[i].path);

				// Read file buffer content into stream
				std::stringstream stream;
				stream << shaders[i].file.rdbuf();

				// Close file handler
				shaders[i].file.close();
				// Convert stream to string
				shaders[i].code_string = stream.str();
				shaders[i].code_cstr = shaders[i].code_string.c_str();
			}
			catch (std::ifstream::failure& e) {
				std::cerr << "Error::Shader - File_Not_Succesfully_Read " << e.what() << "\n";
				exit(-1);
			}
			shaders[i].shader = glCreateShader(shaders[i].shaderType);
			glShaderSource(shaders[i].shader, 1, &shaders[i].code_cstr, NULL);
			glCompileShader(shaders[i].shader);
			checkCompileErrors(shaders[i].shader, shaders[i].name);
		}

		// Create the shader program
		ID = glCreateProgram();
		glAttachShader(ID, shaders[0].shader); // Attach vertex
		glAttachShader(ID, shaders[1].shader); // Attach fragment
		glLinkProgram(ID);
		checkCompileErrors(ID, "Program");

		// Delete shaders - already linked; no longer necessary
		glDeleteShader(shaders[0].shader);
		glDeleteShader(shaders[1].shader);
	}


	void Shader::use() {
		glUseProgram(ID);
	}


	unsigned int Shader::getUniform(const std::string& name) {
		return glGetUniformLocation(ID, name.c_str());
	}



	void Shader::checkCompileErrors(unsigned int shader, std::string type) {
		int success;
		char infolog[1024];
		if (type != "Program") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, infolog);
				std::cerr << "Error::Shader Compilation Error of type: " << type << "\n" << infolog << "\n";
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, infolog);
				std::cerr << "Error::Program Linking Error of type: " << type << "\n" << infolog << "\n";
			}
		}
	}
}
