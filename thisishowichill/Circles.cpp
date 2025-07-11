#include "Circles.h"

Circles::Circles(size_t size, GLfloat x, GLfloat y, GLfloat vx, GLfloat vy) : __size(size) {

    //init
    maxXpos = x;
    maxYpos = y;
    maxvel = vx;
    minvel = vy;
    srand(time(NULL));

    __ptrCircles = new Circle * [__size];
    // Initialize all pointers to new generated circles, I will make destructor to deallocate these circles once
    //the class instance is destroyed

    for (size_t i = 0; i < __size; i++) {
        //[] This may shows that CPP make an operator for pointers arithmetic using [];
        __ptrCircles[i] = new Circle(maxXpos,maxYpos,maxvel,minvel, rand() % 5);
    }

}


// Const version of [] operator
Circle* Circles::operator[](size_t index) const {
    if (index < __size) return __ptrCircles[index];
    throw std::out_of_range("index is out of range");
}

Circles::~Circles() {
    for (size_t i = 0; i < __size; i++) {
       delete __ptrCircles[i];
    }
    delete[] __ptrCircles;
}

int Circles::NumCircles() { return __size; };
