#pragma once
#include <GL/glew.h>

#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer {
    private:
        GLuint VBO;
        unsigned int size;
    public:
        VertexBuffer(const void* data, GLuint size);
        ~VertexBuffer();

        unsigned int GetSize() const { return this->size; }
        void Bind() const;
        void Unbind() const;
    
};

#endif