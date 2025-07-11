#pragma once
#include <glad/glad.h>

class VBO
{
public:
	GLuint ID;
	VBO();

	void Bind();
	void Unbind();
	void Delete();
	void IntroduceVertices(GLfloat* vertices, GLsizeiptr size);
};

