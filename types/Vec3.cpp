//
// Created by tomnir on 08.07.26.
//

#include "Vec3.h"
#include <cmath>
#include <GL/glew>
#include <gl/glfw>
using namespace std;

// Constructors

Vec3::Vec3()
    : m_dimension {3}
    , m_vector {0.0f, 0.0f, 0.0f}
{
    for (GLfloat& component : m_vector)
    {
        component = 0.0f;
    }
}

Vec3::Vec3(const GLfloat firstComponent, const GLfloat secondComponent, const GLfloat thirdComponent)
    : m_dimension {3}
    , m_vector {firstComponent, secondComponent, thirdComponent}
{
}

Vec3::Vec3(const Vec& other)
    : m_dimension {3}
    , m_vector {}
{
    for (int i = 0; i < m_dimension; ++i)
    {
        m_vector[i] = other(i);
    }
}

// Operators

GLfloat& operator() (const size_t component)
{
    return m_vector[component];
}

Vec3 operator*(const Vec3& rhs, const Vec3& lhs)
{
    Vec3 result;
    result(0) = lhs(1)*rhs(2) - lhs(2)*rhs(1);
    result(1) = lhs(2)*rhs(0) - lhs(0)*rhs(2);
    result(2) = lhs(0)*rhs(1) - lhs(1)*rhs(0);
    return result;
}

Vec3 Vec3::operator*(const double rhs)
{
    Vec3 result;
    result(0) = m_vector[1]*rhs(2) - m_vector[2]*rhs(1);
    result(1) = m_vector[2]*rhs(0) - m_vector[0]*rhs(2);
    result(2) = m_vector[0]*rhs(1) - m_vector[1]*rhs(0);
    return result;
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
{
    return vec3( lhs(0)+rhs(0), lhs(1)+rhs(1), rhs(2)+lhs(2) );
}

Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3( lhs(0)-rhs(0), lhs(1)-rhs(1), rhs(2)-lhs(2) );
}

Vec3& Vec3::operator=(const Vec3& rhs)
{
    return Vec3(rhs);
}

bool operator==(const Vec3& lhs, const Vec3& rhs)
{
    return (lhs(0) == rhs(0) && lhs(1) == rhs(1) && lhs(2) == rhs(2));
}

// Methods

GLfloat Vec3::getLength()
{
    return sqrt( m_vector[0]*m_vector[0] + m_vector[1]*m_vector[1] + m_vector[2]*m_vector[2] );
}

GLfloat Vec3::scalarProduct(const Vec3& rhs)
{
    return ( lhs(0)*rhs(0) + lhs(1)*rhs(1) + lhs(2)*rhs(2) );
}


