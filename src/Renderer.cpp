#include "Renderer.hpp"

#include "root.hpp"
#include <iostream>

namespace DK
{
	void renderTriangle(const std::array<glm::vec2, 3>& vertices, Color4 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!fill)
		{
			renderLineLoop({vertices[0], vertices[1], vertices[2]}, color, strokeWidth, model);
			return;
		}

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		glNamedBufferData(vb, sizeof(float) * 6, vertices.data(), GL_STATIC_DRAW);
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

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderTriangle(const std::array<glm::vec2, 3>& vertices, Color3 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderTriangle(vertices, Color4(color, 1.0), fill, strokeWidth, model);
	}
	void renderTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color4 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderTriangle({ p1, p2, p3 }, color, fill, strokeWidth, model);
	}
	void renderTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color3 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderTriangle({ p1, p2, p3 }, color, fill, strokeWidth, model);
	}

	void renderTriangles(const std::vector<std::array<glm::vec2, 3>>& triangles, Color4 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!fill)
		{
			for (const std::array<glm::vec2, 3>& vertices : triangles)
			{
				renderLineLoop(std::vector<glm::vec2>(vertices.begin(), vertices.end()), color, strokeWidth, model);
			}
			return;
		}

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		glNamedBufferData(vb, sizeof(float) * triangles.size() * 6, triangles.data(), GL_STATIC_DRAW);
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

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, triangles.size() * 3);

		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderTriangles(const std::vector<std::array<glm::vec2, 3>>& triangles, Color3 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderTriangles(triangles, Color4(color, 1.0F), fill, strokeWidth, model);
	}
	void renderTriangleFan(const std::vector<glm::vec2>& vertices, Color4 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!fill)
		{
			for (unsigned int i = 2; i < vertices.size(); i++)
			{
				renderLineLoop({ vertices[0], vertices[i], vertices[i - 1] }, color, strokeWidth, model);
			}
			return;
		}

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		glNamedBufferData(vb, sizeof(float) * vertices.size() * 2, vertices.data(), GL_STATIC_DRAW);
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

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());

		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderTriangleFan(const std::vector<glm::vec2>& vertices, Color3 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderTriangleFan(vertices, Color4(color, 1.0F), fill, strokeWidth, model);
	}

	void renderQuad(const std::array<glm::vec2, 4>& vertices, Color4 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!fill)
		{
			renderLineLoop({ vertices[0], vertices[1], vertices[3], vertices[2] }, color, strokeWidth, model);
			return;
		}

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		glNamedBufferData(vb, sizeof(float) * 8, vertices.data(), GL_STATIC_DRAW);
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

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderQuad(const std::array<glm::vec2, 4>& vertices, Color3 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderQuad(vertices, Color4(color, 1.0), fill, strokeWidth, model);
	}
	void renderQuad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4, Color4 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderQuad({ p1, p2, p3, p4 }, color, fill, strokeWidth, model);
	}
	void renderQuad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4, Color3 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderQuad({ p1, p2, p3, p4 }, Color4(color, 1.0F), fill, strokeWidth, model);
	}

	void renderQuads(const std::vector<std::array<glm::vec2, 4>>& quads, Color4 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!fill)
		{
			for (const std::array<glm::vec2, 4>& vertices : quads)
			{
				renderLineLoop({ vertices[0], vertices[1], vertices[3], vertices[2] }, color, strokeWidth, model);
			}
			return;
		}

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		glNamedBufferData(vb, sizeof(float) * 8 * quads.size(), quads.data(), GL_STATIC_DRAW);
		glVertexArrayVertexBuffer(vao, 0, vb, 0, sizeof(float) * 2);
		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);

		unsigned int eb;
		glCreateBuffers(1, &eb);

		unsigned int* eBuff = (unsigned int*)_alloca(sizeof(unsigned int) * 6 * quads.size());
		for (unsigned int i = 0; i < quads.size(); i++)
		{
			unsigned int i6 = i * 6, i4 = i * 4;
			eBuff[i6] = i4;
			eBuff[i6+1] = i4+1;
			eBuff[i6+2] = i4+2;
			eBuff[i6+3] = i4+1;
			eBuff[i6+4] = i4+2;
			eBuff[i6+5] = i4+3;
		}
		glNamedBufferData(eb, sizeof(unsigned int) * 6 * quads.size(), eBuff, GL_STATIC_DRAW);
		glVertexArrayElementBuffer(vao, eb);

		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, quads.size() * 6, GL_UNSIGNED_INT, nullptr);

		glDeleteBuffers(1, &eb);
		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderQuads(const std::vector<std::array<glm::vec2, 4>>& quads, Color3 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderQuads(quads, Color4(color, 1.0F), fill, strokeWidth, model);
	}

	/* after the first two points. every other point must use the previous point to be a triangle in the polygon you want. */
	void renderPoly(const std::vector<glm::vec2>& vertices, Color4 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!fill)
		{
			std::vector<glm::vec2> v;
			unsigned int i = 1;
			while (v.size() != vertices.size())
			{
				v.push_back(vertices[i]);
				if (i % 2 == 1)
				{
					if (i + 2 < vertices.size())
					{
						i += 2;
					}
					else if (i + 1 < vertices.size())
					{
						i++;
					}
					else
					{
						i--;
					}
				}
				else
				{
					i -= 2;
				}
			}
			renderLineLoop(v, color, strokeWidth, model);
			return;
		}

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

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

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());

		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderPoly(const std::vector<glm::vec2>& vertices, Color3 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderPoly(vertices, Color4(color, 1.0F), fill, strokeWidth, model);
	}

	void renderPolys(const std::vector<std::vector<glm::vec2>>& polys, Color4 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!fill)
		{
			for (const std::vector<glm::vec2>& vertices : polys)
			{
				std::vector<glm::vec2> v;
				unsigned int i = 1;
				while (v.size() != vertices.size())
				{
					v.push_back(vertices[i]);
					if (i % 2 == 1)
					{
						if (i + 2 < vertices.size())
						{
							i += 2;
						}
						else if (i + 1 < vertices.size())
						{
							i++;
						}
						else
						{
							i--;
						}
					}
					else
					{
						i -= 2;
					}
				}
				renderLineLoop(v, color, strokeWidth, model);
			}
			return;
		}

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		unsigned int totalPoints = 0;
		for (unsigned int i = 0; i < polys.size(); i++)
		{
			totalPoints += polys[i].size();
		}
		float* vBuff = (float*)_alloca(sizeof(float) * 2 * totalPoints);

		for (unsigned int i = 0, n = 0; i < totalPoints; n++)
		{
			for (unsigned int j = 0; j < polys[n].size(); j++, i++)
			{
				vBuff[i * 2] = polys[n][j].x;
				vBuff[i * 2 + 1] = polys[n][j].y;
			}
		}

		glNamedBufferData(vb, sizeof(float) * 2 * totalPoints, vBuff, GL_STATIC_DRAW);
		glVertexArrayVertexBuffer(vao, 0, vb, 0, sizeof(float) * 2);
		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);

		unsigned int eb;
		glCreateBuffers(1, &eb);

		unsigned int numOfElements = 3 * (totalPoints - 2);
		unsigned int* eBuff = (unsigned int*) _alloca(sizeof(unsigned int) * numOfElements);

		for (unsigned int i = 0; i + 2 < totalPoints; i++)
		{
			eBuff[i * 3] = i;
			eBuff[i * 3 + 1] = i+1;
			eBuff[i * 3 + 2] = i+2;
		}

		glNamedBufferData(eb, sizeof(unsigned int) * numOfElements, eBuff, GL_STATIC_DRAW);
		glVertexArrayElementBuffer(vao, eb);

		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, numOfElements, GL_UNSIGNED_INT, nullptr);

		glDeleteBuffers(1, &eb);
		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderPolys(const std::vector<std::vector<glm::vec2>>& polys, Color3 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderPolys(polys, Color4(color, 1.0F), fill, strokeWidth, model);
	}

	void renderLine(const std::array<glm::vec2, 2>& vertices, Color4 color, float lineWidth, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		glNamedBufferData(vb, sizeof(float) * 4, vertices.data(), GL_STATIC_DRAW);
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

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glLineWidth(lineWidth);
		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, 2);

		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderLine(const std::array<glm::vec2, 2>& vertices, Color3 color, float lineWidth, glm::mat4 model)
	{
		renderLine(vertices, Color4(color, 1.0F), lineWidth, model);
	}
	void renderLine(glm::vec2 p1, glm::vec2 p2, Color4 color, float lineWidth, glm::mat4 model)
	{
		renderLine({ p1, p2 }, color, lineWidth, model);
	}
	void renderLine(glm::vec2 p1, glm::vec2 p2, Color3 color, float lineWidth, glm::mat4 model)
	{
		renderLine({ p1, p2 }, Color4(color, 1.0F), lineWidth, model);
	}

	void renderLineStrip(const std::vector<glm::vec2>& vertices, Color4 color, float lineWidth, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		glNamedBufferData(vb, sizeof(float) * vertices.size() * 2, vertices.data(), GL_STATIC_DRAW);
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

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glLineWidth(lineWidth);
		glBindVertexArray(vao);
		glDrawArrays(GL_LINE_STRIP, 0, vertices.size());

		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderLineStrip(const std::vector<glm::vec2>& vertices, Color3 color, float lineWidth, glm::mat4 model)
	{
		renderLineStrip(vertices, Color4(color, 1.0F), lineWidth, model);
	}
	void renderLineLoop(const std::vector<glm::vec2>& vertices, Color4 color, float lineWidth, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		auto d = vertices.data();
		glNamedBufferData(vb, sizeof(float) * vertices.size() * 2, d, GL_STATIC_DRAW);
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

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glLineWidth(lineWidth);
		glBindVertexArray(vao);
		glDrawArrays(GL_LINE_LOOP, 0, vertices.size());

		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderLineLoop(const std::vector<glm::vec2>& vertices, Color3 color, float lineWidth, glm::mat4 model)
	{
		renderLineLoop(vertices, Color4(color, 1.0F), lineWidth, model);
	}

	void renderLines(const std::vector<std::array<glm::vec2, 2>>& lines, Color4 color, float lineWidth, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		unsigned int vb;
		glCreateBuffers(1, &vb);

		glNamedBufferData(vb, sizeof(float) * lines.size() * 4, lines.data(), GL_STATIC_DRAW);
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

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glLineWidth(lineWidth);
		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, lines.size() * 2);

		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderLines(const std::vector<std::array<glm::vec2, 2>>& lines, Color3 color, float lineWidth, glm::mat4 model)
	{
		renderLines(lines, Color4(color, 1.0F), lineWidth, model);
	}

	void renderCircle(glm::vec2 point, float radius, Color4 color, bool fill, float strokeWidth)
	{
		if (!Context::s_CurrentContext) return;

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		float outerRadius = radius, innerRadius = 0;
		if (!fill)
		{
			outerRadius += 0.5F * strokeWidth;
			innerRadius = radius - 0.5F * strokeWidth;
		}

		float buffer[30] {
			point.x - radius * 2.5F, point.y - radius * 2.5F, outerRadius, innerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
			point.x + radius * 2.5F, point.y - radius * 2.5F, outerRadius, innerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
			point.x, point.y + radius * 2.5F, outerRadius, innerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
		};

		unsigned int VB;
		glCreateBuffers(1, &VB);

		glNamedBufferData(VB, sizeof(float) * 30, buffer, GL_STATIC_DRAW);
		glVertexArrayVertexBuffer(vao, 0, VB, 0, sizeof(float) * 10);

		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);

		glVertexArrayAttribFormat(vao, 1, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 2);
		glVertexArrayAttribBinding(vao, 1, 0);
		glEnableVertexArrayAttrib(vao, 1);

		glVertexArrayAttribFormat(vao, 2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 3);
		glVertexArrayAttribBinding(vao, 2, 0);
		glEnableVertexArrayAttrib(vao, 2);

		glVertexArrayAttribFormat(vao, 3, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4);
		glVertexArrayAttribBinding(vao, 3, 0);
		glEnableVertexArrayAttrib(vao, 3);

		glVertexArrayAttribFormat(vao, 4, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8);
		glVertexArrayAttribBinding(vao, 4, 0);
		glEnableVertexArrayAttrib(vao, 4);

		if (!Program::colorCircleRenderer.isInitialized())
		{
			Program::colorCircleRenderer.initialize(ROOT_DIR "/src/SPrograms/ColorCircle");
		}

		Program::colorCircleRenderer.use();
		Program::colorCircleRenderer.uniMVP(Context::s_CurrentContext->getProjectionMatrix());

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDeleteBuffers(1, &VB);
		glDeleteVertexArrays(1, &vao);
	}
	void renderCircle(glm::vec2 point, float radius, Color3 color, bool fill, float strokeWidth)
	{
		renderCircle(point, radius, Color4(color, 1.0F), fill, strokeWidth);
	}

	void renderCircles(const std::vector<glm::vec2>& points, const std::vector<float>& radii, Color4 color, bool fill, float strokeWidth)
	{
		if (!Context::s_CurrentContext) return;

		unsigned int vao;
		glCreateVertexArrays(1, &vao);

		float* buffer = (float*)_alloca(sizeof(float) * 30 * points.size());

		for (unsigned int i = 0; i < points.size(); i++)
		{
			float outerRadius = radii[i], innerRadius = 0;
			if (!fill)
			{
				outerRadius += 0.5F * strokeWidth;
				innerRadius = radii[i] - 0.5F * strokeWidth;
			}

			float b[30]{
				points[i].x - radii[i] * 2.5F, points[i].y - radii[i] * 2.5F, outerRadius, innerRadius, color.r, color.g, color.b, color.a, points[i].x, points[i].y,
				points[i].x + radii[i] * 2.5F, points[i].y - radii[i] * 2.5F, outerRadius, innerRadius, color.r, color.g, color.b, color.a, points[i].x, points[i].y,
				points[i].x, points[i].y + radii[i] * 2.5F, outerRadius, innerRadius, color.r, color.g, color.b, color.a, points[i].x, points[i].y,
			};
			memcpy(buffer + i * 30, b, sizeof(float) * 30);
		}
		
		unsigned int VB;
		glCreateBuffers(1, &VB);

		glNamedBufferData(VB, sizeof(float) * 30 * points.size(), buffer, GL_STATIC_DRAW);
		glVertexArrayVertexBuffer(vao, 0, VB, 0, sizeof(float) * 10);

		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);

		glVertexArrayAttribFormat(vao, 1, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 2);
		glVertexArrayAttribBinding(vao, 1, 0);
		glEnableVertexArrayAttrib(vao, 1);

		glVertexArrayAttribFormat(vao, 2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 3);
		glVertexArrayAttribBinding(vao, 2, 0);
		glEnableVertexArrayAttrib(vao, 2);

		glVertexArrayAttribFormat(vao, 3, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4);
		glVertexArrayAttribBinding(vao, 3, 0);
		glEnableVertexArrayAttrib(vao, 3);

		glVertexArrayAttribFormat(vao, 4, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8);
		glVertexArrayAttribBinding(vao, 4, 0);
		glEnableVertexArrayAttrib(vao, 4);

		if (!Program::colorCircleRenderer.isInitialized())
		{
			Program::colorCircleRenderer.initialize(ROOT_DIR "/src/SPrograms/ColorCircle");
		}

		Program::colorCircleRenderer.use();
		Program::colorCircleRenderer.uniMVP(Context::s_CurrentContext->getProjectionMatrix());

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3*points.size());

		glDeleteBuffers(1, &VB);
		glDeleteVertexArrays(1, &vao);
	}
	void renderCircles(const std::vector<glm::vec2>& points, const std::vector<float>& radii, Color3 color, bool fill, float strokeWidth)
	{
		renderCircles(points, radii, Color4(color, 1.0F), fill, strokeWidth);
	}

	void renderRing(glm::vec2 point, float outerRadius, float innerRadius, Color4 color, bool fill, float strokeWidth)
	{
		if (!Context::s_CurrentContext) return;

		unsigned int vao, vb;
		glCreateVertexArrays(1, &vao);
		glCreateBuffers(1, &vb);

		if (fill)
		{
			float buffer[30]{
				point.x - outerRadius * 2.5F, point.y - outerRadius * 2.5F, outerRadius, innerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
				point.x + outerRadius * 2.5F, point.y - outerRadius * 2.5F, outerRadius, innerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
				point.x, point.y + outerRadius * 2.5F, outerRadius, innerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
			};

			glNamedBufferData(vb, sizeof(float) * 30, buffer, GL_STATIC_DRAW);
			glVertexArrayVertexBuffer(vao, 0, vb, 0, sizeof(float) * 10);
		}
		else
		{
			float oOuterRadius = outerRadius + 0.5F * strokeWidth, oInnerRadius = outerRadius - 0.5F * strokeWidth;
			float iOuterRadius = innerRadius + 0.5F * strokeWidth, iInnerRadius = innerRadius - 0.5F * strokeWidth;

			float buffer[60]{
				point.x - outerRadius * 2.5F, point.y - outerRadius * 2.5F, oOuterRadius, oInnerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
				point.x + outerRadius * 2.5F, point.y - outerRadius * 2.5F, oOuterRadius, oInnerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
				point.x, point.y + outerRadius * 2.5F, oOuterRadius, oInnerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
				point.x - outerRadius * 2.5F, point.y - outerRadius * 2.5F, iOuterRadius, iInnerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
				point.x + outerRadius * 2.5F, point.y - outerRadius * 2.5F, iOuterRadius, iInnerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
				point.x, point.y + outerRadius * 2.5F, iOuterRadius, iInnerRadius, color.r, color.g, color.b, color.a, point.x, point.y,
			};

			glNamedBufferData(vb, sizeof(float) * 60, buffer, GL_STATIC_DRAW);
			glVertexArrayVertexBuffer(vao, 0, vb, 0, sizeof(float) * 10);
		}
		
		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);

		glVertexArrayAttribFormat(vao, 1, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 2);
		glVertexArrayAttribBinding(vao, 1, 0);
		glEnableVertexArrayAttrib(vao, 1);

		glVertexArrayAttribFormat(vao, 2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 3);
		glVertexArrayAttribBinding(vao, 2, 0);
		glEnableVertexArrayAttrib(vao, 2);

		glVertexArrayAttribFormat(vao, 3, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4);
		glVertexArrayAttribBinding(vao, 3, 0);
		glEnableVertexArrayAttrib(vao, 3);

		glVertexArrayAttribFormat(vao, 4, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8);
		glVertexArrayAttribBinding(vao, 4, 0);
		glEnableVertexArrayAttrib(vao, 4);

		if (!Program::colorCircleRenderer.isInitialized())
		{
			Program::colorCircleRenderer.initialize(ROOT_DIR "/src/SPrograms/ColorCircle");
		}

		Program::colorCircleRenderer.use();
		Program::colorCircleRenderer.uniMVP(Context::s_CurrentContext->getProjectionMatrix());

		glBindVertexArray(vao);
		if (fill)
			glDrawArrays(GL_TRIANGLES, 0, 3);
		else
			glDrawArrays(GL_TRIANGLES, 0, 6);

		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderRing(glm::vec2 point, float outerRadius, float innerRadius, Color3 color, bool fill, float strokeWidth)
	{
		renderRing(point, outerRadius, innerRadius, Color4(color, 1.0F), fill, strokeWidth);
	}

	void renderRings(const std::vector<glm::vec2>& points, const std::vector<float>& outerRadii, const std::vector<float>& innerRadii, Color4 color, bool fill, float strokeWidth)
	{
		if (!Context::s_CurrentContext) return;

		unsigned int vao, vb;
		glCreateVertexArrays(1, &vao);
		glCreateBuffers(1, &vb);

		if (fill)
		{
			float* buffer = (float*)_alloca(sizeof(float) * 30 * points.size());
			for (unsigned int i = 0; i < points.size(); i++)
			{
				float b[30]{
					points[i].x - outerRadii[i] * 2.5F, points[i].y - outerRadii[i] * 2.5F, outerRadii[i], innerRadii[i], color.r, color.g, color.b, color.a, points[i].x, points[i].y,
					points[i].x + outerRadii[i] * 2.5F, points[i].y - outerRadii[i] * 2.5F, outerRadii[i], innerRadii[i], color.r, color.g, color.b, color.a, points[i].x, points[i].y,
					points[i].x, points[i].y + outerRadii[i] * 2.5F, outerRadii[i], innerRadii[i], color.r, color.g, color.b, color.a, points[i].x, points[i].y,
				};
				memcpy(buffer + i * 30, b, sizeof(float) * 30);
			}

			glNamedBufferData(vb, sizeof(float) * 30 * points.size(), buffer, GL_STATIC_DRAW);
			glVertexArrayVertexBuffer(vao, 0, vb, 0, sizeof(float) * 10);
		}
		else
		{
			float* buffer = (float*)_alloca(sizeof(float) * 60 * points.size());
			for (unsigned int i = 0; i < points.size(); i++)
			{
				float oOuterRadius = outerRadii[i] + 0.5F * strokeWidth, oInnerRadius = outerRadii[i] - 0.5F * strokeWidth;
				float iOuterRadius = innerRadii[i] + 0.5F * strokeWidth, iInnerRadius = innerRadii[i] - 0.5F * strokeWidth;

				float b[60]{
					points[i].x - outerRadii[i] * 2.5F, points[i].y - outerRadii[i] * 2.5F, oOuterRadius, oInnerRadius, color.r, color.g, color.b, color.a, points[i].x, points[i].y,
					points[i].x + outerRadii[i] * 2.5F, points[i].y - outerRadii[i] * 2.5F, oOuterRadius, oInnerRadius, color.r, color.g, color.b, color.a, points[i].x, points[i].y,
					points[i].x, points[i].y + outerRadii[i] * 2.5F, oOuterRadius, oInnerRadius, color.r, color.g, color.b, color.a, points[i].x, points[i].y,
					points[i].x - outerRadii[i] * 2.5F, points[i].y - outerRadii[i] * 2.5F, iOuterRadius, iInnerRadius, color.r, color.g, color.b, color.a, points[i].x, points[i].y,
					points[i].x + outerRadii[i] * 2.5F, points[i].y - outerRadii[i] * 2.5F, iOuterRadius, iInnerRadius, color.r, color.g, color.b, color.a, points[i].x, points[i].y,
					points[i].x, points[i].y + outerRadii[i] * 2.5F, iOuterRadius, iInnerRadius, color.r, color.g, color.b, color.a, points[i].x, points[i].y,
				};
				memcpy(buffer + i * 60, b, sizeof(float) * 60);
			}

			glNamedBufferData(vb, sizeof(float) * 60 * points.size(), buffer, GL_STATIC_DRAW);
			glVertexArrayVertexBuffer(vao, 0, vb, 0, sizeof(float) * 10);
		}

		glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(vao, 0, 0);
		glEnableVertexArrayAttrib(vao, 0);

		glVertexArrayAttribFormat(vao, 1, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 2);
		glVertexArrayAttribBinding(vao, 1, 0);
		glEnableVertexArrayAttrib(vao, 1);

		glVertexArrayAttribFormat(vao, 2, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 3);
		glVertexArrayAttribBinding(vao, 2, 0);
		glEnableVertexArrayAttrib(vao, 2);

		glVertexArrayAttribFormat(vao, 3, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4);
		glVertexArrayAttribBinding(vao, 3, 0);
		glEnableVertexArrayAttrib(vao, 3);

		glVertexArrayAttribFormat(vao, 4, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8);
		glVertexArrayAttribBinding(vao, 4, 0);
		glEnableVertexArrayAttrib(vao, 4);

		if (!Program::colorCircleRenderer.isInitialized())
		{
			Program::colorCircleRenderer.initialize(ROOT_DIR "/src/SPrograms/ColorCircle");
		}

		Program::colorCircleRenderer.use();
		Program::colorCircleRenderer.uniMVP(Context::s_CurrentContext->getProjectionMatrix());

		glBindVertexArray(vao);
		if (fill)
			glDrawArrays(GL_TRIANGLES, 0, 3 * points.size());
		else
			glDrawArrays(GL_TRIANGLES, 0, 6 * points.size());

		glDeleteBuffers(1, &vb);
		glDeleteVertexArrays(1, &vao);
	}
	void renderRings(const std::vector<glm::vec2>& points, const std::vector<float>& outerRadii, const std::vector<float>& innerRadii, Color3 color, bool fill, float strokeWidth)
	{
		renderRings(points, outerRadii, innerRadii, Color4(color, 1.0F), fill, strokeWidth);
	}

	void renderRegularPoly(glm::vec2 point, float radius, unsigned int nSided, float startAngle, Color4 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		double angDiff = glm::radians(360.0 / (double)nSided);

		std::vector<glm::vec2> vertices;
		if (fill)
		{
			vertices.push_back(point);
		}

		double L = glm::radians(startAngle); // L is a symbol of angle.
		for (unsigned int i = 0; i < nSided; i++, L+=angDiff)
		{
			vertices.push_back(point + (glm::vec2(glm::cos(L), glm::sin(L)) * radius));
		}

		if (fill)
		{
			vertices.push_back(vertices[1]);
			renderTriangleFan(vertices, color, fill, strokeWidth, model);
		}
		else
		{
			renderLineLoop(vertices, color, strokeWidth, model);
		}
	}
	void renderRegularPoly(glm::vec2 point, float radius, unsigned int nSided, float startAngle, Color3 color, bool fill, float strokeWidth, glm::mat4 model)
	{
		renderRegularPoly(point, radius, nSided, startAngle, Color4(color, 1.0F), fill, strokeWidth, model);
	}

	/* Renders - for Shape Classes */

	void renderTriangle(const Triangle& tri, Color4 color, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!tri.isInitialized() || tri.needsUpdate())
		{
			if (!tri.isInitialized())
			{
				glCreateVertexArrays(1, &tri.m_VAO);

				unsigned int vb;
				glCreateBuffers(1, &vb);
				glVertexArrayVertexBuffer(tri.m_VAO, 0, vb, 0, sizeof(float) * 2);
				glVertexArrayAttribBinding(tri.m_VAO, 0, 0);
				glVertexArrayAttribFormat(tri.m_VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
				glEnableVertexArrayAttrib(tri.m_VAO, 0);
				tri.m_VBOs.push_back(vb);

				tri.m_Initialized = true;
			}

			glNamedBufferData(tri.m_VBOs[0], sizeof(float) * 6, tri.get().data(), GL_STATIC_DRAW);
			tri.m_NeedsUpdate = false;
		}

		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(tri.m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	void renderTriangle(const Triangle& tri, Color3 color, glm::mat4 model)
	{
		renderTriangle(tri, Color4(color, 1.0F), model);
	}
	void renderTriangles(const Triangles& tris, Color4 color, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!tris.isInitialized() || tris.needsUpdate())
		{
			if (!tris.isInitialized())
			{
				glCreateVertexArrays(1, &tris.m_VAO);

				unsigned int vb;
				glCreateBuffers(1, &vb);
				glVertexArrayVertexBuffer(tris.m_VAO, 0, vb, 0, sizeof(float) * 2);
				glVertexArrayAttribBinding(tris.m_VAO, 0, 0);
				glVertexArrayAttribFormat(tris.m_VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
				glEnableVertexArrayAttrib(tris.m_VAO, 0);
				tris.m_VBOs.push_back(vb);

				tris.m_Initialized = true;
			}

			glNamedBufferData(tris.m_VBOs[0], sizeof(float) * 2 * tris.get().size(), tris.get().data(), GL_STATIC_DRAW);
			tris.m_NeedsUpdate = false;
		}

		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(tris.m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, tris.get().size());
	}
	void renderTriangles(const Triangles& tris, Color3 color, glm::mat4 model)
	{
		renderTriangles(tris, Color4(color, 1.0F), model);
	}
	void renderTriangleFan(const TriangleFan& triFan, Color4 color, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!triFan.isInitialized() || triFan.needsUpdate())
		{
			if (!triFan.isInitialized())
			{
				glCreateVertexArrays(1, &triFan.m_VAO);

				unsigned int vb;
				glCreateBuffers(1, &vb);
				glVertexArrayVertexBuffer(triFan.m_VAO, 0, vb, 0, sizeof(float) * 2);
				glVertexArrayAttribBinding(triFan.m_VAO, 0, 0);
				glVertexArrayAttribFormat(triFan.m_VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
				glEnableVertexArrayAttrib(triFan.m_VAO, 0);
				triFan.m_VBOs.push_back(vb);

				triFan.m_Initialized = true;
			}

			glNamedBufferData(triFan.m_VBOs[0], sizeof(float) * 2 * triFan.get().size(), triFan.get().data(), GL_STATIC_DRAW);
			triFan.m_NeedsUpdate = false;
		}

		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(triFan.m_VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, triFan.get().size());
	}
	void renderTriangleFan(const TriangleFan& triFan, Color3 color, glm::mat4 model)
	{
		renderTriangleFan(triFan, Color4(color, 1.0F), model);
	}

	void renderQuad(const Quad& quad, Color4 color, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!quad.isInitialized() || quad.needsUpdate())
		{
			if (!quad.isInitialized())
			{
				glCreateVertexArrays(1, &quad.m_VAO);

				unsigned int vb;
				glCreateBuffers(1, &vb);
				glVertexArrayVertexBuffer(quad.m_VAO, 0, vb, 0, sizeof(float) * 2);
				glVertexArrayAttribBinding(quad.m_VAO, 0, 0);
				glVertexArrayAttribFormat(quad.m_VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
				glEnableVertexArrayAttrib(quad.m_VAO, 0);
				quad.m_VBOs.push_back(vb);

				quad.m_Initialized = true;
			}

			glNamedBufferData(quad.m_VBOs[0], sizeof(float) * 8, quad.get().data(), GL_STATIC_DRAW);
			quad.m_NeedsUpdate = false;
		}

		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(quad.m_VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
	void renderQuad(const Quad& quad, Color3 color, glm::mat4 model)
	{
		renderQuad(quad, Color4(color, 1.0F), model);
	}
	void renderQuads(const Quads& quads, Color4 color, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		const unsigned int totalQuads = quads.totalQuads();
		const unsigned int totalElements = totalQuads * 6u;
		if (!quads.isInitialized() || quads.needsUpdate())
		{
			if (!quads.isInitialized())
			{
				glCreateVertexArrays(1, &quads.m_VAO);

				unsigned int vb;
				glCreateBuffers(1, &vb);
				glVertexArrayVertexBuffer(quads.m_VAO, 0, vb, 0, sizeof(float) * 2);
				glVertexArrayAttribBinding(quads.m_VAO, 0, 0);
				glVertexArrayAttribFormat(quads.m_VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
				glEnableVertexArrayAttrib(quads.m_VAO, 0);
				quads.m_VBOs.push_back(vb);

				quads.m_Initialized = true;
			}

			if (quads.m_ElementsAdded)
			{
				std::vector<unsigned int> eb;
				eb.reserve(totalElements);
				for (unsigned int i = 0; i < totalQuads; i++)
				{
					unsigned int i4 = i * 4u;
					eb.push_back(i4);
					eb.push_back(i4 + 1);
					eb.push_back(i4 + 2);
					eb.push_back(i4 + 1);
					eb.push_back(i4 + 2);
					eb.push_back(i4 + 3);
				}
				quads.setEBO(eb);
				quads.m_ElementsAdded = false;
			}

			glNamedBufferData(quads.m_VBOs[0], sizeof(float) * 2 * quads.get().size(), quads.get().data(), GL_STATIC_DRAW);
			quads.m_NeedsUpdate = false;
		}

		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(quads.m_VAO);
		glDrawElements(GL_TRIANGLES, totalElements, GL_UNSIGNED_INT, nullptr);
	}
	void renderQuads(const Quads& quads, Color3 color, glm::mat4 model)
	{
		renderQuads(quads, Color4(color, 1.0F), model);
	}

	void renderPoly(const Polygon& poly, Color4 color, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!poly.isInitialized() || poly.needsUpdate())
		{
			if (!poly.isInitialized())
			{
				glCreateVertexArrays(1, &poly.m_VAO);

				unsigned int vb;
				glCreateBuffers(1, &vb);
				glVertexArrayVertexBuffer(poly.m_VAO, 0, vb, 0, sizeof(float) * 2);
				glVertexArrayAttribBinding(poly.m_VAO, 0, 0);
				glVertexArrayAttribFormat(poly.m_VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
				glEnableVertexArrayAttrib(poly.m_VAO, 0);
				poly.m_VBOs.push_back(vb);

				poly.m_Initialized = true;
			}

			glNamedBufferData(poly.m_VBOs[0], sizeof(float) * 2 * poly.get().size(), poly.get().data(), GL_STATIC_DRAW);
			poly.m_NeedsUpdate = false;
		}

		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glBindVertexArray(poly.m_VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, poly.get().size());
	}
	void renderPoly(const Polygon& poly, Color3 color, glm::mat4 model)
	{
		renderPoly(poly, Color4(color, 1.0F), model);
	}
	void renderLine(const Line& line, Color4 color, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!line.isInitialized() || line.needsUpdate())
		{
			if (!line.isInitialized())
			{
				glCreateVertexArrays(1, &line.m_VAO);
				unsigned int vb;
				glCreateBuffers(1, &vb);

				glVertexArrayVertexBuffer(line.m_VAO, 0, vb, 0, sizeof(float) * 2);
				glVertexArrayAttribFormat(line.m_VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
				glVertexArrayAttribBinding(line.m_VAO, 0, 0);
				glEnableVertexArrayAttrib(line.m_VAO, 0);
				line.m_VBOs.push_back(vb);

				line.m_Initialized = true;
			}

			glNamedBufferData(line.m_VBOs[0], sizeof(float) * 4, line.get().data(), GL_STATIC_DRAW);
			line.m_NeedsUpdate = false;
		}
		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glLineWidth(line.getLineWidth());
		glBindVertexArray(line.m_VAO);
		glDrawArrays(GL_LINES, 0, 2);
	}
	void renderLines(const Lines& lines, Color4 color, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!lines.isInitialized() || lines.needsUpdate())
		{
			if (!lines.isInitialized())
			{
				glCreateVertexArrays(1, &lines.m_VAO);
				unsigned int vb;
				glCreateBuffers(1, &vb);

				glVertexArrayVertexBuffer(lines.m_VAO, 0, vb, 0, sizeof(float) * 2);
				glVertexArrayAttribFormat(lines.m_VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
				glVertexArrayAttribBinding(lines.m_VAO, 0, 0);
				glEnableVertexArrayAttrib(lines.m_VAO, 0);
				lines.m_VBOs.push_back(vb);

				lines.m_Initialized = true;
			}

			glNamedBufferData(lines.m_VBOs[0], sizeof(float) * lines.get().size() * 2u, lines.get().data(), GL_STATIC_DRAW);
			lines.m_NeedsUpdate = false;
		}
		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glLineWidth(lines.getLineWidth());
		glBindVertexArray(lines.m_VAO);
		glDrawArrays(GL_LINES, 0, lines.get().size());
	}
	void renderLineStrip(const LineStrip& lineStrip, Color4 color, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!lineStrip.isInitialized() || lineStrip.needsUpdate())
		{
			if (!lineStrip.isInitialized())
			{
				glCreateVertexArrays(1, &lineStrip.m_VAO);
				unsigned int vb;
				glCreateBuffers(1, &vb);

				glVertexArrayVertexBuffer(lineStrip.m_VAO, 0, vb, 0, sizeof(float) * 2);
				glVertexArrayAttribFormat(lineStrip.m_VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
				glVertexArrayAttribBinding(lineStrip.m_VAO, 0, 0);
				glEnableVertexArrayAttrib(lineStrip.m_VAO, 0);
				lineStrip.m_VBOs.push_back(vb);

				lineStrip.m_Initialized = true;
			}

			glNamedBufferData(lineStrip.m_VBOs[0], sizeof(float) * lineStrip.get().size() * 2u, lineStrip.get().data(), GL_STATIC_DRAW);

		}
		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glLineWidth(lineStrip.getLineWidth());
		glBindVertexArray(lineStrip.m_VAO);
		glDrawArrays(GL_LINE_STRIP, 0, lineStrip.get().size());
	}
	void renderLineLoop(const LineLoop& lineLoop, Color4 color, glm::mat4 model)
	{
		if (!Context::s_CurrentContext) return;

		if (!lineLoop.isInitialized() || lineLoop.needsUpdate())
		{
			if (!lineLoop.isInitialized())
			{
				glCreateVertexArrays(1, &lineLoop.m_VAO);
				unsigned int vb;
				glCreateBuffers(1, &vb);

				glVertexArrayVertexBuffer(lineLoop.m_VAO, 0, vb, 0, sizeof(float) * 2);
				glVertexArrayAttribFormat(lineLoop.m_VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
				glVertexArrayAttribBinding(lineLoop.m_VAO, 0, 0);
				glEnableVertexArrayAttrib(lineLoop.m_VAO, 0);
				lineLoop.m_VBOs.push_back(vb);

				lineLoop.m_Initialized = true;
			}

			glNamedBufferData(lineLoop.m_VBOs[0], sizeof(float) * lineLoop.get().size() * 2u, lineLoop.get().data(), GL_STATIC_DRAW);

		}
		if (!Program::colorRenderer.isInitialized())
		{
			Program::colorRenderer.initialize(ROOT_DIR "/src/SPrograms/Color");
		}

		Program::colorRenderer.use();
		Program::colorRenderer.uni4f("uColor", color);

		Program::colorRenderer.uniMVP({ Context::s_CurrentContext->getProjectionMatrix(), glm::mat4(1.0F), model });

		glLineWidth(lineLoop.getLineWidth());
		glBindVertexArray(lineLoop.m_VAO);
		glDrawArrays(GL_LINE_LOOP, 0, lineLoop.get().size());
	}

	void render(const Shape& shape, Color4 color, glm::mat4 model)
	{
		switch (shape.getPrimitive())
		{
		case Primitive::TRIANGLE:
			renderTriangle(shape, color, model);
			return;
		case Primitive::TRIANGLES:
			renderTriangles(shape, color, model);
			return;
		case Primitive::TRIANGLE_FAN:
			renderTriangleFan(shape, color, model);
			return;
		case Primitive::QUAD:
			renderQuad(shape, color, model);
			return;
		case Primitive::QUADS:
			renderQuads(shape, color, model);
			return;
		case Primitive::POLYGON:
			renderPoly(shape, color, model);
			return;
		case Primitive::LINE:
			renderLine(shape, color, model);
			return;
		case Primitive::LINES:
			renderLines(shape, color, model);
			return;
		case Primitive::LINE_STRIP:
			renderLineStrip(shape, color, model);
			return;
		case Primitive::LINE_LOOP:
			renderLineLoop(shape, color, model);
			return;
		default:
			throw std::exception("Unknown shape found with no render definition!");
		}
	}
} 