#include "Physics.h"




int Physics::HashCircle(GLfloat x, GLfloat y, int cols ,GLfloat spacing) {

	int xi = floor(x / spacing);
	int yi = floor(y / spacing);

	//+1 for 1-based array
	return yi * cols + xi;

}

void Physics::SpatialHashing(HashingArrayType& HashingArray, Circles &TheCircles, int CirclesNumber, GLuint width, GLuint height, GLfloat radius, size_t &cols, size_t & HashingArraySize)
{

	//Initializing members
	GLfloat spacing = 2*radius;

	cols = (int)(width/spacing)+1;
	size_t rows = (int)(height/spacing)+1;
    HashingArraySize = rows * cols;

	//Initializing size of HashingArray
    HashingArray.resize(HashingArraySize);

	//Hashing the circles based on their location on the grid
	for (size_t i = 0; i < CirclesNumber;i++) {

		int hashIndex = HashCircle(TheCircles[i]->getPosition().x, TheCircles[i]->getPosition().y,cols,spacing);

		HashingArray[hashIndex].push_back(TheCircles[i]);
	}

}

void Physics::CollisionSolveSpatial(HashingArrayType &HashingArray, int cols, int ArraySize, GLuint WindowWidth, GLuint WindowHeight, GLfloat radius) {

	const std::vector<int> neighborOffsets = {
	   1,           // Right
	   -1,          // Left  
	   -cols,       // Up
	   -cols + 1,   // Up Right
	   -cols - 1,   // Up Left
	   cols,        // Down
	   cols + 1,    // Down Right
	   cols - 1     // Down Left
	};

    for (size_t i = 0; i < ArraySize; i++) {
        //If there is circle inside this piece of grid
       
        if (!HashingArray[i].empty()) {

            for (auto it1 = HashingArray[i].begin(); it1 != HashingArray[i].end(); ++it1) {

                SolveCollisionWithFrames(*it1, WindowWidth, WindowHeight);

                auto it2 = it1;
                ++it2;

                for (; it2 != HashingArray[i].end(); ++it2) {
                    if (!(CalculateDistanceBetweenTwoPoints(**it1, **it2, radius) > (radius * 2))) {
                        SolveTwoVectors(*it1, *it2);
                    }
                }
            }



            for (int offset : neighborOffsets) {
                // Boundary checking logic (flag skipHorizontal)
                bool skipHorizontal = false;
                if (offset == 1) { // Right neighbor
                    skipHorizontal = (i % cols == cols - 1); // Skip if on right edge
                }
                else if (offset == -1) { // Left neighbor
                    skipHorizontal = (i % cols == 0); // Skip if on left edge
                }
                else if (offset == -cols + 1 || offset == cols + 1) { // Up-right or Down-right
                    skipHorizontal = (i % cols == cols - 1); // Skip if on right edge
                }
                else if (offset == -cols - 1 || offset == cols - 1) { // Up-left or Down-left
                    skipHorizontal = (i % cols == 0); // Skip if on left edge
                }

                if (!skipHorizontal) {
                    int neighborIndex = static_cast<int>(i) + offset;
                    if (neighborIndex >= 0 && neighborIndex < static_cast<int>(ArraySize)) {
                        if (!HashingArray[neighborIndex].empty()) {
                            for (auto c1 : HashingArray[i]) {
                                SolveCollisionWithFrames(c1, WindowWidth, WindowHeight);

                                for (auto c2 : HashingArray[neighborIndex]) {

                                    //if there is collision
                                    if (!(CalculateDistanceBetweenTwoPoints(*c1, *c2, radius) > (radius * 2))) {
                                        //If collided with frames
                                        SolveTwoVectors(c1, c2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Physics::SolveTwoVectors(Circle*& Circle1, Circle*& Circle2) {

    // Calculate velocity difference (v1 - v2)
    Vec2 velocityDifference;
    velocityDifference.x = Circle1->getVelocity().x - Circle2->getVelocity().x;
    velocityDifference.y = Circle1->getVelocity().y - Circle2->getVelocity().y;

    // Calculate position difference (x1 - x2)
    Vec2 positionDifference;
    positionDifference.x = Circle1->getPosition().x - Circle2->getPosition().x;
    positionDifference.y = Circle1->getPosition().y - Circle2->getPosition().y;

    // Calculate distance squared
    GLfloat distanceSquared = (positionDifference.x * positionDifference.x) +
        (positionDifference.y * positionDifference.y);

    // Avoid division by zero
    if (distanceSquared < 1e-6f) {
        return; // Circles are too close or at same position
    }

    // Calculate dot product of velocity difference and position difference
    GLfloat dotProduct = (velocityDifference.x * positionDifference.x) +
        (velocityDifference.y * positionDifference.y);

    // If objects are moving apart, no collision response needed
    if (dotProduct >= 0) {
        return;
    }

    // Calculate the collision factor
    GLfloat collisionFactor = dotProduct / distanceSquared;

    // Calculate velocity changes for both circles
    Vec2 velocityChange;
    velocityChange.x = collisionFactor * positionDifference.x;
    velocityChange.y = collisionFactor * positionDifference.y;

    // Circle1 velocity: v1' = v1 - [(v1-v2)·(x1-x2)/|x1-x2|²] × (x1-x2)

    Circle1->SetNewVelocity(Circle1->getVelocity().x - velocityChange.x,
        Circle1->getVelocity().y - velocityChange.y);

    // Circle2 velocity: v2' = v2 + [(v1-v2)·(x1-x2)/|x1-x2|²] × (x1-x2)
    Circle2->SetNewVelocity(Circle2->getVelocity().x + velocityChange.x,
        Circle2->getVelocity().y + velocityChange.y);


    GLfloat C1VMagnitude = sqrt((Circle1->getVelocity().x * Circle1->getVelocity().x) + (Circle1->getVelocity().y * Circle1->getVelocity().y));
    GLfloat C2VMagnitude = sqrt((Circle2->getVelocity().x * Circle2->getVelocity().x) + (Circle2->getVelocity().y * Circle2->getVelocity().y));
    
    if (C1VMagnitude > C2VMagnitude) {
        short temp = Circle2->getColor();
        Circle2->SetNewColor(Circle1->getColor());
        Circle1->SetNewColor(temp);
    }
    else { // Vice Versa
        short temp = Circle1->getColor();
        Circle1->SetNewColor(Circle2->getColor());
        Circle2->SetNewColor(temp);
    }

}

GLfloat Physics::CalculateDistanceBetweenTwoPoints(Circle &Circle1, Circle& Circle2, GLfloat radius) {
	GLfloat dx = Circle2.getPosition().x - Circle1.getPosition().x;
	GLfloat dy = Circle2.getPosition().y - Circle1.getPosition().y;
	GLfloat dist = std::sqrt(dx * dx + dy * dy);
	return dist;
}

void Physics::SolveCollisionWithFrames(Circle*& Circle1, GLuint WindowWidth, GLuint WindowHeight) {
    
    // Left/Right walls
    if (Circle1->getPosition().x >= WindowWidth - 51) {
        Circle1->SetNewPosition(WindowWidth - 51, Circle1->getPosition().y); // Fix position
        Circle1->SetNewVelocity((Circle1->getVelocity().x * -1), Circle1->getVelocity().y);
    }
    else if (Circle1->getPosition().x <= 51) {
        Circle1->SetNewPosition(51, Circle1->getPosition().y); // Fix position
        Circle1->SetNewVelocity((Circle1->getVelocity().x * -1), Circle1->getVelocity().y);
    }

    // Top/Bottom walls
    if (Circle1->getPosition().y >= WindowHeight - 51) {
        Circle1->SetNewPosition(Circle1->getPosition().x, WindowHeight - 51); // Fix position
        Circle1->SetNewVelocity(Circle1->getVelocity().x, (Circle1->getVelocity().y * -1));
    }
    else if (Circle1->getPosition().y <= 51) {
        Circle1->SetNewPosition(Circle1->getPosition().x, 51); // Fix position
        Circle1->SetNewVelocity(Circle1->getVelocity().x, (Circle1->getVelocity().y * -1));
    }
}

void Physics::SolveUsingSpatial(Circles & TheCircles, int CirclesNumber, GLuint width, GLuint height, GLfloat radius) {

    HashingArrayType HashingArray;
    size_t HashingArraySize;
    size_t cols;

    SpatialHashing(HashingArray,TheCircles, CirclesNumber, width, height, radius, cols, HashingArraySize);
    CollisionSolveSpatial(HashingArray,cols, HashingArraySize, width, height,radius);

}
