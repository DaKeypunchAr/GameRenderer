#ifndef _Context_Hpp
#define _Context_Hpp

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
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
		void clearScreen() const noexcept;

	public:
		static unsigned short getNumOfAliveContexts() noexcept { return s_TotalContexts; }

	private:
		GLFWwindow* m_Window;

	private:
		static unsigned short s_TotalContexts;
	};
}

#endif