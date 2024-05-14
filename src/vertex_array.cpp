#include "VertexArray.hpp"
#include <map>
#include <iostream>
#include <glad/glad.h>

namespace kn
{
namespace vao
{

static std::map<std::string, unsigned int> vaoMap;

unsigned int generate(const std::string& name, const std::vector<AttrData>& attrDatas)
{
    auto it = vaoMap.find(name);
    if (it != vaoMap.end())
        return it->second;

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    for (const AttrData& data : attrDatas)
    {
        if (data.positions.size() != data.strides.size())
        {
            std::cout << "KN::VAO::GENERATE::ATTR_DATA_MISMATCH" << std::endl;
            return 0;
        }

        glBindBuffer(GL_ARRAY_BUFFER, data.bufferData.ID);
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(float) * data.bufferData.array->size(),
            data.bufferData.array->data(),
            GL_STATIC_DRAW
        );

        int totalRange = 0;
        for (int stride : data.strides)
            totalRange += stride;

        int offset = 0;
        for (int i = 0; i < data.strides.size(); i++)
        {
            glVertexAttribPointer(
                data.positions.at(i),
                data.strides.at(i),
                GL_FLOAT,
                GL_FALSE,
                totalRange * sizeof(float),
                (void*)(offset * sizeof(float))
            );
            glEnableVertexAttribArray(data.positions.at(i));
        }
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
        return 0;
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
        std::cout << "KN::VAO::RELEASE::KEY_NOT_FOUND" << std::endl;
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
