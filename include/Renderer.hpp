#ifndef _Renderer_Hpp
#define _Renderer_Hpp

#include "Context.hpp"
#include "ShaderProgram.hpp"

#include <array>

namespace DK
{
	void renderTriangle(const std::array<glm::vec2, 3>& vertices, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 0.0F);
	void renderTriangle(const std::array<glm::vec2, 3>& vertices, Color3 color = WHITE, bool fill = true, float strokeWidth = 0.0F);
	void renderTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 0.0F);
	void renderTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color3 color = WHITE, bool fill = true, float strokeWidth = 0.0F);

	void renderQuad(const std::array<glm::vec2, 4>& vertices, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 0.0F);
	void renderQuad(const std::array<glm::vec2, 4>& vertices, Color3 color = WHITE, bool fill = true, float strokeWidth = 0.0F);
	void renderQuad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 0.0F);
	void renderQuad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4, Color3 color = WHITE, bool fill = true, float strokeWidth = 0.0F);

	/* after the first two points. every other point must use the previous point to be a triangle in the polygon you want. */
	void renderPoly(const std::vector<glm::vec2>& vertices, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 0.0F);
	void renderPoly(const std::vector<glm::vec2>& vertices, Color3 color = WHITE, bool fill = true, float strokeWidth = 0.0F);

	void renderLine(const std::array<glm::vec2, 2>& vertices, Color4 color = Color4(BLACK, 1.0F), float lineWidth = 2.0F);
	void renderLine(const std::array<glm::vec2, 2>& vertices, Color3 color = BLACK, float lineWidth = 2.0F);
	void renderLine(glm::vec2 p1, glm::vec2 p2, Color4 color = Color4(BLACK, 1.0F), float lineWidth = 2.0F);
	void renderLine(glm::vec2 p1, glm::vec2 p2, Color3 color, float lineWidth = 2.0F);

	void renderCircle(glm::vec2 point, float radius, Color4 color = Color4(DK::WHITE, 1.0F), bool fill = true, float strokeWidth = 0.0F);
	void renderCircle(glm::vec2 point, float radius, Color3 color, bool fill = true, float strokeWidth = 0.0F);

	void renderRing(glm::vec2 point, float outerRadius, float innerRadius, Color4 color = Color4(DK::WHITE, 1.0F), bool fill = true, float strokeWidth = 0.0F);
	void renderRing(glm::vec2 point, float outerRadius, float innerRadius, Color3 color, bool fill = true, float strokeWidth = 0.0F);
}

#endif