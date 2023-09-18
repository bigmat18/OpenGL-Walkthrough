#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh(std::vector<Vertex*> vertices) : m_vertices(vertices)
{
    this->SetupMesh();
}

Mesh::~Mesh() {
    delete this->VAO;
    delete this->VBO;
    delete this->EBO;
    
    for(auto vertice : this->m_vertices)
        delete vertice;

    for(auto texture : this->m_textures)
        delete texture;
}

void Mesh::SetupMesh() {
    std::vector<float> vertices;
    for(auto el : this->m_vertices) {
        vertices.push_back(el->Position.x);
        vertices.push_back(el->Position.y);
        vertices.push_back(el->Position.x);

        vertices.push_back(el->Normal.x);
        vertices.push_back(el->Normal.y);
        vertices.push_back(el->Normal.x);

        vertices.push_back(el->TexCoords.x);
        vertices.push_back(el->TexCoords.y);
    }
    
    this->VAO = new VertexArray();
    this->VBO = new VertexBuffer(&vertices[0], vertices.size() * sizeof(float));
    this->EBO = new IndexBuffer(&this->m_indices[0], this->m_indices.size() * sizeof(unsigned int));

    VertexBufferLayout layout = VertexBufferLayout();
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);

    this->VAO->AddBuffer(*this->VBO, layout);
    this->VAO->Unbind();
}

void Mesh::Draw(Shader &shader) {
    // unsigned int diffuseNum = 1;
    // unsigned int specularNum = 1;

    // for (unsigned int i = 0; i < this->m_textures.size(); i++){
    //     if (this->m_textures[i]->type == 0) {
    //         shader.setInt(("material.texture_diffuse" + std::to_string(diffuseNum++)).c_str(), i);
    //     } else if (this->m_textures[i]->type == 1) {
    //         shader.setInt(("material.texture_specular" + std::to_string(specularNum++)).c_str(), i);
    //     }

    //     this->m_textures[i]->Bind(i);
    // }
    this->VAO->Bind();
}
