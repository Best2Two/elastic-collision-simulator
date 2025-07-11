#pragma once
#include "Circle.h"
#include <iostream>

class Circles
{
public:
	Circles(size_t size, GLfloat x, GLfloat y, GLfloat vx, GLfloat vy);
	~Circles();
	Circle * operator[](size_t index) const;
	int NumCircles();

private:
	 int __globalVelocity=0;

	Circle ** __ptrCircles;
	size_t __size;

	GLfloat maxXpos;
	GLfloat maxYpos;
	GLfloat maxvel;
	GLfloat minvel;

};

