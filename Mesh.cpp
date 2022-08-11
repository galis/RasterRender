//
// Created by galismac on 10/8/2022.
//

#include "Mesh.h"

Mesh::Mesh(const vector<Vertex> &vertices, const vector<unsigned int> &indices) : vertices(vertices), indices(indices),
                                                                                  facesNum(indices.size() / 3) {}

Mesh::Mesh(const vector<Vertex> &vertices, const vector<unsigned int> &indices, const vector<Texture> &textures) : vertices(vertices),
                                                                                                                   indices(indices),
                                                                                                                   textures(textures),
                                                                                                                   facesNum(indices.size() / 3) {}

ostream &operator<<(ostream &os, const Vertex &vertex) {
    os << "Position: " << vertex.Position.x << "," << vertex.Position.y << vertex.Position.z << std::endl
       << " Normal: " << vertex.Normal.x << "," << vertex.Normal.y << "," << vertex.Normal.z << std::endl
       << " TexCoords: " << vertex.TexCoords.x << "," << vertex.TexCoords.y << std::endl;
    return os;
}
