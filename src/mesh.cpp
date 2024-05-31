#include <string>

#include <glad/glad.h>

#include "Mesh.hpp"
#include "BufferObject.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

namespace kn {

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<std::shared_ptr<texture::Texture>> textures)
: vertices(vertices), indices(indices), textures(textures)
{
    setupMesh();
}

void Mesh::setupMesh()
{
    VBO = buffer::generate(vertices);
    EBO = buffer::generate(indices);
    VAO = vao::generate(VBO, EBO);
}

void Mesh::render(std::shared_ptr<shader::Shader> shaderPtr)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        auto texType = textures[i]->type;
        std::string name;
        if(texType == DIFFUSE)
        {
            number = std::to_string(diffuseNr++);
            name = "texture_diffuse";
        }
        else if(texType == SPECULAR)
        {
            number = std::to_string(specularNr++);
            name = "texture_specular";
        }

        shaderPtr->setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i]->id);
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

}  // namespace kn
