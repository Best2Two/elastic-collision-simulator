#pragma once
#include <iostream>
#include <vector>
#include <list>

#include "Circles.h"

class Physics
{	

public:
	  static struct Vec2 {
		  GLfloat x, y;
	  };

	  using HashingArrayType = std::vector<std::list<Circle*>>;


	 static void SpatialHashing(HashingArrayType& HashingArray, Circles& TheCircles, int CirclesNumber, GLuint width, GLuint height, GLfloat radius, size_t& cols, size_t& HashingArraySize);

	 static GLfloat CalculateDistanceBetweenTwoPoints(Circle& Circle1, Circle& Circle2, GLfloat radius);
	 static void SolveTwoVectors(Circle*& Circle1, Circle*& Circle2);
	 static void SolveCollisionWithFrames(Circle*& Circle1, GLuint WindowWidth, GLuint WindowHeight);

     static int HashCircle(GLfloat x, GLfloat y, int cols,GLfloat spacing);
	 
	 static void CollisionSolveSpatial(HashingArrayType& HashingArray, int cols, int ArraySize, GLuint WindowWidth, GLuint WindowHeight, GLfloat radius);
	 static void SolveUsingSpatial(Circles& TheCircles, int CirclesNumber, GLuint width, GLuint height, GLfloat radius);
};

