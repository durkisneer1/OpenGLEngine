#pragma once

#include <vector>
#include <memory>

namespace kn
{

namespace texture { struct Texture; }
namespace shader { struct Shader; }
struct Vertex;

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<texture::Texture>> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<texture::Texture>> textures);
    ~Mesh() = default;

    void render(std::shared_ptr<shader::Shader> shaderPtr);
private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

}  // namespace kn
