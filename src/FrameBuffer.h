#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

class FrameBuffer {
    public:
        FrameBuffer(bool m_isCube = false);
        ~FrameBuffer();

        void BindFrame(GLFWwindow *window);
        void UnbindFrame();

        void BindTex(GLuint slot = 0);
        void UnbindTex();

    private:
        GLuint m_width, m_height;
        GLuint m_FBO, m_depth;
        GLint m_sizeX, m_sizeY;
        bool m_isCube;
};


#endif