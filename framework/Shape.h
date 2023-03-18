#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Shape {
    protected:
        VertexArray VAO;
        VertexBuffer VBO;
        IndexBuffer EBO;
        Shader shader;

    public:
        Shape();

        virtual void InitShape();
        void Draw() const {
            this->shader.use();
            this->VAO.Bind();
            this->EBO.Bind();
            glDrawElements(GL_TRIANGLES, this->EBO.GetCount(), GL_UNSIGNED_INT, 0);
        }
};