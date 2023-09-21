#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh(std::vector<Vertex*> vertices) : m_vertices(vertices) 
{
    this->SetupMesh();
}

Mesh::~Mesh() {
    delete this->VAO;
    delete this->VBO;
    
    for(auto vertice : this->m_vertices)
        delete vertice;
}

void Mesh::SetupMesh() {
    std::vector<float> vertices;
    for(auto el : this->m_vertices) {
        vertices.push_back(el->Position.x);
        vertices.push_back(el->Position.y);
        vertices.push_back(el->Position.z);

        vertices.push_back(el->Normal.x);
        vertices.push_back(el->Normal.y);
        vertices.push_back(el->Normal.z);

        vertices.push_back(el->TexCoords.x);
        vertices.push_back(el->TexCoords.y);
    }
    this->size = vertices.size();
    this->VAO = new VertexArray();
    this->VBO = new VertexBuffer(&vertices[0], vertices.size() * sizeof(float));

    VertexBufferLayout layout = VertexBufferLayout();
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);

    this->VAO->AddBuffer(*this->VBO, layout);
}

void Mesh::Draw() {
    this->VAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, this->size / 8);
    glBindVertexArray(0);
}
