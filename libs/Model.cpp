#include "Model.h"
#include "Shader.h"
#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Model::Model(char *path) {
    this->LoadModel(path);
}

void Model::Draw() {
    for(unsigned int i = 0; i < this->m_meshes.size(); i++) {
        this->m_meshes[i]->Draw();
    }
}

void Model::LoadModel(std::string path) {
    tinyobj::ObjReader reader;
    tinyobj::ObjReaderConfig reader_config = tinyobj::ObjReaderConfig();
    reader_config.triangulate = true;

    if (!reader.ParseFromFile(path, reader_config)) {
        if (!reader.Error().empty())
            fprintf(stderr, "TinyObjReader: %s", reader.Error().c_str());
        exit(1);
    }

    if (!reader.Warning().empty()) {
        fprintf(stderr, "TinyObjReader: %s", reader.Warning().c_str());
    }

    auto attrib = reader.GetAttrib();
    auto shapes = reader.GetShapes();
      
    if(shapes.size() == 0) {
        fprintf(stderr, "No shapes found in object file %s\n", path.c_str());
        exit(1);
    }

    if(attrib.normals.size() == 0) {
        fprintf(stderr, "No normals found in object file %s\n", path.c_str());
        exit(1);
    }

    if(attrib.texcoords.size() == 0) {
        fprintf(stderr, "No texture coordinates found in object file %s\n", path.c_str());
        exit(1);
    }
    
    for(const auto& shape : shapes) {
        std::vector<Vertex*> vertices;

        for(const auto& index : shape.mesh.indices) {
            Vertex *vert = new Vertex();
            
            vert->Position.x = attrib.vertices[3 * index.vertex_index + 0];
            vert->Position.y = attrib.vertices[3 * index.vertex_index + 1];
            vert->Position.z = attrib.vertices[3 * index.vertex_index + 2];

            vert->Normal.x = attrib.normals[3 * index.normal_index + 0];
            vert->Normal.y = attrib.normals[3 * index.normal_index + 1];
            vert->Normal.z = attrib.normals[3 * index.normal_index + 2];

            vert->TexCoords.x = attrib.texcoords[2 * index.texcoord_index + 0];
            vert->TexCoords.x = attrib.texcoords[2 * index.texcoord_index + 1];

            vertices.push_back(vert);
        }
        this->m_meshes.push_back(new Mesh(vertices));
    }
}