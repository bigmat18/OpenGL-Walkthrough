#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(bool m_isCube) : m_width(1024),
                                          m_height(1024),
                                          m_isCube(m_isCube)
{
    int flag = this->m_isCube ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;

    glGenFramebuffers(1, &this->m_FBO);

    // create depth texture
    glGenTextures(1, &this->m_depth);
    glBindTexture(flag, this->m_depth);
    if(!this->m_isCube)
        glTexImage2D(flag, 0, GL_DEPTH_COMPONENT, this->m_width, this->m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    else {
        for (unsigned int i = 0; i < 6; ++i)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, this->m_width, this->m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
    glTexParameteri(flag, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(flag, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if(!this->m_isCube){
        glTexParameteri(flag, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(flag, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
        glTexParameterfv(flag, GL_TEXTURE_BORDER_COLOR, borderColor);
    } else {
        glTexParameteri(flag, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(flag, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(flag, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, this->m_FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, flag, this->m_depth, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer() { 
    if (this->m_FBO != 0)
        glDeleteFramebuffers(1, &this->m_FBO);

    if (this->m_depth != 0)
        glDeleteTextures(1, &this->m_depth);
}

void FrameBuffer::BindFrame(GLFWwindow *window) {
    glfwGetFramebufferSize(window, &this->m_sizeX, &this->m_sizeY);
    glViewport(0, 0, this->m_width, this->m_height);
    glBindFramebuffer(GL_FRAMEBUFFER, this->m_FBO);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::UnbindFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, this->m_sizeX, this->m_sizeY);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FrameBuffer::BindTex(GLuint slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(this->m_isCube ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, this->m_depth);
}

void FrameBuffer::UnbindTex() { glBindTexture(this->m_isCube ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, 0); }