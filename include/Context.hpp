#ifndef _Context_Hpp
#define _Context_Hpp

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GL/glew.h"

#include <string>
#include <exception>
#include <vector>

namespace DK
{
	struct WindowHint
	{
		unsigned int hint;
		unsigned int value;
		WindowHint(unsigned int hint, unsigned int value) : hint(hint), value(value) {}
	};

	void glfwErrorCallback(int error_code, const char* description);
	void __stdcall glErrorCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* msg, const void* userParam);

	class Context
	{
	public:
		Context(glm::uvec2 dimension, const std::string& title = "Window - Title Missing", const std::vector<WindowHint>& hints = {});
		~Context();

		void select() const noexcept;
		bool shouldClose() const noexcept;
		void close() const noexcept;

		void swapBuffers() const noexcept;
		void pollEvents() const noexcept;

		void clearColor(glm::vec4 color) const noexcept;
		void clearColor(glm::vec3 color) const noexcept { clearColor(glm::vec4(color, 1.0f)); }
		void clearScreen() const noexcept;

		glm::mat4 getProjectionMatrix() const noexcept;

	public:
		static unsigned short getNumOfAliveContexts() noexcept { return s_TotalContexts; }
		
	public:
		static const Context* s_CurrentContext;

	private:
		GLFWwindow* m_Window;
		const glm::mat4 m_ProjMatrix;

	private:
		static unsigned short s_TotalContexts;
	};
}

#endif