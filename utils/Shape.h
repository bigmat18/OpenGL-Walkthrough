#pragma once
#include <GL/glew.h>
#include <vector>

#ifndef SHAPE_H
#define SHAPE_H

class Shape {
    public:
        std::vector<GLuint> getIndices() const { return this->indices; }
        std::vector<GLfloat> getVertices() const { return this->vertices; }
        std::vector<GLfloat> getColors() const { return this->colors; }

    protected:
        std::vector<GLuint> indices;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> colors;

    private:
        virtual void buildShape() {};
};

#endif