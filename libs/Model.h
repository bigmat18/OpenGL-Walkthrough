#include <iostream>
#include <vector>

#include "Mesh.h"
#include "Texture2D.h"


#ifndef MODEL_H
#define MODEL_H

class Model {
    public:
        Model(char *path);
        void Draw(class Shader &shader);
    private:
        std::vector<class Mesh*> m_meshes;
        std::string m_directory;

        void LoadModel(std::string path);
        // void ProcessNode(aiNode *node, const aiScene *scene);
        // Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
        // std::vector<Tex> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif