#include "RenderWindow.hpp"
#include "Shader.hpp"

#include "stb_image.h"

#include <iostream>


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


static unsigned int loadTexture(const char* path)
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
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}


int main()
{
    kn::window::init(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
    GLFWwindow* window = kn::window::getWindow();
    stbi_set_flip_vertically_on_load(true);

    auto texture = loadTexture("container.jpg");
    auto texture2 = loadTexture("awesomeface.png");

    Shader shader("shader.vert", "shader.frag");

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Set VBO as target
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // Upload vertices to GL_ARRAY_BUFFER/VBO

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // (layout location, range, data type, normalization, stride, offset)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);  // Positions
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));  // Color
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));  // Texture Coords
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);  // Deactivate VBO
    glBindVertexArray(0);  // Deactivate VAO

    float fadeVal = 0;
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    shader.setFloat("fade", fadeVal);

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
        else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            if (fadeVal <= 1.0)
                fadeVal += 0.001;
            shader.use();
            shader.setFloat("fade", fadeVal);
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            if (fadeVal >= 0.0)
                fadeVal -= 0.001;
            shader.use();
            shader.setFloat("fade", fadeVal);
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.free();

    glfwTerminate();
    return 0;
}
