#include <map>
#include <iostream>
#include <glad/glad.h>

#include "VertexArray.hpp"

namespace kn
{
namespace vao
{

static std::map<std::string, unsigned int> vaoMap;

unsigned int generate(const std::string& name, const std::vector<buffer::BufferData>& bufferDatas)
{
    auto it = vaoMap.find(name);
    if (it != vaoMap.end())
        return it->second;

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    for (const buffer::BufferData& data : bufferDatas)
    {
        glBindBuffer(GL_ARRAY_BUFFER, data.ID);
        glBufferData(
            GL_ARRAY_BUFFER,
            data.array->size() * sizeof(Vertex),
            &(*data.array)[0],
            GL_STATIC_DRAW
        );

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::normal));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::texCoord));
        glEnableVertexAttribArray(2);
    }
        
    vaoMap[std::move(name)] = VAO;
    return VAO;
}

unsigned int get(const std::string& name)
{
    auto it = vaoMap.find(name);
    if (it != vaoMap.end())
        return it->second;
    else
        std::cout << "KN::VAO::GET::KEY_NOT_FOUND::" << name << std::endl;
}

void release(const std::string& name)
{
    auto it = vaoMap.find(name);
    if (it != vaoMap.end())
    {
        glDeleteVertexArrays(1, &it->second);
        vaoMap.erase(it);
    }
    else
    {
        std::cout << "KN::VAO::RELEASE::KEY_NOT_FOUND::" << name << std::endl;
    }
}

void releaseAll()
{
    for (const auto& pair : vaoMap)
        glDeleteVertexArrays(1, &pair.second);
    vaoMap.clear();
}

}  // namespace vao
}  // namespace kn
