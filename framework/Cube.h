#pragma once
#include "Shape.h"
#include <GL/glew.h>

class Cube : public Shape {
    public:
        Cube(GLfloat side, const char *vertexPath, const char *fragmentPath);
        void BuildShape();

    private:
        GLfloat side;
};