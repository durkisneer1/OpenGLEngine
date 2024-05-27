#include <map>
#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>

#include "Texture.hpp"

namespace kn
{
namespace texture
{

static std::map<std::string, std::shared_ptr<Texture>> textureMap;

std::shared_ptr<Texture> load(const std::string& name, TextureType textureType, const std::string& path)
{
    auto it = textureMap.find(name);
    if (it != textureMap.end() && it->second->path == path)
        return it->second;

    unsigned int texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, numChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &numChannels, 0); 
    if (data != nullptr)
    {
        if (numChannels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if (numChannels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "KN::TEXTURE::LOAD::FAILED::" << path << "::" << name << std::endl;
    }
    stbi_image_free(data);

    Texture texture{texID, textureType, path};
    auto texPtr = std::make_shared<Texture>(texture);
    textureMap[std::move(name)] = texPtr;
    return texPtr;
}

std::shared_ptr<Texture> create(const std::string& name, TextureType textureType, Color color)
{
    auto it = textureMap.find(name);
    if (it != textureMap.end())
        return it->second;

    unsigned int texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    SDL_Surface *surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, nullptr, SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a));
    if (surface != nullptr)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "KN::TEXTURE::CREATE::FAILED::" << name << std::endl;
    }

    Texture texture{texID, textureType};
    auto texPtr = std::make_shared<Texture>(texture);
    textureMap[std::move(name)] = texPtr;
    return texPtr;
}

std::shared_ptr<Texture> get(const std::string& name)
{
    auto it = textureMap.find(name);
    if (it != textureMap.end())
        return it->second;
    else
        std::cout << "KN::TEXTURE::GET::TEXTURE_NOT_FOUND::" << name << std::endl;
}

unsigned int count()
{
    return textureMap.size();
}

void release(const std::string& name)
{
    auto it = textureMap.find(name);
    if (it != textureMap.end())
    {
        glDeleteTextures(1, &it->second->id);
        textureMap.erase(it);
    }
    else
    {
        std::cout << "KN::TEXTURE::RELEASE::KEY_NOT_FOUND" << std::endl;
    }
}

void releaseAll()
{
    for (const auto& pair : textureMap)
        glDeleteTextures(1, &pair.second->id);
    textureMap.clear();
}

}  // namespace texture
}  // namespace kn
