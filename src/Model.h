#include <iostream>
#include <vector>

#include "Mesh.h"
#include "Texture2D.h"


#ifndef MODEL_H
#define MODEL_H

class Model {
    public:
        Model(char *path);
        ~Model();
        
        void Draw();

    private:
        std::vector<class Mesh*> m_meshes;

        void LoadModel(std::string path);
};

#endif