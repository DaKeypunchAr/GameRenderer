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

	float nGon = 3;
	double nGonSpeed = 1;

	bool pause = false;
	bool fill = false;

	bool wPressed = false, sPressed = false, pPressed = false, fPressed = false;

	double startAngle = 0;
	while (!context.shouldClose())
	{
		context.clearScreen();
		if (!wPressed && glfwGetKey(context.getRawPointer(), GLFW_KEY_W)) wPressed = true;
		if (!sPressed && glfwGetKey(context.getRawPointer(), GLFW_KEY_S)) sPressed = true;
		if (!pPressed && glfwGetKey(context.getRawPointer(), GLFW_KEY_P)) pPressed = true;
		if (!fPressed && glfwGetKey(context.getRawPointer(), GLFW_KEY_F)) fPressed = true;

		if (wPressed && !glfwGetKey(context.getRawPointer(), GLFW_KEY_W)) nGon++;
		if (wPressed && !glfwGetKey(context.getRawPointer(), GLFW_KEY_S)) nGon--;

		DK::renderRegularPoly(glm::vec2(400), 300, (unsigned int)nGon, startAngle, DK::PINK, fill, 3.0F);

		if (pPressed && !glfwGetKey(context.getRawPointer(), GLFW_KEY_P))
		{
			pPressed = false; pause = !pause;
		}
		if (fPressed && !glfwGetKey(context.getRawPointer(), GLFW_KEY_F))
		{
			fPressed = false; fill = !fill;
		}

		if (!pause)
		{
			startAngle += nGonSpeed;
			nGon += 0.1;
		}

		if (nGon > 25) nGon = 3;
		if (nGon < 3) nGon = 3;
		context.swapBuffers();
		context.pollEvents();
	}
}