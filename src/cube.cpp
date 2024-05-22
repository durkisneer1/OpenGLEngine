#include "Cube.hpp"
#include "Texture.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "VertexArray.hpp"
#include "BufferObject.hpp"

namespace kn
{

static const std::vector<float> vertices = {
    // vertices           // normals          // texcoords
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f, -1.0f,   0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f, -1.0f,   0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
    1.0f,  1.0f, -1.0f,   0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 0.0f,

    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    1.0f,  1.0f,  1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

    -1.0f, 1.0f, 1.0f,    -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    -1.0f, 1.0f, -1.0f,   -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -1.0f, 1.0f, 1.0f,    -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    1.0f, 1.0f, -1.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    1.0f, -1.0f, 1.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
    1.0f, -1.0f, -1.0f,   0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,    0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 1.0f,    0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
    -1.0f, -1.0f, 1.0f,   0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,

    -1.0f, 1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    1.0f, 1.0f, -1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    -1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    -1.0f, 1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
};

Cube::Cube()
{
    const auto& VBO = kn::buffer::generate("cube", vertices);
    VAO = kn::vao::generate(
        "cube",
        {
            { VBO, { 3, 3, 2 }, { 0, 1, 2 } }
        }
    );

    shaderPtr = shader::get("default");
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

    shaderPtr->setMat4("model", model);
    shaderPtr->setFloat("material.gloss", gloss);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuse);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specular);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

}  // namespace kn
