#include <glad/glad.h>
#include <algorithm>

#include "VertexArray.hpp"
#include "BufferObject.hpp"

namespace kn {
namespace vao {

static std::vector<unsigned int> vaos;

unsigned int generate(std::shared_ptr<buffer::VertexData> buffer, std::shared_ptr<buffer::IndexData> indexBuffer)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, buffer->ID);
    glBufferData(
        GL_ARRAY_BUFFER,
        buffer->array->size() * sizeof(Vertex),
        &(*buffer->array)[0],
        GL_STATIC_DRAW
    );

    if (indexBuffer)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->ID);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            indexBuffer->array->size() * sizeof(unsigned int),
            &(*indexBuffer->array)[0],
            GL_STATIC_DRAW
        );
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::texCoord));
    glEnableVertexAttribArray(2);

    vaos.push_back(VAO);
    return VAO;
}

const std::vector<unsigned int>& getVAOs()
{
    return vaos;
}

void release(unsigned int vao)
{
    glDeleteVertexArrays(1, &vao);
    vaos.erase(std::remove(vaos.begin(), vaos.end(), vao), vaos.end());
}

void releaseAll()
{
    for (auto vao : vaos)
        glDeleteVertexArrays(1, &vao);
    vaos.clear();
}

}  // namespace vao
}  // namespace kn
