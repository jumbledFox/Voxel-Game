#include "vertex_array.hpp"


gl::VertexArray::VertexArray() {
	create();
}

void gl::VertexArray::bind() const {
	glBindVertexArray(m_ID);
}


void gl::VertexArray::create() {
	if (!m_ID)
		glGenVertexArrays(1, &m_ID);
}

void gl::VertexArray::destroy(){
	glDeleteVertexArrays(1, &m_ID);
	glDeleteBuffers(m_bufferObjects.size(), m_bufferObjects.data());

	m_bufferObjects.clear();
	m_ID = 0;
	m_indicesCount = 0;
}


void gl::VertexArray::draw(GLenum drawMode) const {
	bind();
	glDrawElements(drawMode, m_indicesCount, GL_UNSIGNED_INT, 0);
}


void gl::VertexArray::addVertexBuffer(const std::vector<GLfloat>& vertices, const BufferLayoutList& layoutList){
	bind();

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

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

void gl::VertexArray::addIndexBuffer(const std::vector<GLuint>& indices){
	bind();

	GLuint elementBuffer;
	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	m_bufferObjects.push_back(elementBuffer);
	m_indicesCount = indices.size();
}