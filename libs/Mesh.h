#include <glm/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture2D.h"

#ifndef MESH_H
#define MESH_H

typedef struct {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
} Vertex; 

class Mesh {
    public:
        std::vector<Vertex*> m_vertices;
        std::vector<GLuint> m_indices;
        std::vector<Texture2D*> m_textures;

        Mesh(std::vector<Vertex*> vertices);
        ~Mesh();
        
        void Draw(class Shader &shader);

    private:
        VertexArray* VAO;
        VertexBuffer* VBO;
        IndexBuffer* EBO;

        void SetupMesh();
};

#endif