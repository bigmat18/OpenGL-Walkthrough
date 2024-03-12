#include "Sphere.h"

const float PI = acos(-1.0f);

Sphere::Sphere() {}

void Sphere::BuildVerticesSmooth(){
    float x, y, z, xy;
    float nx, ny, nz, lengthInv = 1.0f / this->m_readius;
    float s, t;

    float sectorStep = 2 * PI / this->m_sector;
    float stackStep = PI / this->m_stack;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= this->m_stack; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;
        xy = this->m_readius * cosf(stackAngle);
        z = this->m_readius * sinf(stackAngle);

        for (int j = 0; j <= this->m_sector; ++j) {
            sectorAngle = j * sectorStep;

            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            this->m_vertices.push_back(x);
            this->m_vertices.push_back(y);
            this->m_vertices.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            this->m_normals.push_back(nx);
            this->m_normals.push_back(ny);
            this->m_normals.push_back(nz);

            // vertex tex coord (s, t) range between [0, 1]
            s = (float)j / this->m_sector;
            t = (float)i / this->m_stack;
            this->m_texCoords.push_back(s);
            this->m_texCoords.push_back(t);
        }
    }
}