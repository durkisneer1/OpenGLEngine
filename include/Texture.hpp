#pragma once

#include <string>
#include "Constants.hpp"

namespace kn
{
namespace texture
{

unsigned int load(const std::string& name, const std::string& path);

unsigned int get(const std::string& name);

unsigned int create(const std::string& name, Color color);

void release(const std::string& name);

void releaseAll();

}  // namespace texture
}  // namespace kn
