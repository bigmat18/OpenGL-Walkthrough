#include <glm/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>

#ifndef MESH_H
#define MESH_H

 typedef struct {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
} Vertex;

typedef struct {
    unsigned int id;
    std::string type;
    std::string path;
} Tex; 

class Mesh {
    public:
        std::vector<Vertex> m_vertices;
        std::vector<GLuint> m_indices;
        std::vector<Tex> m_textures;

        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Tex> textures);
        void Draw(class Shader &shader);

    private:
        GLuint VAO, VBO, EBO;

        void SetupMesh();
};

#endif