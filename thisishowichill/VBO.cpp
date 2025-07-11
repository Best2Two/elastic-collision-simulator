#include "VBO.h"

VBO::VBO() {
	glGenBuffers(1, &ID);
}

void VBO::Bind()
{
	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}

void VBO::IntroduceVertices(GLfloat *vertices, GLsizeiptr size) {

	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

}