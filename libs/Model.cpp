#include "Model.h"
#include "Shader.h"
#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Model::Model(char *path) {
    this->LoadModel(path);
}

void Model::Draw(Shader &shader) {
    for(unsigned int i = 0; i < this->m_meshes.size(); i++) {
        this->m_meshes[i]->Draw(shader);
    }
}

void Model::LoadModel(std::string path) {
    // Assimp::Importer import;
    // const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    //     std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
    //     return;
    // }

    // this->m_directory = path.substr(0, path.find_first_of('/'));

    // this->ProcessNode(scene->mRootNode, scene);
    
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
        std::vector<Vertex *> vertices;

        for(const auto& index : shape.mesh.indices) {
            Vertex *vert = new Vertex;

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

// void Model::ProcessNode(aiNode *node, const aiScene *scene) {
//     for(unsigned int i = 0; i < node->mNumMeshes; i++){
//         aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
//         this->m_meshes.push_back(this->ProcessMesh(mesh, scene));
//     }

//     for(unsigned int i = 0; i < node->mNumChildren; i++) {
//         this->ProcessNode(node->mChildren[i], scene);
//     }
// }

// Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
//     std::vector<Vertex*> vertices;
//     std::vector<GLuint> indices;
//     std::vector<Texture2D*> textures;

//     for(unsigned int i = 0; i < mesh->mNumVertices; i++){
//         Vertex *vertex = new Vertex();

//         glm::vec3 pos, norm, tex;

//         pos.x = mesh->mVertices[i].x;
//         pos.y = mesh->mVertices[i].y;
//         pos.z = mesh->mVertices[i].z;
//         vertex->Position = pos;

//         norm.x = mesh->mNormals[i].x;
//         norm.y = mesh->mNormals[i].y;
//         norm.z = mesh->mNormals[i].z;
//         vertex->Normal = norm;

//         if (mesh->mTextureCoords[0]) {
//             tex.x = mesh->mTextureCoords[0][i].x;
//             tex.y = mesh->mTextureCoords[0][i].y;
//             vertex->TexCoords = tex;
//         } else vertex->TexCoords = glm::vec2(0.0f, 0.0f);

//         vertices.push_back(vertex);
//     }

//     for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
//         aiFace face = mesh->mFaces[i];
//         for (unsigned int j = 0; j < face.mNumIndices; j++)
//             indices.push_back(face.mIndices[j]);
//     }

//     if (mesh->mMaterialIndex >= 0) {
//         aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

//         std::vector<Texture2D*> diffuseMaps = this->LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//         textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

//         std::vector<Texture2D*> specularMaps = this->LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//         textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//     }

//     return Mesh(vertices, indices, textures);
// }

// std::vector<Texture2D*> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
//     std::vector<Texture2D*> textures;

//     for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
//         aiString str;
//         mat->GetTexture(type, i, &str);

//         std::string filename = this->m_directory + '/' + std::string(str.C_Str());
//         int type = typeName == "texture_diffuse" ? 0 : "texture_specular" ? 1 : 2;

//         Texture2D *texture = new Texture2D(filename, type);
//         textures.push_back(texture);
//     }

//     return textures;
// }