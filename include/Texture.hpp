#pragma once

#include <string>
#include <memory>
#include "Constants.hpp"

namespace kn
{

enum TextureType
{
    DIFFUSE,
    SPECULAR
};

namespace texture
{

struct Texture
{
    unsigned int id;
    TextureType type;
};

std::shared_ptr<Texture> load(const std::string& name, TextureType textureType, const std::string& path);

std::shared_ptr<Texture> get(const std::string& name);

std::shared_ptr<Texture> create(const std::string& name, TextureType textureType, Color color);

void release(const std::string& name);

void releaseAll();

}  // namespace texture
}  // namespace kn
