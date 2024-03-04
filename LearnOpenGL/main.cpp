#include "RenderWindow.hpp"
#include "Shader.hpp"

#include "stb_image.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main()
{
    kn::window::init(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL");
    GLFWwindow* window = kn::window::getWindow();

    Shader shader("shader.vert", "shader.frag");  // Load vertex and fragment shaders

    // Triangle vertices with center at origin
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  // Bottom left
        0.5f, -0.5f, 0.0f,   // Bottom right
        0.0f,  0.5f, 0.0f    // Top center
    };

    float texCoords[] = {
        0.0f, 0.0f,  // Bottom left
        1.0f, 0.0f,  // Bottom right
        0.5f, 1.0f   // Top center
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);  // Generate VAO ID
    glGenBuffers(1, &VBO);  // Generate VBO ID

    glBindVertexArray(VAO);  // Activate VAO

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  // Bind VBO ID to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // Upload vertices to GL_ARRAY_BUFFER/VBO

    // At layout location `0`, stride over `3` `float`ing point `3` dimensional vertices starting at byte `0`
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  // Enable location 0

    glBindBuffer(GL_ARRAY_BUFFER, 0);  // Deactivate VBO
    glBindVertexArray(0);  // Deactivate VAO

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shader.use();  // Set active shader program
        glBindVertexArray(VAO);  // Set active VAO
        glDrawArrays(GL_TRIANGLES, 0, 3);  // Draw with VAO configuration containing VBO(s)

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.free();

    glfwTerminate();
    return 0;
}
