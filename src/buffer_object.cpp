#include "BufferObject.hpp"

#include <glad/glad.h>
#include <iostream>

namespace kn
{
namespace buffer
{

static std::map<std::string, BufferData> _bufferMap;

const BufferData& generate(const std::string& name, const std::vector<Vertex>& array)
{
    auto it = _bufferMap.find(name);
    if (it != _bufferMap.end())
        return it->second;

    unsigned int buffer;
    glGenBuffers(1, &buffer);

    _bufferMap[std::move(name)] = BufferData{ buffer, &array };
    return _bufferMap[name];
}

const BufferData& get(const std::string& name)
{
    auto it = _bufferMap.find(name);
    if (it != _bufferMap.end())
    {
        glDeleteBuffers(1, &it->second.ID);
        return it->second;
    }
    else
    {
        std::cout << "KN::BUFFER::GET::KEY_NOT_FOUND::" << name << std::endl;
    }
}

const std::map<std::string, BufferData>& getAll()
{
    return _bufferMap;
}

void release(const std::string& name)
{
    auto it = _bufferMap.find(name);
    if (it != _bufferMap.end())
        _bufferMap.erase(it);
    else
        std::cout << "KN::BUFFER::RELEASE::KEY_NOT_FOUND::" << name << std::endl;
}

void releaseAll()
{
    for (const auto& pair : _bufferMap)
        glDeleteBuffers(1, &pair.second.ID);
    _bufferMap.clear();
}

}  // namespace buffer
}  // namespace kn
