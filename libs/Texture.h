#include <GL/glew.h>
#include <string>

#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
    protected:
        GLuint rendererID;
        GLint width, height, BPP;
        unsigned char *localBuffer;

    public:
        enum Type {
            diffuse = 0,
            specular = 1,
            none = 2
        } type;

        Texture(int type = 3);
        virtual ~Texture();

        virtual void Bind(GLuint slot) const = 0;
        virtual void Unbind() const = 0;

        int GetWidth() const { return this->width; }
        int GetHeight() const { return this->height; }

        GLuint GetID() const { return this->rendererID; }

        void SetFlipVerticallyOnLoad(bool value = true);
        void LoadImageBuffer(char const *string);
        void FreeImageBuffer();
};

#endif