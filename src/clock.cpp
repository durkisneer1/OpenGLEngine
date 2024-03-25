#include "Clock.hpp"

#include <GLFW/glfw3.h>


using namespace kn;


double Clock::tick()
{
	now = glfwGetTime();
	deltaTime = now - last;
	last = now;
	return deltaTime;
}