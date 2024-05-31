#pragma once

#include <vector>
#include <memory>

namespace kn {
namespace buffer { struct VertexData; struct IndexData; }
namespace vao {

unsigned int generate(std::shared_ptr<buffer::VertexData> buffer, std::shared_ptr<buffer::IndexData> indexBuffer = nullptr);

const std::vector<unsigned int>& getVAOs();

void release(unsigned int vao);

void releaseAll();

}  // namespace vao
}  // namespace kn
