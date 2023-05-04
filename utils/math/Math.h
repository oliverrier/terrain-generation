#pragma once

#include <type_traits>
#include <array>
#include <cmath>

template<typename T>
struct Point2d
{
    explicit Point2d(const T& _x = 0, const T& _y = 0)
        : x(_x)
        , y(_y)
    {}

    Point2d(const Point2d& pt)
        : x(pt.x)
        , y(pt.y)
    {}

    T x;
    T y;
};

template<typename T>
struct Point3d
{
    Point3d() : x(0), y(0), z(0) {}

    Point3d(const T& _x, const T& _y, const T& _z)
        : x(_x)
        , y(_y)
        , z(_z)
    {}

    Point3d(const Point3d& pt)
        : x(pt.x)
        , y(pt.y)
        , z(pt.z)
    {}

    Point3d<T> operator+(const Point3d<T>& other) const
    {
        return Point3d<T>(x + other.x, y + other.y, z + other.z);
    }


    Point3d<T> operator*(const T& other) const
    {
        return Point3d<T>(x * other, y * other, z * other);
    }

    Point3d<T> operator/(const T& other) const
    {
        if (other != 0)
        {
            return Point3d<T>(x / other, y / other, z / other);
        }
        else
        {
            return Point3d<T>(0, 0, 0);
        }
    }

    Point3d<T>& operator+=(const Point3d<T>& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Point3d<T> operator-(const Point3d<T>& other) const
    {
        return Point3d<T>(x - other.x, y - other.y, z - other.z);
    }


    T x;
    T y;
    T z;
};

template<typename Type>
struct Mat4
{
    using T = Type;

    Mat4()
    {
        for (int i = 0; i < 16; ++i) m_data[i] = 0;
    }

    T& operator()(int line, int col) { return m_data[line + col * 4]; }
    const T& operator()(int line, int col) const { return m_data[line + col * 4]; }

    const Type* getData() const
    {
        return &m_data[0];
    }

    static Mat4<Type> identity()
    {
        Mat4<Type> result;
        result(0, 0) = result(1, 1) = result(2, 2) = result(3, 3) = 1;
        return result;
    }

    static Mat4<Type> rotationX(const Type& angle)
    {
        return rotationAxisAligned<1, 2>(angle);
    }

    static Mat4<Type> rotationY(const Type& angle)
    {
        return rotationAxisAligned<0, 2>(angle);
    }

    static Mat4<Type> rotationZ(const Type& angle)
    {
        return rotationAxisAligned<0, 1>(angle);
    }

    static Mat4<Type> translation(const Type& x, const Type& y, const Type& z)
    {
        Mat4<Type> result = identity();
        result(0, 3) = x;
        result(1, 3) = y;
        result(2, 3) = z;
        return result;
    }

    static Mat4<Type> translation(const Point3d<Type>& p)
    {
        return translation(p.x, p.y, p.z);
    }

    static Mat4<Type> projection(const Type& aspect, const Type& fov, const Type& farPlane, const Type& nearPlane)
    {
        Mat4<Type> result;
        result(0, 0) = 1.f / (aspect * std::tan(fov / 2.f));
        result(1, 1) = 1.f / (std::tan(fov / 2.f));
        result(2, 2) = -(farPlane + nearPlane) / (farPlane - nearPlane);
        result(2, 3) = -(2.f * farPlane * nearPlane) / (farPlane - nearPlane);
        result(3, 2) = -1.f;
        return result;
    }

private:
    template<int a1, int a2>
    static Mat4<Type> rotationAxisAligned(const Type& angle)
    {
        Mat4<Type> result = identity();
        result(a1, a1) = std::cos(angle);
        result(a1, a2) = std::sin(angle);
        result(a2, a1) = -std::sin(angle);
        result(a2, a2) = std::cos(angle);
        return result;
    };

    std::array<Type, 16> m_data;
};

template<typename Type>
Mat4<Type> operator*(const Mat4<Type>& op1, const Mat4<Type>& op2)
{
    Mat4<Type> result;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
                result(i, j) += op1(i, k) * op2(k, j);
        }
    }
    return result;
}

template<typename Type>
struct Color
{
    Color(const Type& r_, const Type& g_, const Type& b_, const Type& a_) : r(r_), g(g_), b(b_), a(a_) {}

    Type r = 0;
    Type g = 0;
    Type b = 0;
    Type a = 0;
};
