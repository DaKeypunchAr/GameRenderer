#include "Renderer.hpp"

#include <iostream>

static glm::vec4 GREEN = glm::vec4(0.3f, 0.7f, 0.4f, 1.0f);

int main()
{
	std::cout << "Let's begin this renderer's development process!\n";

	std::vector<DK::WindowHint> hints = {
		DK::WindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API),
		DK::WindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE),
		DK::WindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4),
		DK::WindowHint(GLFW_CONTEXT_VERSION_MINOR, 5),
		DK::WindowHint(GLFW_RESIZABLE, GLFW_FALSE)
	};
	DK::Context context({ 800u, 800u }, "Test - Game Renderer", hints);
	context.clearColor(DK::BLACK);

	while (!context.shouldClose())
	{
		context.clearScreen();


		context.swapBuffers();
		context.pollEvents();
	}
}