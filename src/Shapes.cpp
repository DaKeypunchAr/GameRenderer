#include "Shapes.hpp"

namespace DK
{
	template <typename T>
	static void ammendVector(const std::vector<T>& source, std::vector<T>& destination)
	{
		for (unsigned int i = 0; i < source.size(); i++)
		{
			destination.push_back(source[i]);
		}
	}

	/* Shape */
	Shape::Shape(const std::vector<glm::vec2>& vertices, Primitive primitive)
		: m_Vertices(vertices), m_Primitive(primitive) {}
	Shape::Shape(const Shape& shape)
		: m_Vertices(shape.get()), m_Primitive(shape.getPrimitive()) {}
	Shape::~Shape()
	{
		if (!m_Initialized) return;
		glDeleteVertexArrays(1, &m_VAO);
		for (unsigned int vb : m_VBOs)
		{
			glDeleteBuffers(1, &vb);
		}
		if (!m_UsesEBO) return;
		glDeleteBuffers(1, &m_EBO);
	}
	void Shape::setEBO(const std::vector<unsigned int>& indices) const
	{
		if (!m_UsesEBO)
		{
			glCreateBuffers(1, &m_EBO);
			glVertexArrayElementBuffer(m_VAO, m_EBO);
			m_UsesEBO = true;
		}

		glNamedBufferData(m_EBO, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	}

	const glm::vec2& Shape::operator[](int i) const
	{
		if (i < 0 || i >= m_Vertices.size()) throw std::exception("Index out of bounds!");
		return m_Vertices[i];
	}
	void Shape::setVertex(unsigned int i, glm::vec2 vertex)
	{
		if (i < 0 || i >= m_Vertices.size()) throw std::exception("Index out of bounds!");
		m_NeedsUpdate = true;
		m_Vertices[i] = vertex;
	}
	glm::vec2 Shape::getVertex(unsigned int i) const
	{
		if (i < 0 || i >= m_Vertices.size()) throw std::exception("Vertex out of bounds!");
		return m_Vertices[i];
	}
	const std::vector<glm::vec2>& Shape::get() const
	{
		return m_Vertices;
	}

	bool Shape::isInitialized() const noexcept
	{
		return m_Initialized;
	}
	bool Shape::needsUpdate() const noexcept
	{
		return m_NeedsUpdate;
	}
	Primitive Shape::getPrimitive() const noexcept
	{
		return m_Primitive;
	}

	/* Shape - Triangle */
	Triangle::Triangle(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
		: Shape({ p1,p2,p3 }, Primitive::TRIANGLE) {}
	Triangle::Triangle(const std::array<glm::vec2, 3>& tri)
		: Shape(std::vector<glm::vec2>(tri.begin(), tri.end()), Primitive::TRIANGLE) {}
	Triangle::Triangle(const Triangle& tri)
		: Shape(tri.get(), Primitive::TRIANGLE) {}

	/* Shape - Triangles */
	Triangles::Triangles(const std::vector<Triangle>& triangles)
		: Shape({}, Primitive::TRIANGLES)
	{
		add(triangles);
	}
	Triangles::Triangles(const std::vector<Triangles>& triangles)
		: Shape({}, Primitive::TRIANGLES)
	{
		add(triangles);
	}
	Triangles::Triangles(const std::vector<TriangleFan>& triangleFans)
		: Shape({}, Primitive::TRIANGLES)
	{
		add(triangleFans);
	}
	Triangles::Triangles(const std::vector<Quad>& quads)
		: Shape({}, Primitive::TRIANGLES)
	{
		add(quads);
	}
	Triangles::Triangles(const std::vector<Quads>& quads)
		: Shape({}, Primitive::TRIANGLES)
	{
		add(quads);
	}
	Triangles::Triangles(const std::vector<Polygon>& polygons)
		: Shape({}, Primitive::TRIANGLES)
	{
		add(polygons);
	}

	void Triangles::add(const std::vector<Triangle>& triangles)
	{
		m_NeedsUpdate = true;
		for (const auto& tri : triangles)
		{
			ammendVector(tri.get(), m_Vertices);
		}
	}
	void Triangles::add(const std::vector<Triangles>& triangles)
	{
		m_NeedsUpdate = true;
		for (const auto& tri : triangles)
		{
			ammendVector(tri.get(), m_Vertices);
		}
	}
	void Triangles::add(const std::vector<Quad>& quads)
	{
		m_NeedsUpdate = true;
		for (const auto& quad : quads)
		{
			ammendVector({ quad[0], quad[1], quad[2], quad[1], quad[2], quad[3] }, m_Vertices);
		}
	}
	void Triangles::add(const std::vector<Quads>& quads)
	{
		m_NeedsUpdate = true;
		for (const auto& quad : quads)
		{
			for (unsigned int i = 0; i < quad.totalQuads(); i++)
			{
				const auto& q = quad.getQuadAt(i);
				ammendVector({ q[0], q[1], q[2], q[1], q[2], q[3] }, m_Vertices);
			}
		}
	}
	void Triangles::add(const std::vector<Polygon>& polygons)
	{
		m_NeedsUpdate = true;
		for (const auto& poly : polygons)
		{
			const auto& v = poly.get();
			for (unsigned int i = 2; i < v.size(); i++)
			{
				ammendVector({ v[0], v[1], v[2] }, m_Vertices);
			}
		}
	}
	void Triangles::add(const std::vector<TriangleFan>& triFans)
	{
		for (const auto& triFan : triFans)
		{
			glm::vec2 cPoint = triFan[0];
			for (unsigned int i = 2; i < m_Vertices.size(); i++)
			{
				ammendVector({ cPoint, triFan[i - 1], triFan[i] }, m_Vertices);
			}
		}
	}

	void Triangles::update(unsigned int triIdx, const Triangles& tris)
	{
		unsigned int vertexIdx = triIdx * 3u;
		if (vertexIdx + tris.get().size() > m_Vertices.size()) throw std::exception("Index out of bound!");

		for (unsigned int i = 0, j = vertexIdx; i < tris.get().size(); i++, j++)
		{
			m_Vertices[j] = tris[i];
		}
		m_NeedsUpdate = true;
	}
	void Triangles::update(unsigned int triIdx, const Triangle& tri)
	{
		std::vector<Triangle> tris = { tri };
		update(triIdx, Triangles(tris));
	}
	void Triangles::update(unsigned int triIdx, const TriangleFan& triFan)
	{
		std::vector<TriangleFan> triFans = { triFan };
		update(triIdx, Triangles(triFans));
	}
	void Triangles::update(unsigned int triIdx, const Quad& quad)
	{
		std::vector<Quad> quads = { quad };
		update(triIdx, Triangles(quads));
	}
	void Triangles::update(unsigned int triIdx, const Quads& _quads)
	{
		std::vector<Quads> quads = { _quads };
		update(triIdx, Triangles(quads));
	}
	void Triangles::update(unsigned int triIdx, const Polygon& polygon)
	{
		std::vector<Polygon> poly = { polygon };
		update(triIdx, Triangles(poly));
	}

	Triangle Triangles::getTriAt(unsigned int triIdx) const
	{
		unsigned int vIdx = triIdx * 3u;
		if (vIdx + 3u > m_Vertices.size()) throw std::exception("Triangle not found!");

		return { m_Vertices[vIdx], m_Vertices[vIdx + 1], m_Vertices[vIdx + 2] };
	}

	/* Shapes - Quad */
	Quad::Quad(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4)
		: Shape({ p1, p2, p3, p4 }, Primitive::QUAD) {}
	Quad::Quad(glm::vec4 bl, glm::vec4 tr)
		: Shape({ bl, glm::vec2(bl.x, tr.y), glm::vec2(tr.x, bl.y), tr }, Primitive::QUAD) {}
	Quad::Quad(const std::array<glm::vec2, 4>& quad)
		: Shape(std::vector<glm::vec2>(quad.begin(), quad.end()), Primitive::QUAD) {}
	Quad::Quad(const Quad& quad)
		: Shape(quad.get(), Primitive::QUAD) {}

	/* Shapes - Quads */
	Quads::Quads(const std::vector<Quad>& quads)
		: Shape({}, Primitive::QUADS)
	{
		add(quads);
	}
	Quads::Quads(const std::vector<Quads>& quads)
		: Shape({}, Primitive::QUADS)
	{
		add(quads);
	}

	void Quads::add(const std::vector<Quad>& quads)
	{
		for (const auto& q : quads)
		{
			ammendVector(q.get(), m_Vertices);
		}
		m_NeedsUpdate = true;
	}
	void Quads::add(const std::vector<Quads>& quads)
	{
		for (const auto& q : quads)
		{
			ammendVector(q.get(), m_Vertices);
		}
		m_NeedsUpdate = true;
	}

	void Quads::update(unsigned int quadIdx, const Quad& quad)
	{
		unsigned int vIdx = quadIdx * 4u;
		if (vIdx + 4u > m_Vertices.size()) throw std::exception("Index out of bounds!");

		m_Vertices[vIdx] = quad[0];
		m_Vertices[vIdx + 1] = quad[1];
		m_Vertices[vIdx + 2] = quad[2];
		m_Vertices[vIdx + 3] = quad[3];

		m_NeedsUpdate = true;
	}
	void Quads::update(unsigned int quadIdx, const Quads& quads)
	{
		unsigned int vIdx = quadIdx * 4u;
		if (vIdx + quads.get().size() > m_Vertices.size()) throw std::exception("Index out of bounds!");

		const auto& v = quads.get();
		for (unsigned int i = vIdx, j = 0; j < quads.get().size(); i++, j++)
		{
			m_Vertices[i] = quads[j];
		}
		m_NeedsUpdate = true;
	}

	Quad Quads::getQuadAt(unsigned int quadIdx) const
	{
		unsigned int vIdx = quadIdx * 4u;
		if (vIdx + 4u > m_Vertices.size()) throw std::exception("Quad not found!");

		return { m_Vertices[vIdx], m_Vertices[vIdx + 1], m_Vertices[vIdx + 2], m_Vertices[vIdx + 3] };
	}

	/* Shape - Polygon */
	Polygon::Polygon(const std::vector<glm::vec2>& vertices)
		: Shape(vertices, Primitive::POLYGON) {}
	Polygon::Polygon(const Triangle& tri)
		: Shape(tri.get(), Primitive::POLYGON) {}
	Polygon::Polygon(const Quad& quad)
		: Shape(quad.get(), Primitive::POLYGON) {}
	Polygon::Polygon(const Polygon& poly)
		: Shape(poly.get(), Primitive::POLYGON) {}

	void Polygon::add(const std::vector<glm::vec2>& vertices)
	{
		m_NeedsUpdate = true;
		ammendVector(vertices, m_Vertices);
	}

	/* Shape - Triangle Fan */
	TriangleFan::TriangleFan(glm::vec2 centerPoint)
		: Shape({ centerPoint }, Primitive::TRIANGLE_FAN) {}
	TriangleFan::TriangleFan(glm::vec2 centerPoint, const std::vector<glm::vec2>& lines)
		: Shape({ centerPoint }, Primitive::TRIANGLE_FAN)
	{
		ammendVector(lines, m_Vertices);
	}
	TriangleFan::TriangleFan(const TriangleFan& triFan)
		: Shape(triFan.get(), Primitive::TRIANGLE_FAN) {}

	void TriangleFan::setCenterPoint(glm::vec2 p)
	{
		m_Vertices[0] = p;
	}

	void TriangleFan::add(const std::vector<glm::vec2>& points)
	{
		m_NeedsUpdate = true;
		ammendVector(points, m_Vertices);
	}

	TriangleFan TriangleFan::makeRegularPoly(unsigned int nSided, float radius)
	{
		double angDiff = glm::radians(360.0 / (double)nSided);

		std::vector<glm::vec2> vertices;

		double L = 0; // L is a symbol of angle.
		for (unsigned int i = 0; i < nSided; i++, L += angDiff)
		{
			vertices.push_back(glm::vec2(glm::cos(L), glm::sin(L)) * radius);
		}
		vertices.push_back(vertices[0]);

		return TriangleFan(glm::vec2(0), vertices);
	}

	/* Shape - Line */
	Line::Line(glm::vec2 p1, glm::vec2 p2, float lineWidth)
		: Shape({ p1, p2 }, Primitive::LINE), m_LineWidth(lineWidth) {}
	Line::Line(const std::array<glm::vec2, 2>& line, float lineWidth)
		: Shape(std::vector<glm::vec2>(line.begin(), line.end()), Primitive::LINE), m_LineWidth(lineWidth) {}
	Line::Line(const Line& line)
		: Shape(line.get(), Primitive::LINE), m_LineWidth(line.getLineWidth()) {}

	void Line::setLineWidth(float lineWidth) const
	{
		m_LineWidth = lineWidth;
	}
	float Line::getLineWidth() const
	{
		return m_LineWidth;
	}

	/* Shape - Lines */
	Lines::Lines(const std::vector<Line>& lines)
		: Shape({}, Primitive::LINES), m_LineWidths()
	{
		add(lines);
	}
	Lines::Lines(const std::vector<Lines>& lines)
		: Shape({}, Primitive::LINES), m_LineWidths()
	{
		add(lines);
	}
	Lines::Lines(const std::vector<LineStrip>& lineStrips)
		: Shape({}, Primitive::LINES), m_LineWidths()
	{
		add(lineStrips);
	}
	Lines::Lines(const std::vector<LineLoop>& lineLoops)
		: Shape({}, Primitive::LINES), m_LineWidths()
	{
		add(lineLoops);
	}
}