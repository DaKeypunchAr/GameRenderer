#include "Renderer.hpp"

/* Color Settings that make you mesmerize seeing some renders :) */
static const glm::vec4 GREEN = glm::vec4(0.3f, 0.7f, 0.4f, 1.0f);

glm::vec3 color = GREEN;
glm::vec3 colorChange = glm::vec3(0.0002f, 0.00058f, 0.0009f);
glm::vec<3, bool> addColorChange = glm::vec<3, bool>(true, false, true);
glm::vec3 colorChangeChange = glm::vec3(0.000001f, 0.0000034f, 0.000001f);
glm::vec<3, bool> addColorChangeChange = glm::vec<3, bool>(false, false, true);

void updateColor()
{
	color.r += colorChange.r * (addColorChange.r ? 1 : -1);
	color.g += colorChange.g * (addColorChange.g ? 1 : -1);
	color.b += colorChange.b * (addColorChange.b ? 1 : -1);

	if (color.r > 1)
	{
		color.r = 1; addColorChange.r = false;
	}
	else if (color.r < 0)
	{
		color.r = 0; addColorChange.r = true;
	}
	if (color.g > 1)
	{
		color.g = 1; addColorChange.g = false;
	}
	else if (color.g < 0)
	{
		color.g = 0; addColorChange.g = true;
	}
	if (color.b > 1)
	{
		color.b = 1; addColorChange.b = false;
	}
	else if (color.b < 0)
	{
		color.b = 0; addColorChange.b = true;
	}

	colorChange.r += colorChangeChange.r * (addColorChangeChange.r ? 1 : -1);
	colorChange.g += colorChangeChange.g * (addColorChangeChange.g ? 1 : -1);
	colorChange.b += colorChangeChange.b * (addColorChangeChange.b ? 1 : -1);

	if (colorChange.r > 0.001f)
	{
		colorChange.r = 0.001f; addColorChangeChange.r = false;
	}
	else if (colorChange.r < 0)
	{
		colorChange.r = 0; addColorChangeChange.r = true;
	}
	if (colorChange.g > 0.001f)
	{
		colorChange.g = 0.001f; addColorChangeChange.g = false;
	}
	else if (colorChange.g < 0)
	{
		colorChange.g = 0; addColorChangeChange.g = true;
	}
	if (colorChange.b > 0.001f)
	{
		colorChange.b = 0.001f; addColorChangeChange.b = false;
	}
	else if (colorChange.b < 0)
	{
		colorChange.b = 0; addColorChangeChange.b = true;
	}
}

/* Tests that will take place */
void testRPolys(const DK::Context& context)
{
	static GLFWwindow* rawPtr = context.getRawPointer();
	static float nGon = 3;
	static float nGonSpeed = 0.01f;
	static double nGonAngleSpeed = 1.0;
	static double startAngle = 0;

	static bool pause = false;
	static bool fill = true;
	static unsigned short counter = 0;

	static bool wPressed = false, sPressed = false, pPressed = false, fPressed = false;

	if (!wPressed && glfwGetKey(rawPtr, GLFW_KEY_W)) wPressed = true;
	if (!sPressed && glfwGetKey(rawPtr, GLFW_KEY_S)) sPressed = true;
	if (!pPressed && glfwGetKey(rawPtr, GLFW_KEY_P)) pPressed = true;
	if (!fPressed && glfwGetKey(rawPtr, GLFW_KEY_F)) fPressed = true;

	if (wPressed && !glfwGetKey(rawPtr, GLFW_KEY_W))
	{
		wPressed = false;
		nGon++;
	}
	if (sPressed && !glfwGetKey(rawPtr, GLFW_KEY_S))
	{
		sPressed = false;
		nGon--;
	}

	if (nGon < 3)
	{
		nGon = 3; nGonSpeed *= -1;
	}
	else if (nGon > 30)
	{
		nGon = 30; nGonSpeed *= -1;
	}

	if (counter++ == 5000)
	{
		counter = 0;
		fill = !fill;
	}

	DK::renderRegularPoly(glm::vec2(400), 300, (unsigned int)nGon, startAngle, color, fill, 8.0F);

	if (pPressed && !glfwGetKey(rawPtr, GLFW_KEY_P))
	{
		pPressed = false; pause = !pause;
	}
	if (fPressed && !glfwGetKey(rawPtr, GLFW_KEY_F))
	{
		fPressed = false; fill = !fill;
	}

	if (!pause)
	{
		startAngle += nGonAngleSpeed;
		nGon += nGonSpeed;
	}
}
void testRing(const DK::Context& context)
{
	static float outerRadius = 360.0F, innerRadius = 0.0F;
	static float oRChange = 0.1f, iRChange = 0.34f;
	static float oRChangeChange = 0.023f, iRChangeChange = 0.034f;
	static bool addORChange = false, addIRChange = true;
	static bool addORChangeChange = true, addIRChangeChange = false;
	static bool fill = true;
	static unsigned char counter = 0;

	outerRadius += addORChange ? oRChange : (-oRChange);
	innerRadius += addIRChange ? iRChange : (-iRChange);
	oRChange += addORChangeChange ? oRChangeChange : (-oRChangeChange);
	iRChange += addIRChangeChange ? iRChangeChange : (-iRChangeChange);

	if (counter++ == 255)
	{
		fill = !fill;
	}

	if (outerRadius > 240.0F)
	{
		outerRadius = 240.0F;
		addORChange = false;
	}
	if (innerRadius > outerRadius)
	{
		addIRChange = false;
		addORChange = true;
		innerRadius = outerRadius;
	}
	if (innerRadius < 3.0F)
	{
		addIRChange = true;
		innerRadius = 3.0F;
	}
	if (oRChange < 0.1F)
	{
		oRChange = 0.1F; addORChangeChange = true;
	}
	else if (oRChange > 3.5F)
	{
		oRChange = 3.5F; addORChangeChange = false;
	}
	if (iRChange < 0.1F)
	{
		iRChange = 0.1F; addIRChangeChange = true;
	}
	else if (iRChange > 3.5F)
	{
		iRChange = 3.5F; addIRChangeChange = false;
	}

	static std::vector<glm::vec2> points{
		glm::vec2(400),
		glm::vec2(125),
		glm::vec2(675, 125),
		glm::vec2(125, 675),
		glm::vec2(675),
	};
	float sOR = outerRadius * 0.4f, sIR = innerRadius * 0.4f;
	DK::renderRings(points, { outerRadius, sOR, sOR, sOR, sOR }, { innerRadius, sIR, sIR, sIR, sIR }, color, fill, 10.0F);
}

int main()
{
	/* Creating a context */
	std::vector<DK::WindowHint> hints = {
		DK::WindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API),
		DK::WindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE),
		DK::WindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4),
		DK::WindowHint(GLFW_CONTEXT_VERSION_MINOR, 5),
		DK::WindowHint(GLFW_RESIZABLE, GLFW_FALSE)
	};
	DK::Context context({ 800u, 800u }, "Test - Game Renderer", hints);

	glm::vec2 center = glm::vec2(400);
	DK::TriangleFan hexagon = DK::TriangleFan::makeRegularPoly(6u, 200.0F);

	float angle = 0.0F;
	float angleDiff = static_cast<float>(glm::radians(1.0));

	while (!context.shouldClose())
	{
		context.clearColor(glm::vec3(1.0f) - color);
		updateColor();
		context.clearScreen();
		glm::mat4 model = glm::translate(glm::mat4(1.0F), glm::vec3(center, 0.0F));
		model = glm::rotate(model, angle, glm::vec3(0.0F, 0.0F, 1.0F));
		
		DK::renderTriangleFan(hexagon, color, model);
		
		angle += angleDiff;

		context.swapBuffers();
		context.pollEvents();
	}
}