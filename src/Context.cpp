#include "Context.hpp"

namespace DK
{
	void glfwErrorCallback(int error_code, const char* description)
	{
		throw std::exception("GLFW Error!");
	}
	void glErrorCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* msg, const void* userParam)
	{
		throw std::exception("GL Error!");
	}

	Context::Context(glm::uvec2 dimension, const std::string& title, const std::vector<WindowHint>& hints)
		: m_ProjMatrix(glm::ortho(0.0f, (float)dimension.x, 0.0f, (float)dimension.y))
	{
		if (s_TotalContexts == 0 || hints.size() != 0)
		{
			if (!glfwInit())
				throw std::exception("Failed to initialize GLFW!");

			glfwSetErrorCallback(glfwErrorCallback);

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

			glEnable(GL_DEBUG_CALLBACK_FUNCTION);
			glDebugMessageCallback(glErrorCallback, nullptr);
		}
		s_TotalContexts++;
	}

	Context::~Context()
	{
		if (s_CurrentContext == this)
			s_CurrentContext = nullptr;
		glfwDestroyWindow(m_Window);
		if (s_TotalContexts == 1)
		{
			glfwTerminate();
		}
		s_TotalContexts--;
	}

	void Context::select() const noexcept
	{
		s_CurrentContext = this;
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
		if (s_CurrentContext != this) select();
		glfwPollEvents();
	}

	void Context::clearColor(glm::vec4 color) const noexcept
	{
		if (s_CurrentContext != this) select();
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Context::clearScreen() const noexcept
	{
		if (s_CurrentContext != this) select();
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glm::mat4 Context::getProjectionMatrix() const noexcept
	{
		return m_ProjMatrix;
	}

	unsigned short Context::s_TotalContexts = 0;
	const Context* Context::s_CurrentContext = nullptr;
}