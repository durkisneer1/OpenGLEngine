#include "Cube.hpp"

#include <glad/glad.h>

#include <iostream>

namespace kn
{

static float vertices[] = {
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

Cube::Cube(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, Color color)
: pos(pos), rot(rot), scale(scale), color(color)
{
    // Generate and bind texture2d id
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Generate texture from sdl surface
    SDL_Surface *surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, color.r, color.g, color.b));
    if (surface != nullptr)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to create surface" << std::endl;
    }
    SDL_FreeSurface(surface);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // bind Vertex Array Object
    glBindVertexArray(VAO);

    // copy vertex array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    shaderPtr = shader::get("default");
}

void Cube::render()
{
    shaderPtr->use();
    glBindTexture(GL_TEXTURE_2D, texID);
    glBindVertexArray(VAO);
    shaderPtr->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

Cube::~Cube()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &texID);
}

}  // namespace kn
