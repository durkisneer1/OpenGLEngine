#pragma once

#include <string>
#include <vector>
#include <functional>

namespace kn
{
namespace buffer
{

struct BufferData
{
    unsigned int ID;
    const std::vector<float>* array;
};

const BufferData& generate(const std::string& name, const std::vector<float>& array);

const BufferData& get(const std::string& name);

void release(const std::string& name);

void releaseAll();

}  // namespace buffer
}  // namespace kn
