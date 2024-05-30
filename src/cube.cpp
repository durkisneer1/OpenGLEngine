#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Cube.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "BufferObject.hpp"

namespace kn
{

static const std::vector<Vertex> vertices = {
    {{ -1.0f, -1.0f, -1.0f },  { 0.0f, 0.0f, -1.0f },  { 0.0f, 0.0f }},
    {{ 1.0f, -1.0f, -1.0f },   { 0.0f, 0.0f, -1.0f },  { 1.0f, 0.0f }},
    {{ 1.0f,  1.0f, -1.0f },   { 0.0f, 0.0f, -1.0f },  { 1.0f, 1.0f }},
    {{ 1.0f,  1.0f, -1.0f },   { 0.0f, 0.0f, -1.0f },  { 1.0f, 1.0f }},
    {{ -1.0f,  1.0f, -1.0f },  { 0.0f, 0.0f, -1.0f },  { 0.0f, 1.0f }},
    {{ -1.0f, -1.0f, -1.0f },  { 0.0f, 0.0f, -1.0f },  { 0.0f, 0.0f }},

    {{ -1.0f, -1.0f,  1.0f },  { 0.0f, 0.0f, 1.0f },  { 0.0f, 0.0f }},
    {{ 1.0f, -1.0f,  1.0f },   { 0.0f, 0.0f, 1.0f },  { 1.0f, 0.0f }},
    {{ 1.0f,  1.0f,  1.0f },   { 0.0f, 0.0f, 1.0f },  { 1.0f, 1.0f }},
    {{ 1.0f,  1.0f,  1.0f },   { 0.0f, 0.0f, 1.0f },  { 1.0f, 1.0f }},
    {{ -1.0f,  1.0f,  1.0f },  { 0.0f, 0.0f, 1.0f },  { 0.0f, 1.0f }},
    {{ -1.0f, -1.0f,  1.0f },  { 0.0f, 0.0f, 1.0f },  { 0.0f, 0.0f }},

    {{ -1.0f, 1.0f, 1.0f },    { -1.0f, 0.0f, 0.0f },  { 1.0f, 0.0f }},
    {{ -1.0f, 1.0f, -1.0f },   { -1.0f, 0.0f, 0.0f },  { 1.0f, 1.0f }},
    {{ -1.0f, -1.0f, -1.0f },  { -1.0f, 0.0f, 0.0f },  { 0.0f, 1.0f }},
    {{ -1.0f, -1.0f, -1.0f },  { -1.0f, 0.0f, 0.0f },  { 0.0f, 1.0f }},
    {{ -1.0f, -1.0f, 1.0f },   { -1.0f, 0.0f, 0.0f },  { 0.0f, 0.0f }},
    {{ -1.0f, 1.0f, 1.0f },    { -1.0f, 0.0f, 0.0f },  { 1.0f, 0.0f }},

    {{ 1.0f, 1.0f, 1.0f },    { 1.0f, 0.0f, 0.0f },  { 1.0f, 0.0f }},
    {{ 1.0f, 1.0f, -1.0f },   { 1.0f, 0.0f, 0.0f },  { 1.0f, 1.0f }},
    {{ 1.0f, -1.0f, -1.0f },  { 1.0f, 0.0f, 0.0f },  { 0.0f, 1.0f }},
    {{ 1.0f, -1.0f, -1.0f },  { 1.0f, 0.0f, 0.0f },  { 0.0f, 1.0f }},
    {{ 1.0f, -1.0f, 1.0f },   { 1.0f, 0.0f, 0.0f },  { 0.0f, 0.0f }},
    {{ 1.0f, 1.0f, 1.0f },    { 1.0f, 0.0f, 0.0f },  { 1.0f, 0.0f }},

    {{ -1.0f, -1.0f, -1.0f },  { 0.0f, -1.0f, 0.0f },  { 0.0f, 1.0f }},
    {{ 1.0f, -1.0f, -1.0f },   { 0.0f, -1.0f, 0.0f },  { 1.0f, 1.0f }},
    {{ 1.0f, -1.0f, 1.0f },    { 0.0f, -1.0f, 0.0f },  { 1.0f, 0.0f }},
    {{ 1.0f, -1.0f, 1.0f },    { 0.0f, -1.0f, 0.0f },  { 1.0f, 0.0f }},
    {{ -1.0f, -1.0f, 1.0f },   { 0.0f, -1.0f, 0.0f },  { 0.0f, 0.0f }},
    {{ -1.0f, -1.0f, -1.0f },  { 0.0f, -1.0f, 0.0f },  { 0.0f, 1.0f }},

    {{ -1.0f, 1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },  { 0.0f, 1.0f }},
    {{ 1.0f, 1.0f, -1.0f },   { 0.0f, 1.0f, 0.0f },  { 1.0f, 1.0f }},
    {{ 1.0f, 1.0f, 1.0f },    { 0.0f, 1.0f, 0.0f },  { 1.0f, 0.0f }},
    {{ 1.0f, 1.0f, 1.0f },    { 0.0f, 1.0f, 0.0f },  { 1.0f, 0.0f }},
    {{ -1.0f, 1.0f, 1.0f },   { 0.0f, 1.0f, 0.0f },  { 0.0f, 0.0f }},
    {{ -1.0f, 1.0f, -1.0f },  { 0.0f, 1.0f, 0.0f },  { 0.0f, 1.0f }}
};

Cube::Cube()
{
    VAO = kn::vao::generate(
        "cube",
        kn::buffer::generate("cube", vertices)
    );

    shaderPtr = shader::get("default");
    shaderPtr->use();
    shaderPtr->setInt("material.diffuse", 0);
    shaderPtr->setInt("material.specular", 1);
    diffuse = texture::get("_k_diffuse_");
    specular = texture::get("_k_specular_");
}

void Cube::render()
{
    glm::mat4 model = glm::mat4(1.0f);
    model *= glm::toMat4(glm::quat(glm::radians(rot)));
    model = glm::scale(model, scale);
    model = glm::translate(model, pos);

    shaderPtr->use();
    shaderPtr->setMat4("model", model);
    shaderPtr->setFloat("material.gloss", gloss);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse->id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specular->id);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

}  // namespace kn
