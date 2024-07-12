#include "Context.hpp"

namespace DK
{
	Context::Context(glm::uvec2 dimension, const std::string& title, const std::vector<WindowHint>& hints)
	{
		if (s_TotalContexts == 0 || hints.size() != 0)
		{
			if (!glfwInit())
				throw std::exception("Failed to initialize GLFW!");
			if (hints.size() != 0)
			{
				for (const WindowHint& hint : hints)
				{
					glfwWindowHint(hint.hint, hint.value);
				}
			}
		}
		m_Window = glfwCreateWindow(dimension.x, dimension.y, title.c_str(), nullptr, nullptr);
		if (!m_Window)
			throw std::exception("Failed to initialize Window!");

		select();
		if (s_TotalContexts == 0)
		{
			if (glewInit())
				throw std::exception("Failed to initialize GLEW!");
		}
		s_TotalContexts++;
	}

	Context::~Context()
	{
		glfwDestroyWindow(m_Window);
		if (s_TotalContexts == 1)
		{
			glfwTerminate();
		}
		s_TotalContexts--;
	}

	void Context::select() const noexcept
	{
		glfwMakeContextCurrent(m_Window);
	}

	bool Context::shouldClose() const noexcept
	{
		return glfwWindowShouldClose(m_Window);
	}

	void Context::close() const noexcept
	{
		glfwSetWindowShouldClose(m_Window, 1);
	}

	void Context::swapBuffers() const noexcept
	{
		glfwSwapBuffers(m_Window);
	}

	void Context::pollEvents() const noexcept
	{
		select();
		glfwPollEvents();
	}

	void Context::clearColor(glm::vec4 color) const noexcept
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Context::clearScreen() const noexcept
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	unsigned short Context::s_TotalContexts = 0;
}