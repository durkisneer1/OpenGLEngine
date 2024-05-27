#include "BufferObject.hpp"

#include <map>
#include <glad/glad.h>
#include <iostream>

namespace kn
{
namespace buffer
{

static std::map<std::string, BufferData> bufferMap;

const BufferData& generate(const std::string& name, const std::vector<Vertex>& array)
{
    auto it = bufferMap.find(name);
    if (it != bufferMap.end())
        return it->second;

    unsigned int buffer;
    glGenBuffers(1, &buffer);

    bufferMap[std::move(name)] = BufferData{ buffer, &array };
    return bufferMap[name];
}

const BufferData& get(const std::string& name)
{
    auto it = bufferMap.find(name);
    if (it != bufferMap.end())
    {
        glDeleteBuffers(1, &it->second.ID);
        return it->second;
    }
    else
    {
        std::cout << "KN::BUFFER::GET::KEY_NOT_FOUND::" << name << std::endl;
    }
}

void release(const std::string& name)
{
    auto it = bufferMap.find(name);
    if (it != bufferMap.end())
        bufferMap.erase(it);
    else
        std::cout << "KN::BUFFER::RELEASE::KEY_NOT_FOUND::" << name << std::endl;
}

void releaseAll()
{   
    for (const auto& pair : bufferMap)
        glDeleteBuffers(1, &pair.second.ID);
    bufferMap.clear();
}

}  // namespace buffer
}  // namespace kn
