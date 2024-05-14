#pragma once

#include <string>

namespace kn
{
namespace texture
{

unsigned int load(const std::string& name, const std::string& path);

unsigned int get(const std::string& name);

void release(const std::string& name);

void releaseAll();

}  // namespace texture
}  // namespace kn
