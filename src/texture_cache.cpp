#include "TextureCache.hpp"
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


namespace kn
{
    unsigned int loadTexture(const char* path)
    {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Wrap texture by repeating if smaller than mesh
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Linear interpolation between mipmaps and samples when far
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // Linear interpolation from sample when close to camera
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Get width, height, and color channel count of image file
        int width, height, numChannels;
        unsigned char* data = stbi_load(path, &width, &height, &numChannels, 0);
        if (data)
        {
            // (target, mipmap level, format to store, texture size, 0, format and data type to load, image data)
            if (numChannels == 3)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            else if (numChannels == 4)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }

            glGenerateMipmap(GL_TEXTURE_2D);  // Generate multiple resolutions
        }
        else
        {
            std::cout << "Failed to load texture: " << path << std::endl;
        }
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);

        return texture;
    }
}