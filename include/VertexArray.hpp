#pragma once

#include <string>
#include <vector>

#include "BufferObject.hpp"

namespace kn
{
namespace vao
{

unsigned int generate(const std::string& name, const buffer::BufferData& bufferDatas, const buffer::BufferData* indexBuffer = nullptr);

unsigned int get(const std::string& name);

void release(const std::string& name);

void releaseAll();

}  // namespace vao
}  // namespace kn
