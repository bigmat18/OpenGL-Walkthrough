#include "Cube.h"
#include "VertexBuffer.h"
#include <iostream>

Cube::Cube(GLfloat side, const char* vertexPath, const char* fragmentPath) : Shape(vertexPath, fragmentPath), 
                                                                             side(side) 
{ this->BuildShape(); }

void Cube::BuildShape() {
    GLfloat positions[] = {
        -this->side, -this->side, this->side,
        this->side, -this->side, this->side,
        -this->side, this->side, this->side,
        this->side, this->side, this->side,
        -this->side, -this->side, -this->side,
        this->side, -this->side, -this->side,
        -this->side, this->side, -this->side,
        this->side, this->side, -this->side
    };
    
    GLuint indices[] = {
        0, 1, 2, 2, 1, 3,
        5, 4, 7, 7, 4, 6,
        4, 0, 6, 6, 0, 2,
        1, 5, 3, 3, 5, 7,
        2, 3, 6, 6, 3, 7,
        4, 5, 0, 0, 5, 1
    };

    this->VBO = new VertexBuffer(positions, 8 * 3 * sizeof(float));
    this->EBO = new IndexBuffer(indices, 36);

    VertexBufferLayout layout;
    layout.Push<float>(3);

    this->VAO->AddBuffer(*this->VBO, layout);
}