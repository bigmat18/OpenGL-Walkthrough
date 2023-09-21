#include <GL/glew.h>
#include <string>
#include "Texture.h"

#ifndef TEXTURE2D_H
#define TEXTURE2D_H

class Texture2D : public Texture {
    private:
        std::string filePath;
        bool m_isMesh;

    public:
        Texture2D(const std::string &path, bool isMesh = false);
        ~Texture2D();

        void Bind(GLuint slot = 0) const override;
        void Unbind() const override;
};

#endif