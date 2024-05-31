#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

namespace kn {

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

namespace buffer {

struct VertexData
{
    unsigned int ID;
    const std::vector<Vertex>* array;
};

struct IndexData
{
    unsigned int ID;
    const std::vector<unsigned int>* array;
};

std::shared_ptr<VertexData> generate(const std::vector<Vertex>& array);

std::shared_ptr<IndexData> generate(const std::vector<unsigned int>& array);

const std::vector<std::shared_ptr<VertexData>>& getVertexDatas();

const std::vector<std::shared_ptr<IndexData>>& getIndexDatas();

void release(std::shared_ptr<VertexData> buffer);

void release(std::shared_ptr<IndexData> buffer);

void releaseAll();

}  // namespace buffer
}  // namespace kn
