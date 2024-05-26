#pragma once

#include <string>
#include <vector>
#include <functional>

#include <glm/glm.hpp>

namespace kn
{

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

namespace buffer
{

struct BufferData
{
    unsigned int ID;
    const std::vector<Vertex>* array;
};

const BufferData& generate(const std::string& name, const std::vector<Vertex>& array);

const BufferData& get(const std::string& name);

void release(const std::string& name);

void releaseAll();

}  // namespace buffer
}  // namespace kn
