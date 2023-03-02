#pragma once
#include <GL/glew.h>
#include "Shape.h"
#include <vector>

#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
    public:
        Renderer();

        void addVertex(float values[],
                       size_t sizeValues,
                       GLuint index,
                       GLuint number = 3,
                       GLuint size = 3,
                       GLuint offset = 0);

        void addVertexColored(float values[],
                              size_t sizeValues,
                              GLuint indexPos,
                              GLuint indexColor,
                              GLuint numberPos = 3,
                              GLuint numberColor = 3,
                              GLuint size = 6,
                              GLuint posOffset = 0,
                              GLuint colorOffset = 12);

        void addIndeces(GLuint indices[], size_t size);

        void addShape(class Shape *shape);

        void bind();

        int getShapesSize() const { return this->shapes.size(); }

        int getShapeVertexSize(unsigned int pos) const { return this->shapes[pos]->getIndices().size(); }

    private:
        GLuint VAO;
        std::vector<GLuint> VBOs;
        std::vector<GLuint> EBOs;
        std::vector<Shape*> shapes;
};

#endif