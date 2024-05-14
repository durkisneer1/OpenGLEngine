#include "Texture.hpp"

#include <map>
#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>

namespace kn
{
namespace texture
{

static std::map<std::string, unsigned int> textureMap;

unsigned int load(const std::string& name, const std::string& path)
{
    auto it = textureMap.find(name);
    if (it != textureMap.end())
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
        std::cout << "KN::TEXTURE::LOAD::FAILED" << std::endl;
    }
    stbi_image_free(data);

    textureMap[std::move(name)] = texID;
    return texID;
}

unsigned int get(const std::string& name)
{
    auto it = textureMap.find(name);
    if (it != textureMap.end())
        return it->second;
    else
        std::cout << "KN::TEXTURE::GET::TEXTURE_NOT_FOUND" << std::endl;
}

void release(const std::string& name)
{
    auto it = textureMap.find(name);
    if (it != textureMap.end())
    {
        glDeleteTextures(1, &it->second);
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
        glDeleteTextures(1, &pair.second);
    textureMap.clear();
}

}  // namespace texture
}  // namespace kn
