#pragma once

template<typename Type>
struct vertex_struct
{
    Point3d<Type> p;
    Point2d<Type> t;
};

template<typename Type>
class Triangle
{
public:

    Triangle(const vertex_struct<Type>& p0, const vertex_struct<Type>& p1, const vertex_struct<Type>& p2)
        : m_vao(0)
        , m_vbo(0)
        , m_points{ {p0, p1, p2} }
    {
        load();
    }

    ~Triangle()
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

        // Allocate storage size units of OpenGL
        // Copy data from client to server
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_points), m_points.data(), GL_STATIC_DRAW);

        ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, "../shaders/triangle/triangle.vert"},
            {GL_FRAGMENT_SHADER, "../shaders/triangle/triangle.frag"},
            {GL_NONE, nullptr}
        };

        m_program = Shader::loadShaders(shaders);
        glUseProgram(m_program);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_struct<Type>), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_struct<Type>), (char*)(0) + sizeof(vertex_struct<Type>::p));
        glEnableVertexAttribArray(1);
    }

    void render(const Mat4<Type>& VP)
    {
        glBindVertexArray(m_vao);
        Color<Type> c{ 1.0, 0.0, 0.0, 1.0 };
        GLuint mySuperColorLocation = glGetUniformLocation(m_program, "mySuperColor");
        glUniform4f(mySuperColorLocation, c.r, c.g, c.b, c.a);

        Mat4<Type> Model = Mat4<Type>::translation(0, 0, -5) * Mat4<Type>::rotationY(m_angle);

        Mat4<Type> MVP = VP * Model;

        GLuint MVPLocation = glGetUniformLocation(m_program, "MVP");
        glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, MVP.getData());

        m_texture.bind();
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_points.size()));
    }

    void update()
    {
        m_angle += 0.025f;
    }

private:
    Type m_angle = 0;
    Texture m_texture;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_program;
    std::array<vertex_struct<Type>, 3> m_points;
};