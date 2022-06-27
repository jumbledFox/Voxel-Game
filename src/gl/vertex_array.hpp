#pragma once

#include <vector>
#include <glad/glad.h>

namespace gl {
	struct BufferLayout {
		unsigned int type;
		unsigned int count;
		bool normalised;

	public:
		static unsigned int size(GLenum var) {
			switch (var) {
			case GL_UNSIGNED_BYTE:
				return 1;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_FLOAT:
				return 4;

			default:
				break;
			}
		}
	};
	using BufferLayoutList = std::vector<BufferLayout>;

	class VertexArray {
	public:
		// Buffer Layout stuff
		struct BufferElement {
			unsigned int type;
			unsigned int count;
			bool normalised;
		};

		class BufferLayout {
		private:
			std::vector<BufferElement> m_elements;
			unsigned int m_stride;

			// Actually add the info to the layout
			void AddToLayout(unsigned count, unsigned type, unsigned size, bool normalised = false) {
				m_elements.push_back({ type, count, normalised });
				m_stride += count * size;
			}
		public:
			// Make adding attributes easy
			template<typename T>
			void Push(unsigned int count) { }

			template<> void Push<float>(unsigned int count) { AddToLayout(count, GL_FLOAT, 4, false); }
			template<> void Push<unsigned>(unsigned int count) { AddToLayout(count, GL_UNSIGNED_INT, 4, false); }
			template<> void Push<unsigned char>(unsigned int count) { AddToLayout(count, GL_UNSIGNED_BYTE, 1, true); }
		};



		VertexArray();

		// Binds the vertex array
		void bind() const;

		// Generates the vertex array if one doesn't already exist
		void create();
		// Destroys the vertex array!!
		void destroy();

		// Draws the elements
		void draw(GLenum drawMode) const;

		// Add a vertex buffer, decode its data
		void addVertexBuffer(const std::vector<GLfloat>& vertices, const BufferLayoutList& layoutList);
		// Add indices / index buffer
		void addIndexBuffer(const std::vector<GLuint>& indices);

	private:
		std::vector<GLuint> m_bufferObjects;
		GLuint m_ID = 0;
		GLsizei m_indicesCount = 0;
	};
}