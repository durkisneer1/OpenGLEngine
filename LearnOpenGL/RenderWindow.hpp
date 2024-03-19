#include <string>


struct GLFWwindow;


namespace kn
{
	namespace window
	{
		int init(int screenWidth, int screenHeight, const std::string& windowTitle);

		void framebufferSizeCallback(GLFWwindow* window, int width, int height);

		void toggleWireframe();

		GLFWwindow* get();
	}
}
