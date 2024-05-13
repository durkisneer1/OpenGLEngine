#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Constants.hpp"
#include "Shader.hpp"

namespace kn
{

class Cube {
public:
    glm::vec3 pos;
    glm::vec3 scale;

    Cube(
        glm::vec3 pos = { 0.0f, 0.0f, 0.0f },
        glm::vec3 scale = { 1.0f, 1.0f, 1.0f },
        Color color = { 200, 200, 200 }
    );
    ~Cube();

    void render();

private:
    std::shared_ptr<shader::Shader> shaderPtr;
    unsigned int texID, VAO;
    Color color;
};

}  // namespace kn
