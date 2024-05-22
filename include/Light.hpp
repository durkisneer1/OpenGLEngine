#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "Shader.hpp"

namespace kn
{

class DirectionalLight
{
public:
    DirectionalLight();
    ~DirectionalLight() = default;

    glm::vec3 direction = { 0.0f, -1.0f, 0.0f };
    glm::vec3 ambient = { 0.05f, 0.05f, 0.05f };
    glm::vec3 diffuse = { 1.0f, 1.0f, 1.0f };
    glm::vec3 specular = { 1.0f, 1.0f, 1.0f };

    void update();

private:
    std::shared_ptr<shader::Shader> m_shaderPtr;
};

}  // namespace kn
