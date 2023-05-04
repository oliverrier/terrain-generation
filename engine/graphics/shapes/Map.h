#pragma once

#include "GL/glew.h"
#include "SFML/OpenGL.hpp"

#include <array>
#include <iostream>

#include "utils/math/Math.h"
#include "engine/graphics/shaders/Shader.h"


template<typename Type>
struct vertex_struct_map
{
	vertex_struct_map(const Point3d<Type>& p_, const Point3d<Type>& n_, const Color<Type>& c_) : p(p_), c(c_), n(n_) {}
	Point3d<Type> p;
	Point3d<Type> n;

	Color<Type> c;
	int nb_face = 0;

};


template<typename Type>
class Map
{
public:

	Map()
		: m_vao(0)
		, m_vbo(0)
	{
		load();
	}

	~Map()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
	}


	void generateTerrainVerticesIndices(float size, float step) {

		int numVertices = static_cast<int>(size / step) + 1;
		int height = -1;

		for (int i = 0; i < numVertices; i++) {
			for (int j = 0; j < numVertices; j++) {
				Type x = i * step;
				Type z = j * step;
				Type y = height;
				m_vertexVect.push_back(Point3d<Type>{x, y, z});

			}
		}

		// Générer les indices pour les triangles
		for (int i = 0; i < numVertices - 1; i++) {
			for (int j = 0; j < numVertices - 1; j++) {
				// Indices des sommets des deux triangles formant un carré
				unsigned int index1 = i * numVertices + j;
				unsigned int index2 = index1 + 1;
				unsigned int index3 = (i + 1) * numVertices + j;
				unsigned int index4 = index3 + 1;

				// Premier triangle
				m_indices.push_back(index1);
				m_indices.push_back(index2);
				m_indices.push_back(index3);

				// Deuxième triangle
				m_indices.push_back(index2);
				m_indices.push_back(index4);
				m_indices.push_back(index3);
			}
		}
	}

	void load()
	{

		// We want only one buffer with the id generated and stored in m_vao
		glGenVertexArrays(1, &m_vao);

		// create a new active VAO
		glBindVertexArray(m_vao);

		// we want only one buffer with the id generated and stored in m_vbo
		glGenBuffers(1, &m_vbo);

		// 1. create a new active VBO if doesn’t exist
		// 2. if the VBO is active it will make it active
		// 3. if binded to 0, OpenGL stops
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		Point3d<Type> P000 = { -1, -1, -1 }; Point3d<Type> P001 = { -1, -1, +1 }; Point3d<Type> P010 = { -1, +1, -1 }; Point3d<Type> P011 = { -1, +1, +1 };
		Point3d<Type> P100 = { +1, -1, -1 }; Point3d<Type> P101 = { +1, -1, +1 }; Point3d<Type> P110 = { +1, +1, -1 }; Point3d<Type> P111 = { +1, +1, +1 };

		Color<Type> vr = { 1, 0, 0, 1 }; Color<Type> vg = { 0, 1, 0, 1 }; Color<Type> vb = { 0, 0, 1, 1 };
		Color<Type> ar = { 0, 1, 1, 1 }; Color<Type> ag = { 1, 0, 1, 1 }; Color<Type> ab = { 1, 1, 0, 1 };

		Point3d<Type> nxn = { -1, 0, 0 }; Point3d<Type> nxp = { +1, 0, 0 };
		Point3d<Type> nyn = { 0, -1, 0 }; Point3d<Type> nyp = { 0, +1, 0 };
		Point3d<Type> nzn = { 0, 0, -1 }; Point3d<Type> nzp = { 0, 0, +1 };

		using VertexStructMapType = vertex_struct_map<Type>;
		std::vector<vertex_struct_map<Type>> points;

		generateTerrainVerticesIndices(20, 0.01);

		for (Point3d<float>& p : m_vertexVect)
		{
			points.push_back(VertexStructMapType{ p, nyp, vg });
		}

		for (int i = 2; i < m_indices.size(); i += 3) {
			int index = m_indices.at(i);
			VertexStructMapType& p1 = points.at(m_indices.at(i));
			VertexStructMapType& p2 = points.at(m_indices.at(i - 1));
			VertexStructMapType& p3 = points.at(m_indices.at(i - 2));

			//calculate vector
			Point3d<Type> vec12 = { p2.p.x - p1.p.x, p2.p.y - p1.p.y, p2.p.z - p1.p.z };
			Point3d<Type> vec13 = { p3.p.x - p1.p.x, p3.p.y - p1.p.y, p3.p.z - p1.p.z };

			//Calculate normal
			Point3d<Type> normal =
			{
				(vec12.z * vec13.y) - (vec12.y * vec13.z),
				(vec12.x * vec13.z) - (vec12.z * vec13.x),
				(vec12.y * vec13.x) - (vec12.x * vec13.y)
			};

			p1.n = ((p1.n * p1.nb_face) + normal) / (p1.nb_face + 1);
			p1.n = p1.n / std::sqrt((p1.n.x * p1.n.x) + (p1.n.y * p1.n.y) + (p1.n.z * p1.n.z));

			p1.nb_face += 1;

			p2.n = ((p2.n * p2.nb_face) + normal) / (p2.nb_face + 1);
			p2.n = p2.n / std::sqrt((p2.n.x * p2.n.x) + (p2.n.y * p2.n.y) + (p2.n.z * p2.n.z));

			p2.nb_face += 1;

			p3.n = ((p3.n * p3.nb_face) + normal) / (p3.nb_face + 1);
			p3.n = p3.n / std::sqrt((p3.n.x * p3.n.x) + (p3.n.y * p3.n.y) + (p3.n.z * p3.n.z));

			p3.nb_face += 1;

		}

		m_nbVertices = static_cast<GLsizei>(points.size());

		// Allocate storage size units of OpenGL
		// Copy data from client to server
		glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(VertexStructMapType), points.data(), GL_STATIC_DRAW);

		ShaderInfo shaders[] = {
			{GL_VERTEX_SHADER, "assets/shaders/map.vert"},
			{GL_FRAGMENT_SHADER, "assets/shaders/map.frag"},
			{GL_NONE, nullptr}
		};

		m_program = Shader::loadShaders(shaders);
		glUseProgram(m_program);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructMapType), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexStructMapType), (char*)(0) + sizeof(VertexStructMapType::p));
		glEnableVertexAttribArray(1);

		// En cas de bug penser a changer le décalage par rapport au autres données dans la struct
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexStructMapType), (char*)(0) + sizeof(VertexStructMapType::p) + sizeof(VertexStructMapType::n));
		glEnableVertexAttribArray(2);



		glGenBuffers(1, &m_elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);
	}

	void render(const Mat4<Type>& View, const Mat4<Type>& Projection)
	{
		glBindVertexArray(m_vao);

		Mat4<Type> Model = Mat4<Type>::translation(0, 0, -5) * Mat4<Type>::rotationY(m_angleY) * Mat4<Type>::rotationX(m_angleX);

		glUniformMatrix4fv(glGetUniformLocation(m_program, "ModelMatrix"), 1, GL_FALSE, Model.getData());
		glUniformMatrix4fv(glGetUniformLocation(m_program, "ViewMatrix"), 1, GL_FALSE, View.getData());
		glUniformMatrix4fv(glGetUniformLocation(m_program, "ProjectionMatrix"), 1, GL_FALSE, Projection.getData());

		glUniform1f(glGetUniformLocation(m_program, "material.ambient"), 0.3f);
		glUniform1f(glGetUniformLocation(m_program, "material.diffuse"), 0.7f);
		glUniform1f(glGetUniformLocation(m_program, "material.specular"), 1.f);
		glUniform1f(glGetUniformLocation(m_program, "material.specularSmoothness"), 2.0f);

		glUniform3f(glGetUniformLocation(m_program, "light.direction"), 0.f, -1.f, 0.f);
		glUniform3f(glGetUniformLocation(m_program, "light.color"), 1.f, 1.f, 1.f);

		glUniform3f(glGetUniformLocation(m_program, "camera.worldPosition"), 0.f, 0.f, 0.f);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementbuffer);

		glDrawElements(
			GL_TRIANGLES,      // mode
			m_indices.size(),    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
		);

	}

	void update()
	{
		/*m_angleX += 0.0125f;
		m_angleY += 0.025f;*/
	}

private:
	Type m_angleX = 0;
	Type m_angleY = 0;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_program;
	GLsizei m_nbVertices;

	GLuint m_elementbuffer;
	std::vector<Point3d<Type>> m_vertexVect;
	std::vector<unsigned int> m_indices;
};

