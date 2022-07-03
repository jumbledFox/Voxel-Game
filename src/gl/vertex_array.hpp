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

		VertexArray();

		// Binds the vertex array
		void bind() const;

		// Generates the vertex array if one doesn't already exist
		void create();
		// Destroys the vertex array!!
		void destroy();

		// Draws the elements
		void draw(GLenum drawMode) const;

		// Add indices / index buffer
		void addIndexBuffer(const std::vector<GLuint>& indices);


		// Add a vertex buffer, decode its data
		template <typename T>
		void addVertexBuffer(const std::vector<T>& vertices, const BufferLayoutList& layoutList) {
			bind();

			GLuint vertexBuffer;
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);

			GLsizei stride = 0;
			for (const auto& layout : layoutList)
				stride += layout.count * layout.size(layout.type);

			unsigned c = 0;
			unsigned lastSize = 0;
			for (const auto& layout : layoutList) {
				glVertexAttribPointer(c, layout.count, layout.type, layout.normalised, stride, (void*)(lastSize));
				glEnableVertexAttribArray(c);

				c++;
				lastSize += layout.count * layout.size(layout.type);
			}

			m_bufferObjects.push_back(vertexBuffer);
		}

	private:
		std::vector<GLuint> m_bufferObjects;
		GLuint m_ID = 0;
		GLsizei m_indicesCount = 0;
	};
}
