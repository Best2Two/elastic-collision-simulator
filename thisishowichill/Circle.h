#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <random>

class Circle
{

private:

	struct Vec {
		GLfloat x;
		GLfloat y;
	};
	Vec position; //x,y
	Vec velocity; //x,y

	static enum enColors {
		Red,Green,White,Pink
	};

	enColors CircleColor;

public:
	Circle(GLfloat maxXpos, GLfloat maxYpos, GLfloat maxvel, GLfloat minvel, short colornum);

	void SetNewPosition(float x, float y);
	void SetNewVelocity(float x, float y);
	void SetNewColor(short colornum);

	//Getters
	const Vec& getVelocity() const;
	const Vec& getPosition() const;
	short getColor();
};
