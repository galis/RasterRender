//
// Created by galismac on 10/8/2022.
//

#ifndef RASTERIZATIONRENDER_MESH_H
#define RASTERIZATIONRENDER_MESH_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <ostream>
#include "Texture.h"

using namespace std;

#define MAX_BONE_INFLUENCE 4

class Vertex {
public:
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];

    glm::vec4 ClipPos, NormalPos;//cache

    friend ostream &operator<<(ostream &os, const Vertex &vertex);
};

class Mesh {
public:
    // mesh Data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    int facesNum;
    unsigned int VAO;

    Mesh(const vector<Vertex> &vertices, const vector<unsigned int> &indices);

    Mesh(const vector<Vertex> &vertices, const vector<unsigned int> &indices, const vector<Texture> &textures);

};


#endif //RASTERIZATIONRENDER_MESH_H
