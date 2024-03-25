#include <glm/glm.hpp>

#include <string>


struct GLFWwindow;


namespace kn
{
	namespace window
	{
		int init(int screenWidth, int screenHeight, const std::string& windowTitle);

		void toggleWireframe();

		GLFWwindow* get();

		int getWidth();

		int getHeight();

		void _framebufferSizeCallback(GLFWwindow* window, int width, int height);
	}
}
