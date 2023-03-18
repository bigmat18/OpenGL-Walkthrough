#pragma once
#include "Shape.h"
#include <GL/glew.h>

class Square : public Shape {
    public:
        Square();
        ~Square();
        void InitShape();
};