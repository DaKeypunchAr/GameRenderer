#ifndef _Renderer_Hpp
#define _Renderer_Hpp

#include "Shapes.hpp"

namespace DK
{
	void renderTriangle(const std::array<glm::vec2, 3>& vertices, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderTriangle(const std::array<glm::vec2, 3>& vertices, Color3 color = WHITE, bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderTriangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, Color3 color = WHITE, bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));

	void renderTriangles(const std::vector<std::array<glm::vec2, 3>>& vertices, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderTriangles(const std::vector<std::array<glm::vec2, 3>>&, Color3 color = WHITE, bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderTriangleFan(const std::vector<glm::vec2>& vertices, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderTriangleFan(const std::vector<glm::vec2>& vertices, Color3 color = WHITE , bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));

	void renderQuad(const std::array<glm::vec2, 4>& vertices, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderQuad(const std::array<glm::vec2, 4>& vertices, Color3 color = WHITE, bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderQuad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderQuad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4, Color3 color = WHITE, bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));

	void renderQuads(const std::vector<std::array<glm::vec2, 4>>& quads, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderQuads(const std::vector<std::array<glm::vec2, 4>>& quads, Color3 color = WHITE, bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));

	/* after the first two points. every other point must use the previous point to be a triangle in the polygon you want. */
	void renderPoly(const std::vector<glm::vec2>& vertices, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderPoly(const std::vector<glm::vec2>& vertices, Color3 color = WHITE, bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));

	void renderPolys(const std::vector<std::vector<glm::vec2>>& vertices, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderPolys(const std::vector<std::vector<glm::vec2>>& vertices, Color3 color = WHITE, bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));

	static const unsigned char LINE_ENDS_BAD = 0;
	static const unsigned char LINE_ENDS_GOOD = 1;

	void renderLine(const std::array<glm::vec2, 2>& vertices, Color4 color = Color4(WHITE, 1.0F), float lineWidth = 1.0F, unsigned char lineType = LINE_ENDS_BAD, glm::mat4 model = glm::mat4(1.0F));
	void renderLine(const std::array<glm::vec2, 2>& vertices, Color3 color = WHITE, float lineWidth = 1.0F, unsigned char lineType = LINE_ENDS_BAD, glm::mat4 model = glm::mat4(1.0F));
	void renderLine(glm::vec2 p1, glm::vec2 p2, Color4 color = Color4(WHITE, 1.0F), float lineWidth = 1.0F, unsigned char lineType = LINE_ENDS_BAD, glm::mat4 model = glm::mat4(1.0F));
	void renderLine(glm::vec2 p1, glm::vec2 p2, Color3 color, float lineWidth = 1.0F, unsigned char lineType = LINE_ENDS_BAD, glm::mat4 model = glm::mat4(1.0F));

	void renderLineStrip(const std::vector<glm::vec2>& vertices, Color4 color = Color4(WHITE, 1.0F), float lineWidth = 1.0F, unsigned char lineType = LINE_ENDS_BAD, glm::mat4 model = glm::mat4(1.0F));
	void renderLineStrip(const std::vector<glm::vec2>& vertices, Color3 color = WHITE, float lineWidth = 1.0F, unsigned char lineType = LINE_ENDS_BAD, glm::mat4 model = glm::mat4(1.0F));
	void renderLineLoop(const std::vector<glm::vec2>& vertices, Color4 color = Color4(WHITE, 1.0F), float lineWidth = 1.0F, unsigned char lineType = LINE_ENDS_BAD, glm::mat4 model = glm::mat4(1.0F));
	void renderLineLoop(const std::vector<glm::vec2>& vertices, Color3 color = WHITE, float lineWidth = 1.0F, unsigned char lineType = LINE_ENDS_BAD, glm::mat4 model = glm::mat4(1.0F));

	void renderLines(const std::vector<std::array<glm::vec2, 2>>& vertices, Color4 color = Color4(DK::WHITE, 1.0F), float lineWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderLines(const std::vector<std::array<glm::vec2, 2>>& vertices, Color3 color = DK::WHITE, float lineWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));

	void renderCircle(glm::vec2 point, float radius, Color4 color = Color4(DK::WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F);
	void renderCircle(glm::vec2 point, float radius, Color3 color, bool fill = true, float strokeWidth = 1.0F);

	void renderCircles(const std::vector<glm::vec2>& point, const std::vector<float>& radius, Color4 color = Color4(WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F);
	void renderCircles(const std::vector<glm::vec2>& point, const std::vector<float>& radius, Color3 color = WHITE, bool fill = true, float strokeWidth = 1.0F);

	void renderRing(glm::vec2 point, float outerRadius, float innerRadius, Color4 color = Color4(DK::WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F);
	void renderRing(glm::vec2 point, float outerRadius, float innerRadius, Color3 color, bool fill = true, float strokeWidth = 1.0F);

	void renderRings(const std::vector<glm::vec2>& point, const std::vector<float>& outerRadius, const std::vector<float>& innerRadius, Color4 color = Color4(DK::WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F);
	void renderRings(const std::vector<glm::vec2>& point, const std::vector<float>& outerRadius, const std::vector<float>& innerRadius, Color3 color, bool fill = true, float strokeWidth = 1.0F);

	void renderRegularPoly(glm::vec2 point, float radius, unsigned int nSidedPoly, float startAngle = 0.0F, Color4 color = Color4(DK::WHITE, 1.0F), bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
	void renderRegularPoly(glm::vec2 point, float radius, unsigned int nSidedPoly, float startAngle = 0.0F, Color3 color = DK::WHITE, bool fill = true, float strokeWidth = 1.0F, glm::mat4 model = glm::mat4(1.0F));
}

#endif