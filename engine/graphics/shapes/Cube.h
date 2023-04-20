#pragma once

#include "GL/glew.h"
#include "SFML/OpenGL.hpp"

#include <array>

#include "engine/grapics/shaders/Shader.h"
#include "MathHelper.h"


template<typename Type>
struct vertex_struct_cube
{
    vertex_struct_cube(const Point3d<Type>& p_, const Point3d<Type>& n_, const Color<Type>& c_) : p(p_), c(c_), n(n_) {}
    Point3d<Type> p;
    Point3d<Type> n;
    Color<Type> c;
};


template<typename Type>
class Cube
{
public:

    Cube()
        : m_vao(0)
        , m_vbo(0)
    {
        load();
    }

    ~Cube()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
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

        using vt = vertex_struct_cube<Type>;
        std::array<vertex_struct_cube<Type>, 36> points = {
            vt{P000, nxn, vr}, vt{P010, nxn, vr}, vt{P011, nxn, vr}, vt{P000, nxn, vr}, vt{P011, nxn, vr}, vt{P001, nxn, vr}
          , vt{P100, nxp, ar}, vt{P110, nxp, ar}, vt{P111, nxp, ar}, vt{P100, nxp, ar}, vt{P111, nxp, ar}, vt{P101, nxp, ar}
          , vt{P000, nyn, vg}, vt{P100, nyn, vg}, vt{P101, nyn, vg}, vt{P000, nyn, vg}, vt{P101, nyn, vg}, vt{P001, nyn, vg}
          , vt{P010, nyp, ag}, vt{P110, nyp, ag}, vt{P111, nyp, ag}, vt{P010, nyp, ag}, vt{P111, nyp, ag}, vt{P011, nyp, ag}
          , vt{P000, nzn, vb}, vt{P100, nzn, vb}, vt{P110, nzn, vb}, vt{P000, nzn, vb}, vt{P110, nzn, vb}, vt{P010, nzn, vb}
          , vt{P001, nzp, ab}, vt{P101, nzp, ab}, vt{P111, nzp, ab}, vt{P001, nzp, ab}, vt{P111, nzp, ab}, vt{P011, nzp, ab}
        };

        m_nbVertices = static_cast<GLsizei>(points.size());

        // Allocate storage size units of OpenGL
        // Copy data from client to server
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points.data(), GL_STATIC_DRAW);

        ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, "../shaders/cube/cube.vert"},
            {GL_FRAGMENT_SHADER, "../shaders/cube/cube.frag"},
            {GL_NONE, nullptr}
        };

        m_program = Shader::loadShaders(shaders);
        glUseProgram(m_program);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_struct_cube<Type>), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_struct_cube<Type>), (char*)(0) + sizeof(vertex_struct_cube<Type>::p));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_struct_cube<Type>), (char*)(0) + sizeof(vertex_struct_cube<Type>::p) + sizeof(vertex_struct_cube<Type>::n));
        glEnableVertexAttribArray(2);
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

        glDrawArrays(GL_TRIANGLES, 0, m_nbVertices);
    }

    void update()
    {
        m_angleX += 0.0125f;
        m_angleY += 0.025f;
    }

private:
    Type m_angleX = 0;
    Type m_angleY = 0;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_program;
    GLsizei m_nbVertices;
};

