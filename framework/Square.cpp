#include "Square.h"
#include "VertexBuffer.h"

Square::Square() {}

Square::~Square() {}

void Square::InitShape() {
    GLfloat positions[] = {
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0,
        0.5, 0.5, 0.0,
        -0.5, 0.5, 0.0
    };
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    this->VBO = VertexBuffer(positions, 12 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    this->VAO.AddBuffer(this->VBO, layout);
    this->EBO = IndexBuffer(indices, 6);
}