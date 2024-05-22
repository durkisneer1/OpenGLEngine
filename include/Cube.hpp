#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Constants.hpp"
#include "Shader.hpp"

namespace kn
{

class Cube {
public:
    glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
    glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
    glm::vec3 rot = { 0.0f, 0.0f, 0.0f };
    float gloss = 32.0f;
    unsigned int diffuse;
    unsigned int specular;

    Cube();
    ~Cube() = default;

    void render();

private:
    std::shared_ptr<shader::Shader> shaderPtr;
    unsigned int VAO;
};

}  // namespace kn
