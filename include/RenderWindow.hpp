#include <glm/glm.hpp>

#include <string>


struct GLFWwindow;


namespace kn
{
	namespace window
	{
		int init(int screenWidth, int screenHeight, const std::string& windowTitle);

		void toggleWireframe();

		float tick();

		GLFWwindow* get();

		int getWidth();

		int getHeight();
	}
}
