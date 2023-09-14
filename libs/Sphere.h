#pragma once
#include "Shape.h"

class Sphere : public Shape {
    public:
        Sphere();

    private:
        void BuildVerticesSmooth();

        GLfloat m_readius;
        GLuint m_sector, m_stack;

        std::vector<GLfloat> m_vertices;
        std::vector<GLfloat> m_normals;
        std::vector<GLfloat> m_texCoords;
};