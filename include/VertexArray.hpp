#pragma once

#include <string>
#include <vector>

#include "BufferObject.hpp"

namespace kn
{
namespace vao
{

unsigned int generate(const std::string& name, const std::vector<buffer::BufferData>& bufferDatas);

unsigned int get(const std::string& name);

void release(const std::string& name);

void releaseAll();

}  // namespace vao
}  // namespace kn
