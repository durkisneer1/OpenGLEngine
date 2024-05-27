#pragma once

#include <vector>
#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

namespace kn
{

namespace texture { struct Texture; }
namespace shader { struct Shader; }
class Mesh;

class Model
{
public:
    glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
    glm::vec3 rot = { 0.0f, 0.0f, 0.0f };
    float gloss = 32.0f;

    Model(char* path);

    void render();
private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::shared_ptr<shader::Shader> shaderPtr;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<std::shared_ptr<texture::Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
};

}  // namespace kn
