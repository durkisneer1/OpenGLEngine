#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>


namespace kn
{
	namespace window
	{
		int init(int screenWidth, int screenHeight, const std::string& windowTitle);

		void framebufferSizeCallback(GLFWwindow* window, int width, int height);

		void toggleWireframe(bool mode);

		GLFWwindow* getWindow();
	}
}
