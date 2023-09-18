#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(int type) : rendererID(0),
                             width(0),
                             height(0),
                             BPP(0),
                             localBuffer(nullptr),
                             type(Texture::Type(type)) {};
Texture::~Texture() {};

void Texture::SetFlipVerticallyOnLoad(bool value) {
    stbi_set_flip_vertically_on_load(value);
}

void Texture::LoadImageBuffer(char const *string){
    this->localBuffer = stbi_load(string, &this->width, &this->height, &this->BPP, 4);
}

void Texture::FreeImageBuffer(){
    stbi_image_free(this->localBuffer);
}