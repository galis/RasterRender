//
// Created by galismac on 10/8/2022.
//

#ifndef RASTERIZATIONRENDER_MODEL_H
#define RASTERIZATIONRENDER_MODEL_H


#include <string>
#include <ostream>
#include <vector>
#include "assimp_compat.h"
#include "Mesh.h"
#include "Texture.h"


using namespace std;

class Model {
private:
    bool loadStatus;
    string modelPath;
    vector<Mesh> meshs;

    void processNode(AiNode *node, const AiScene *scene);

    Mesh processMesh(AiMesh *mesh, const AiScene *scene);

public:
    Model(string &path);

    Model(string &&path);

    bool isLoad() const;

    bool load();

    const string &getPath() const;

    void setPath(const string &path);

    friend std::ostream &operator<<(std::ostream &os, const Model &model);

    const vector<Mesh> &getMeshs() const;
};


#endif //RASTERIZATIONRENDER_MODEL_H
