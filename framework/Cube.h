#pragma once
#include "Shape.h"
#include <GL/glew.h>

class Cube : public Shape {
    public:
        Cube(GLfloat side, const char *vertexPath, const char *fragmentPath, const bool texture = false);
        void BuildShape();

    private:
        GLfloat side;
        bool texture;
};