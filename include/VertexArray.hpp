#pragma once

#include <string>
#include <vector>

#include "BufferObject.hpp"

namespace kn
{
namespace vao
{

struct AttrData
{
    buffer::BufferData bufferData;
    std::vector<int> strides;
    std::vector<int> positions;
};

unsigned int generate(const std::string& name, const std::vector<AttrData>& attrData);

unsigned int get(const std::string& name);

void release(const std::string& name);

void releaseAll();

}  // namespace vao
}  // namespace kn
