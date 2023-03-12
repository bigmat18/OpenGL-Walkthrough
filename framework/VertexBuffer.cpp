#include "VertexBuffer.h"
#include "Renderer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void* data, GLuint size){
    glGenBuffers(1, &this->mRendererID);
    glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer(){ glDeleteBuffers(1, &this->mRendererID); }

void VertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, mRendererID); }

void VertexBuffer::Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }