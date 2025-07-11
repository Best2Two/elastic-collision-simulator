#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<fstream>
#include<sstream>

#include "Circle.h"

class Shaders {
private:
	static GLfloat lightblue[4];
	static GLfloat yellow[4];
	static GLfloat white[4];
	static GLfloat pink[4];
	static GLfloat red[4];

	static GLfloat* Colors[5];

	 int u_Color_location;
	 int u_Center_location;

public:
	Shaders(const char* vertexFile, const char* fragmentFile);
	

	GLuint ID;
	std::string get_file_contents(const char* filename);
	void Activate();
	void Delete();

	void LoadColor(short numColor);
	void LoadPosition(GLfloat x, GLfloat y);
	void LoadCirclePositionToBackBuffer(Circle *Circle1);

	void DrawPrimitive();
	
};