//
// Created by galismac on 10/8/2022.
//

#include "Model.h"
#include "Resource.h"
#include "Platform.h"
#include "assimp_compat.h"

bool Model::isLoad() const {
    return loadStatus;
}

bool Model::load() {
    if (!Resource::CheckPath(modelPath)) {
        return false;
    }
    Assimp::Importer importer;
    const AiScene *scene = importer.ReadFile(modelPath,
                                             aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        Platform::Debug("加载失败!");
        return false;
    }
    processNode(scene->mRootNode, scene);
    return true;
}

const string &Model::getPath() const {
    return modelPath;
}

void Model::setPath(const string &path) {
    modelPath = path;
}

Model::Model(string &path) : modelPath(path) {
}

Model::Model(string &&path) : modelPath(std::move(path)) {

}

void Model::processNode(AiNode *node, const AiScene *scene) {
    for (int i = 0; i < node->mNumMeshes; i++) {
        meshs.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));
    }
    for (int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(AiMesh *mesh, const AiScene *scene) {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        //处理位置
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        //处理法线
        if (mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        //处理纹理坐标
        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            //假设使用纹理坐标类型0
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        } else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
//    // process materials
//    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
//    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
//    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
//    // Same applies to other texture as the following list summarizes:
//    // diffuse: texture_diffuseN
//    // specular: texture_specularN
//    // normal: texture_normalN
//
//    // 1. diffuse maps
//    vector <Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//    // 2. specular maps
//    vector <Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//    // 3. normal maps
//    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
//    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
//    // 4. height maps
//    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
//    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
}

std::ostream &operator<<(std::ostream &os, const Model &model) {
    os << "loadStatus: " << model.loadStatus << " path: " << model.modelPath;
    return os;
}

const vector<Mesh> &Model::getMeshs() const {
    return meshs;
}



