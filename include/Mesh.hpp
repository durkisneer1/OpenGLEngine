#pragma once

#include <vector>
#include <memory>

namespace kn
{

namespace texture { struct Texture; }
struct Vertex;

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<std::shared_ptr<texture::Texture>> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<texture::Texture>> textures);
    ~Mesh() = default;

    void render();
private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

}  // namespace kn
