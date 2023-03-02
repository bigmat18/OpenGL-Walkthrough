#pragma once
#include "Shape.h"
#include <GL/glew.h>
#include <vector>

#ifndef CUBE_H
#define CUBE_H

class Cube : public Shape {
    public:
        Cube(std::vector<GLfloat> colors, GLfloat side = 1.0f);

    private:
        GLfloat side;
        void buildShape();
};


#endif