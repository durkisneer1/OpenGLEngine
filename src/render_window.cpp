#include "RenderWindow.hpp"
#include "stb_image.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


namespace kn
{
    namespace window
    {
        static GLFWwindow* _window;
        static bool _wireframeMode = false;
        static bool _zBufferMode = true;

        static float _deltaTime = 0.0f;
        static float _lastFrame = 0.0f;

        int init(int screenWidth, int screenHeight, const std::string& windowTitle)
        {
            // GLFW Initialization v4.6
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            _window = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), nullptr, nullptr);
            if (_window == nullptr)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return -1;
            }
            glfwMakeContextCurrent(_window);

            // Load OpenGL Function Pointers
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return -1;
            }

            // Enable OpenGL Z-Buffer
            glEnable(GL_DEPTH_TEST);
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        void framebufferSizeCallback(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }

        float tick()
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            _deltaTime = currentFrame - _lastFrame;
            _lastFrame = currentFrame;
            return _deltaTime;
        }

        int getWidth()
        {
            int vpSize[4];
            glGetIntegerv(GL_VIEWPORT, vpSize);
            return vpSize[2];
        }

        int getHeight()
        {
            int vpSize[4];
            glGetIntegerv(GL_VIEWPORT, vpSize);
            return vpSize[3];
        }

        void toggleWireframe()
        {
            _wireframeMode = !(_wireframeMode);
            if (_wireframeMode)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }

        GLFWwindow* get()
        {
            return _window;
        }
    }
}
