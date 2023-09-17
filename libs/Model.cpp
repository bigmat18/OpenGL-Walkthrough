#include "Model.h"
#include "Shader.h"
#include "Mesh.h"

Model::Model(char *path) {
    this->LoadModel(path);
}

void Model::Draw(Shader &shader) {
    for(unsigned int i = 0; i < this->m_meshes.size(); i++) {
        this->m_meshes[i].Draw(shader);
    }
}

void Model::LoadModel(std::string path) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    this->m_directory = path.substr(0, path.find_first_of('/'));

    this->ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->m_meshes.push_back(this->ProcessMesh(mesh, scene));
    }

    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        this->ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Tex> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
        // process vertex positions, normals and texture coordinates
        glm::vec3 pos, norm, tex;

        pos.x = mesh->mVertices[i].x;
        pos.y = mesh->mVertices[i].y;
        pos.z = mesh->mVertices[i].z;
        vertex.Position = pos;

        norm.x = mesh->mNormals[i].x;
        norm.y = mesh->mNormals[i].y;
        norm.z = mesh->mNormals[i].z;
        vertex.Normal = norm;

        if (mesh->mTextureCoords[0]) {
            tex.x = mesh->mTextureCoords[0][i].x;
            tex.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = tex;
        } else vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Tex> diffuseMaps = this->LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        std::vector<Tex> specularMaps = this->LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Tex> Model::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<Tex> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        Tex texture;


        std::string filename = std::string(str.C_Str());
        filename = this->m_directory + '/' + filename;
        Texture2D tex = Texture2D(filename);

        texture.id = tex.GetID();
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
    }
    return textures;
}