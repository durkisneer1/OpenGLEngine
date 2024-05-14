#include "Cube.hpp"

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "VertexArray.hpp"
#include "BufferObject.hpp"
#include "Texture.hpp"

namespace kn
{

static const std::vector<float> vertices = {
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
    1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
    1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
    1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f,

    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
    1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
    1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,

    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

    1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
    1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
    1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
    1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
    1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
    1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
    1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
    1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 1.0f,

    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
    1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
    1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
    1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f
};

Cube::Cube(unsigned int textureID) : texID(textureID)
{
    const auto& VBO = kn::buffer::generate("cube", vertices);
    VAO = kn::vao::generate(
        "cube",
        {
            { VBO, { 3, 2 }, { 0, 1 } }
        }
    );

    shaderPtr = shader::get("default");
    shaderPtr->use();
    shaderPtr->setBool("useTexture", texID ? true : false);
    // GLint val;
    // glGetUniformiv(shaderPtr->ID, glGetUniformLocation(shaderPtr->ID, "useTexture"), &val);
    // std::cout << val << std::endl;
}

void Cube::render()
{
    shaderPtr->use();
    shaderPtr->setVec3("uColor", color);

    if (texID)
        glBindTexture(GL_TEXTURE_2D, texID);
    glBindVertexArray(VAO);

    glm::mat4 model = glm::mat4(1.0f);
    model *= glm::toMat4(glm::quat(glm::radians(rot)));
    model = glm::scale(model, scale);
    model = glm::translate(model, pos);
    shaderPtr->setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Cube::~Cube()
{
    if (texID)
        glDeleteTextures(1, &texID);
}

}  // namespace kn
