#include "Texture2D.h"
#include <GL/glew.h>

Texture2D::Texture2D(const std::string &path, int type) : Texture(type), 
                                                          filePath(path)
{
    this->SetFlipVerticallyOnLoad();
    this->LoadImageBuffer(this->filePath.c_str());
    glGenTextures(1, &this->rendererID);
    glBindTexture(GL_TEXTURE_2D, this->rendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (this->localBuffer) this->FreeImageBuffer();
}

Texture2D::~Texture2D() { glDeleteTextures(1, &this->rendererID); }

void Texture2D::Bind(GLuint slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, this->rendererID);
}

void Texture2D::Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }