#include "Circle.h"


Circle::Circle(GLfloat maxXpos, GLfloat maxYpos, GLfloat maxvel, GLfloat minvel, short colornum) {

	position.x = 0 + static_cast<float>(rand()) / RAND_MAX * (maxXpos - 0);
	position.y = 0 + static_cast<float>(rand()) / RAND_MAX * (maxYpos - 0);
	velocity.x = minvel + static_cast<float>(rand()) / RAND_MAX * (maxvel - minvel);
	velocity.y = minvel + static_cast<float>(rand()) / RAND_MAX * (maxvel - minvel);

	CircleColor = enColors(colornum);

}

void Circle::SetNewPosition(float x, float y) {
	position.x = x;
	position.y = y;
};

void Circle::SetNewVelocity(float x, float y) {
	velocity.x = x;
	velocity.y = y;
};

void Circle::SetNewColor(short colornum) {
	CircleColor = (enColors)colornum;
}


//Getters
const Circle::Vec& Circle::getVelocity() const { return velocity; }
const Circle::Vec& Circle::getPosition() const { return position; }
short Circle::getColor() { return int(CircleColor); }


