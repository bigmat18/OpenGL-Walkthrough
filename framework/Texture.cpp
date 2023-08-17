#include "Texture.h"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string &path) : rendererID(0),
                                            filePath(path), 
                                            localBuffer(nullptr),
                                            width(0),
                                            height(0),
                                            BPP(0)
{
    stbi_set_flip_vertically_on_load(true);
    this->localBuffer = stbi_load(this->filePath.c_str(), &this->width, &this->height, &this->BPP, 4);
    GLenum format;
    if (this->BPP == 1)      format = GL_RED;
    else if (this->BPP == 3) format = GL_RGB;
    else if (this->BPP == 4) format = GL_RGBA;
    else;

    glGenTextures(1, &this->rendererID);
    glBindTexture(GL_TEXTURE_2D, this->rendererID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->localBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    if(this->localBuffer) stbi_image_free(this->localBuffer);
}

Texture::~Texture() { glDeleteTextures(1, &this->rendererID); }

void Texture::Bind(GLuint slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, this->rendererID);
}

void Texture::Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }