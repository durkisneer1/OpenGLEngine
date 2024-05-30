#include <iostream>

#include <assimp/postprocess.h>
#include <stb/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Model.hpp"
#include "Mesh.hpp"
#include "BufferObject.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

namespace kn
{

Model::Model(const std::string& path)
{
    loadModel(path);
    shaderPtr = shader::get("default");
}

void Model::render()
{
    glm::mat4 model = glm::mat4(1.0f);
    model *= glm::toMat4(glm::quat(glm::radians(rot)));
    model = glm::scale(model, scale);
    model = glm::translate(model, pos);

    shaderPtr->use();
    shaderPtr->setMat4("model", model);
    shaderPtr->setFloat("material.gloss", gloss);

    for (Mesh& mesh : meshes)
        mesh.render(shaderPtr);
}

void Model::loadModel(const std::string& path)
{
    Assimp::Importer aiImporter;
    const aiScene* scene = aiImporter.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "KN::MODEL::LOAD_MODEL::INCOMPLETE::ASSIMP::" << aiImporter.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // Processing node's meshes
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    // Processing node's children's meshes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<texture::Texture>> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vec;

        vec.x = mesh->mVertices[i].x;
        vec.y = mesh->mVertices[i].y;
        vec.z = mesh->mVertices[i].z;
        vertex.position = vec;

        vec.x = mesh->mNormals[i].x;
        vec.y = mesh->mNormals[i].y;
        vec.z = mesh->mNormals[i].z;
        vertex.normal = vec;

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoord = vec;
        }
        else {
            vertex.texCoord = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    auto diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, DIFFUSE);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    auto specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, SPECULAR);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    return Mesh(vertices, indices, textures);
}

std::vector<std::shared_ptr<texture::Texture>> Model::loadMaterialTextures(
    aiMaterial *mat, aiTextureType type, TextureType texType
)
{
    std::vector<std::shared_ptr<texture::Texture>> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string indexName = directory + "/" + std::string(str.C_Str());
        auto texture = texture::load(indexName, texType, indexName);
        textures.push_back(texture);
    }
    return textures;
}

}  // namespace kn
