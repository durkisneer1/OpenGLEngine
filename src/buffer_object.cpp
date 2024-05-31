#include <glad/glad.h>
#include <algorithm>

#include "BufferObject.hpp"

namespace kn {
namespace buffer {

static std::vector<std::shared_ptr<VertexData>> _vertexBuffers;

static std::vector<std::shared_ptr<IndexData>> _indexBuffers;

std::shared_ptr<VertexData> generate(const std::vector<Vertex>& array)
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);

    VertexData data = { buffer, &array };
    auto ptr = std::make_shared<VertexData>(data);
    _vertexBuffers.push_back(ptr);
    return ptr;
}

std::shared_ptr<IndexData> generate(const std::vector<unsigned int>& array)
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);

    IndexData data = { buffer, &array };
    auto ptr = std::make_shared<IndexData>(data);
    _indexBuffers.push_back(ptr);
    return ptr;
}

const std::vector<std::shared_ptr<VertexData>>& getVertexDatas()
{
    return _vertexBuffers;
}

const std::vector<std::shared_ptr<IndexData>>& getIndexDatas()
{
    return _indexBuffers;
}

void release(std::shared_ptr<VertexData> buffer)
{
    glDeleteBuffers(1, &buffer->ID);
    delete buffer->array;
    _vertexBuffers.erase(std::remove(_vertexBuffers.begin(), _vertexBuffers.end(), buffer), _vertexBuffers.end());
}

void release(std::shared_ptr<IndexData> buffer)
{
    glDeleteBuffers(1, &buffer->ID);
    delete buffer->array;
    _indexBuffers.erase(std::remove(_indexBuffers.begin(), _indexBuffers.end(), buffer), _indexBuffers.end());
}

void releaseAll()
{
    for (auto& buffer : _vertexBuffers)
    {
        glDeleteBuffers(1, &buffer->ID);
        delete buffer->array;
    }
    _vertexBuffers.clear();

    for (auto& buffer : _indexBuffers)
    {
        glDeleteBuffers(1, &buffer->ID);
        delete buffer->array;
    }
    _indexBuffers.clear();
}

}  // namespace buffer
}  // namespace kn
