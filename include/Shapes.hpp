#ifndef _Shapes_Hpp
#define _Shapes_Hpp

#include "Context.hpp"
#include "ShaderProgram.hpp"
#include <array>

namespace DK
{
	class Shape;

	enum class Primitive
	{
		NONE,

		TRIANGLE,
		TRIANGLES,
		TRIANGLE_FAN,

		QUAD,
		QUADS,

		POLYGON,
	};

	void render(const Shape& shape, Color4 color = Color4(WHITE, 1.0F), glm::mat4 model = glm::mat4(1.0F));
	void render(const Shape& shape, Color3 color = WHITE, glm::mat4 model = glm::mat4(1.0F));

	class Shape
	{
	public:
		Shape() = delete;
		~Shape();

		void setVertex(unsigned int i, glm::vec2 val);
		glm::vec2 getVertex(unsigned int i) const;
		const glm::vec2& operator[](int i) const;

		const std::vector<glm::vec2>& get() const;

		bool isInitialized() const noexcept;
		bool needsUpdate() const noexcept;
		Primitive getPrimitive() const noexcept;

		friend void render(const Shape& shape, Color4 color, glm::mat4 model);

	protected:
		Shape(const std::vector<glm::vec2>& vertices, Primitive primitive);
		void setEBO(const std::vector<unsigned int>& eb) const;

	protected:
		mutable Primitive m_Primitive = Primitive::NONE;
		mutable unsigned int m_VAO;
		mutable std::vector<unsigned int> m_VBOs;
		mutable unsigned int m_EBO;

		std::vector<glm::vec2> m_Vertices;
		mutable bool m_Initialized = false;
		mutable bool m_NeedsUpdate = true;
		mutable bool m_UsesEBO = false;
	};

	class Triangle;
	class Triangles;
	class Quad;
	class Quads;
	class Polygon;
	class TriangleFan;

	void renderTriangle(const Triangle& tri, Color4 color = Color4(WHITE, 1.0F), glm::mat4 model = glm::mat4(1.0F));
	void renderTriangle(const Triangle& tri, Color3 color = WHITE, glm::mat4 model = glm::mat4(1.0F));

	void renderTriangles(const Triangles& tris, Color4 color = Color4(WHITE, 1.0F), glm::mat4 model = glm::mat4(1.0F));
	void renderTriangles(const Triangles& tris, Color3 color = WHITE, glm::mat4 model = glm::mat4(1.0F));

	void renderQuad(const Quad& quad, Color4 color = Color4(WHITE, 1.0F), glm::mat4 model = glm::mat4(1.0F));
	void renderQuad(const Quad& quad, Color3 color = WHITE, glm::mat4 model = glm::mat4(1.0F));

	void renderQuads(const Quads& quads, Color4 color = Color4(WHITE, 1.0F), glm::mat4 model = glm::mat4(1.0F));
	void renderQuads(const Quads& quads, Color3 color = WHITE, glm::mat4 model = glm::mat4(1.0F));

	void renderPoly(const Polygon& poly, Color4 color = Color4(WHITE, 1.0F), glm::mat4 model = glm::mat4(1.0F));
	void renderPoly(const Polygon& poly, Color3 color = WHITE, glm::mat4 model = glm::mat4(1.0F));

	void renderTriangleFan(const TriangleFan& triFan, Color4 color = Color4(WHITE, 1.0F), glm::mat4 model = glm::mat4(1.0F));
	void renderTriangleFan(const TriangleFan& triFan, Color3 color = WHITE, glm::mat4 model = glm::mat4(1.0F));

	class Triangle : public Shape
	{
	public:
		Triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3);
		Triangle(const std::array<glm::vec2, 3>& vertices);
		Triangle(const Triangle& tri);
		~Triangle() = default;

		friend void renderTriangle(const Triangle& tri, Color4 color, glm::mat4 model);
	};

	class Triangles : public Shape
	{
	public:
		Triangles(const std::vector<Triangle>& tris);
		Triangles(const std::vector<Triangles>& tris);
		Triangles(const std::vector<TriangleFan>& triFans);
		Triangles(const std::vector<Quad>& quads);
		Triangles(const std::vector<Quads>& quads);
		Triangles(const std::vector<Polygon>& polys);
		~Triangles() = default;

		void add(const std::vector<Triangle>& tris);
		void add(const std::vector<Triangles>& tris);
		void add(const std::vector<TriangleFan>& triFans);
		void add(const std::vector<Quad>& quads);
		void add(const std::vector<Quads>& quads);
		void add(const std::vector<Polygon>& polys);

		void update(unsigned int triIdx, const Triangle& tri);
		void update(unsigned int triIdx, const Triangles& tris);
		void update(unsigned int triIdx, const TriangleFan& triFan);
		void update(unsigned int triIdx, const Quad& quad);
		void update(unsigned int triIdx, const Quads& quads);
		void update(unsigned int triIdx, const Polygon& poly);

		Triangle getTriAt(unsigned int i) const;
		unsigned int totalTriangles() const { return m_Vertices.size() / 3u; }

		friend void renderTriangles(const Triangles& tris, Color4 color, glm::mat4 model);
	};

	class Quad : public Shape
	{
	public:
		Quad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4);
		Quad(glm::vec4 bl, glm::vec4 br);
		Quad(const std::array<glm::vec2, 4>& quad);
		Quad(const Quad& quad);

		friend void renderQuad(const Quad& quad, Color4 color, glm::mat4 model);
	};

	class Quads : public Shape
	{
	public:
		Quads(const std::vector<Quad>& quads);
		Quads(const std::vector<Quads>& quads);
		~Quads() = default;

		void add(const std::vector<Quad>& quads);
		void add(const std::vector<Quads>& quads);

		Quad getQuadAt(unsigned int i) const;
		unsigned int totalQuads() const { return m_Vertices.size() / 4u; }

		friend void renderQuads(const Quads& quads, Color4 color, glm::mat4 model);

	protected:
		mutable bool m_ElementsAdded = true;
	};

	class Polygon : public Shape
	{
	public:
		Polygon(const std::vector<glm::vec2>& vertices);
		Polygon(const Triangle& tri);
		Polygon(const Quad& quad);
		Polygon(const Polygon& poly);
		~Polygon() = default;

		void add(const std::vector<glm::vec2>& points);

		friend void renderPoly(const Polygon& triStrip, Color4 color, glm::mat4 model);
	};

	class TriangleFan : public Shape
	{
	public:
		TriangleFan(glm::vec2 centerPoint);
		TriangleFan(glm::vec2 centerPoint, const std::vector<glm::vec2>& lines);
		TriangleFan(const TriangleFan& tri);
		~TriangleFan() = default;

		void setCenterPoint(glm::vec2 p);

		void add(const std::vector<glm::vec2>& points);

		Triangle getTriAt(unsigned int i) const;

		friend void renderTriangleFan(const TriangleFan& triFan, Color4 color, glm::mat4 model);

	public:
		static TriangleFan makeRegularPoly(unsigned int nSided, float radius);
	};

}

#endif