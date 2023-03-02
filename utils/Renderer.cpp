#include "Renderer.h"
#include "debugging.h"
#include "Shape.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>

Renderer::Renderer() {
    glGenVertexArrays(1, &this->VAO);
} 

void Renderer::addVertex(float values[], size_t sizeValues, GLuint index, GLuint number, GLuint size, GLuint offset){
    glBindVertexArray(this->VAO);
    this->VBOs.push_back(0);
    glGenBuffers(1, &this->VBOs.back());
    glBindBuffer(GL_ARRAY_BUFFER, this->VBOs.back());
    glBufferData(GL_ARRAY_BUFFER, sizeValues, values, GL_STATIC_DRAW);
    glVertexAttribPointer(index, number, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*)(size_t)offset);
    glEnableVertexAttribArray(index);
    glBindVertexArray(GL_NONE);
}

void Renderer::addVertexColored(float values[], 
                                size_t sizeValues,
                                GLuint indexPos, 
                                GLuint indexColor, 
                                GLuint numberPos, 
                                GLuint numberColor, 
                                GLuint size, 
                                GLuint posOffset, 
                                GLuint colorOffset){
    glBindVertexArray(this->VAO);
    this->VBOs.push_back(0);
    glGenBuffers(1, &this->VBOs.back());

    glBindBuffer(GL_ARRAY_BUFFER, this->VBOs.back());
    glBufferData(GL_ARRAY_BUFFER, sizeValues, values, GL_STATIC_DRAW);

    glVertexAttribPointer(indexPos, numberPos, GL_FLOAT, GL_FALSE, size * sizeof(float), (void *)(size_t)posOffset);
    glVertexAttribPointer(indexColor, numberColor, GL_FLOAT, GL_FALSE, size * sizeof(float), (void *)(size_t)colorOffset);

    glEnableVertexAttribArray(indexPos);
    glEnableVertexAttribArray(indexColor);

    glBindVertexArray(GL_NONE);
}

void Renderer::addIndeces(GLuint indices[], size_t size){
    glBindVertexArray(this->VAO);
    this->EBOs.push_back(0);
    glGenBuffers(1, &this->EBOs.back());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBOs.back());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    glBindVertexArray(GL_NONE);
}

void Renderer::addShape(Shape *shape){
    this->addVertex(&shape->getVertices()[0], 
                    shape->getVertices().size() * sizeof(float), 0);
    this->addVertex(&shape->getColors()[0],
                    shape->getColors().size() * sizeof(float), 1);
    this->addIndeces(&shape->getIndices()[0], 
                    shape->getIndices().size() * sizeof(int));
}

void Renderer::bind() {
    glBindVertexArray(this->VAO);
}