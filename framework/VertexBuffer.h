#pragma once
#include <GL/glew.h>

#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer {
    private:
        GLuint mRendererID;
    public:
        VertexBuffer(const void* data, GLuint size);
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
    
};

#endif