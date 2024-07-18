#include "Renderer.hpp"

#include "root.hpp"
#include <iostream>

namespace DK
{
	void renderTriangle(const std::array<glm::vec2, 3>& vertices, Color4 color, bool fill, float strokeWidth)
	{
		if (!Context::s_CurrentContext) return;

		if (!fill)
		{
			renderLine(vertices[0], vertices[1], color, strokeWidth);
			renderLine(vertices[0], vertices[2], color, strokeWidth);
			renderLine(vertices[1], vertices[2], color, strokeWidth);
			return;
		}

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		unsigned int eb;
		glCreateBuffers(1, &eb);

		unsigned char eBuff[3] = { 0,1,2 };
		glNamedBufferData(eb, sizeof(unsigned char) * 3, eBuff, GL_STATIC_DRAW);
		glVertexArrayElementBuffer(vao, eb);

		float vBuff[6]{};
		for (unsigned char i = 0; i < 3; i++)
		{
			vBuff[i * 2] = vertices[i].x;
			vBuff[i * 2 + 1] = vertices[i].y;
		}
		glNamedBufferData(vb, sizeof(float) * 6, vBuff, GL_STATIC_DRAW);
		glVertexArrayVertexBuffer(vao, 0, vb, 0, sizeof(float) * 2);
		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);

		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP(Context::s_CurrentContext->getProjectionMatrix());

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, nullptr);

		glDeleteBuffers(1, &vb);
		glDeleteBuffers(1, &eb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderTriangle(const std::array<glm::vec2, 3>& vertices, Color3 color, bool fill, float strokeWidth)
	{
		renderTriangle(vertices, Color4(color, 1.0), fill, strokeWidth);
	}
	void renderTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color4 color, bool fill, float strokeWidth)
	{
		renderTriangle({ p1, p2, p3 }, color, fill, strokeWidth);
	}
	void renderTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color3 color, bool fill, float strokeWidth)
	{
		renderTriangle({ p1, p2, p3 }, color, fill, strokeWidth);
	}

	void renderQuad(const std::array<glm::vec2, 4>& vertices, Color4 color, bool fill, float strokeWidth)
	{
		if (!Context::s_CurrentContext) return;

		if (!fill)
		{
			renderLine(vertices[0], vertices[1], color, strokeWidth);
			renderLine(vertices[1], vertices[3], color, strokeWidth);
			renderLine(vertices[2], vertices[3], color, strokeWidth);
			renderLine(vertices[2], vertices[0], color, strokeWidth);
			return;
		}

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		unsigned int eb;
		glCreateBuffers(1, &eb);

		unsigned char eBuff[6] = { 0,1,2, 1,2,3 };
		glNamedBufferData(eb, sizeof(unsigned char) * 6, eBuff, GL_STATIC_DRAW);
		glVertexArrayElementBuffer(vao, eb);

		float vBuff[8]{};
		for (unsigned char i = 0; i < 4; i++)
		{
			vBuff[i * 2] = vertices[i].x;
			vBuff[i * 2 + 1] = vertices[i].y;
		}
		glNamedBufferData(vb, sizeof(float) * 8, vBuff, GL_STATIC_DRAW);
		glVertexArrayVertexBuffer(vao, 0, vb, 0, sizeof(float) * 2);
		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);

		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP(Context::s_CurrentContext->getProjectionMatrix());

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);

		glDeleteBuffers(1, &vb);
		glDeleteBuffers(1, &eb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderQuad(const std::array<glm::vec2, 4>& vertices, Color3 color, bool fill, float strokeWidth)
	{
		renderQuad(vertices, Color4(color, 1.0), fill, strokeWidth);
	}
	void renderQuad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4, Color4 color, bool fill, float strokeWidth)
	{
		renderQuad({ p1, p2, p3, p4 }, color, fill, strokeWidth);
	}
	void renderQuad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4, Color3 color, bool fill, float strokeWidth)
	{
		renderQuad({ p1, p2, p3, p4 }, Color4(color, 1.0F), fill, strokeWidth);
	}

	/* after the first two points. every other point must use the previous point to be a triangle in the polygon you want. */
	void renderPoly(const std::vector<glm::vec2>& vertices, Color4 color, bool fill, float strokeWidth)
	{
		if (!Context::s_CurrentContext) return;

		if (!fill)
		{
			if (vertices.size() > 3)
			{
				const unsigned int limit = vertices.size() - 2;
				unsigned int lastA = 3, lastB = 2;
				for (unsigned int i = 1; i < limit; i += 2)
				{
					renderLine(vertices[i], vertices[i + 2], color, strokeWidth);
					lastA = i + 2;
				}
				for (unsigned int i = 0; i < limit; i += 2)
				{
					renderLine(vertices[i], vertices[i + 2], color, strokeWidth);
					lastB = i + 2;
				}
				renderLine(vertices[0], vertices[1], color, strokeWidth);
				renderLine(vertices[lastA], vertices[lastB], color, strokeWidth);
				return;
			}
			renderLine(vertices[0], vertices[1], color, strokeWidth);
			renderLine(vertices[0], vertices[2], color, strokeWidth);
			renderLine(vertices[1], vertices[2], color, strokeWidth);
			return;
		}

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		unsigned int eb;
		glCreateBuffers(1, &eb);

		unsigned short triangles = vertices.size() - 2;

		unsigned short* eBuff = (unsigned short*) _alloca(sizeof(unsigned short) * 3 * triangles);

		for (unsigned short i = 0; i < triangles; i++)
		{
			eBuff[i * 3] = i;
			eBuff[i * 3 + 1] = 1 + i;
			eBuff[i * 3 + 2] = 2 + i;
		}

		glNamedBufferData(eb, sizeof(unsigned short) * 3 * triangles, eBuff, GL_STATIC_DRAW);
		glVertexArrayElementBuffer(vao, eb);

		glNamedBufferData(vb, sizeof(float) * 2 * vertices.size(), vertices.data(), GL_STATIC_DRAW);
		glVertexArrayVertexBuffer(vao, 0, vb, 0, sizeof(float) * 2);
		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);

		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP(Context::s_CurrentContext->getProjectionMatrix());

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3 * triangles, GL_UNSIGNED_SHORT, nullptr);

		glDeleteBuffers(1, &vb);
		glDeleteBuffers(1, &eb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderPoly(const std::vector<glm::vec2>& vertices, Color3 color, bool fill, float strokeWidth)
	{
		renderPoly(vertices, Color4(color, 1.0F), fill, strokeWidth);
	}

	void renderLine(const std::array<glm::vec2, 2>& vertices, Color4 color, float lineWidth)
	{
		glm::vec2 offset = vertices[1] - vertices[0];

		float distance = glm::sqrt((offset.x * offset.x) + (offset.y * offset.y));

		if (distance == 0)
		{
			throw std::exception("Line must not be a point!");
		}

		glm::vec2 dir = offset / distance;

		glm::vec2 lineSloper = glm::vec2(-dir.y, dir.x) * lineWidth / 2.0f;

		glm::vec2 p1 = vertices[0] + lineSloper;
		glm::vec2 p2 = vertices[0] - lineSloper;

		glm::vec2 p3 = vertices[1] + lineSloper;
		glm::vec2 p4 = vertices[1] - lineSloper;

		renderQuad(p1, p2, p3, p4, color);
	}
	void renderLine(const std::array<glm::vec2, 2>& vertices, Color3 color, float lineWidth)
	{
		renderLine(vertices, Color4(color, 1.0F), lineWidth);
	}
	void renderLine(glm::vec2 p1, glm::vec2 p2, Color4 color, float lineWidth)
	{
		renderLine({ p1, p2 }, color, lineWidth);
	}
	void renderLine(glm::vec2 p1, glm::vec2 p2, Color3 color, float lineWidth)
	{
		renderLine({ p1, p2 }, Color4(color, 1.0F), lineWidth);
	}

	void renderCircle(glm::vec2 point, float radius, Color4 color, bool fill, float strokeWidth)
	{
		if (!Context::s_CurrentContext) return;

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		unsigned int eb;
		glCreateBuffers(1, &eb);

		unsigned char eBuff[3]{ 0,1,2 };

		glNamedBufferData(eb, sizeof(unsigned char) * 3, eBuff, GL_STATIC_DRAW);
		glVertexArrayElementBuffer(vao, eb);

		float pos[6]
		{
			point.x - radius * 2.5F, point.y - radius * 2.5F,
			point.x + radius * 2.5F, point.y - radius * 2.5F,
			point.x, point.y + radius * 2.5F
		};

		glNamedBufferData(vb, sizeof(float) * 6, pos, GL_STATIC_DRAW);
		glVertexArrayVertexBuffer(vao, 0, vb, 0, sizeof(float) * 2);
		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);

		if (!Program::colorCircleRenderer.isInitialized())
		{
			Program::colorCircleRenderer.initialize(ROOT_DIR "/src/SPrograms/ColorCircle");
		}

		Program::colorCircleRenderer.use();
		Program::colorCircleRenderer.uni4f("uColor", color);

		if (fill)
		{
			Program::colorCircleRenderer.uni1f("uOuterRadius", radius);
			Program::colorCircleRenderer.uni1f("uInnerRadius", 0);
		}
		else
		{
			Program::colorCircleRenderer.uni1f("uOuterRadius", radius + 0.5F * strokeWidth);
			Program::colorCircleRenderer.uni1f("uInnerRadius", radius - 0.5F * strokeWidth);
		}

		Program::colorCircleRenderer.uni2f("uPoint", point);

		Program::colorCircleRenderer.uniMVP(Context::s_CurrentContext->getProjectionMatrix());

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, nullptr);

		glDeleteBuffers(1, &vb);
		glDeleteBuffers(1, &eb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderCircle(glm::vec2 point, float radius, Color3 color, bool fill, float strokeWidth)
	{
		renderCircle(point, radius, Color4(color, 1.0F), fill, strokeWidth);
	}

	void renderRing(glm::vec2 point, float outerRadius, float innerRadius, Color4 color, bool fill, float strokeWidth)
	{
		if (!Context::s_CurrentContext) return;

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		unsigned int eb;
		glCreateBuffers(1, &eb);

		unsigned char eBuff[3]{ 0,1,2 };

		glNamedBufferData(eb, sizeof(unsigned char) * 3, eBuff, GL_STATIC_DRAW);
		glVertexArrayElementBuffer(vao, eb);

		float pos[6]
		{
			point.x - outerRadius * 2.5F, point.y - outerRadius * 2.5F,
			point.x + outerRadius * 2.5F, point.y - outerRadius * 2.5F,
			point.x, point.y + outerRadius * 2.5F
		};

		glNamedBufferData(vb, sizeof(float) * 6, pos, GL_STATIC_DRAW);
		glVertexArrayVertexBuffer(vao, 0, vb, 0, sizeof(float) * 2);
		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);

		if (!Program::colorCircleRenderer.isInitialized())
		{
			Program::colorCircleRenderer.initialize(ROOT_DIR "/src/SPrograms/ColorCircle");
		}

		Program::colorCircleRenderer.use();
		Program::colorCircleRenderer.uni4f("uColor", color);

		if (fill)
		{
			Program::colorCircleRenderer.uni1f("uOuterRadius", outerRadius);
			Program::colorCircleRenderer.uni1f("uInnerRadius", innerRadius);
		}
		else
		{
			Program::colorCircleRenderer.uni1f("uOuterRadius", outerRadius + 0.5F * strokeWidth);
			Program::colorCircleRenderer.uni1f("uInnerRadius", outerRadius - 0.5F * strokeWidth);
		}

		Program::colorCircleRenderer.uni2f("uPoint", point);

		Program::colorCircleRenderer.uniMVP(Context::s_CurrentContext->getProjectionMatrix());

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, nullptr);

		if (!fill)
		{
			Program::colorCircleRenderer.uni1f("uOuterRadius", innerRadius + 0.5F * strokeWidth);
			Program::colorCircleRenderer.uni1f("uInnerRadius", innerRadius - 0.5F * strokeWidth);

			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, nullptr);
		}

		glDeleteBuffers(1, &vb);
		glDeleteBuffers(1, &eb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderRing(glm::vec2 point, float outerRadius, float innerRadius, Color3 color, bool fill, float strokeWidth)
	{
		renderRing(point, outerRadius, innerRadius, Color4(color, 1.0F), fill, strokeWidth);
	}
}