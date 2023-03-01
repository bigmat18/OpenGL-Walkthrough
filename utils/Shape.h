#pragma once
#include <GL/glew.h>
#include <vector>

#ifndef SHAPE_H
#define SHAPE_H

class Shape {
    public:
    private:
        std::vector<GLuint> indices;
        std::vector<GLfloat> vertices;
};

#endif