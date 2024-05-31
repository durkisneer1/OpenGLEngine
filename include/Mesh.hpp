#pragma once

#include <vector>
#include <memory>

namespace kn {
namespace texture { struct Texture; }
namespace shader { struct Shader; }
namespace buffer { struct VertexData; struct IndexData; }

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
    unsigned int VAO;
    std::shared_ptr<buffer::VertexData> VBO;
    std::shared_ptr<buffer::IndexData> EBO;

    void setupMesh();
};

}  // namespace kn
