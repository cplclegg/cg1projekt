//
// Created by tomnir on 08.07.26.
//

#include "Vec3.h"
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

// Operators

GLfloat& Vec3::operator() (const int component)
{
    return m_vector[component];
}

const GLfloat& Vec3::operator() (const int component) const
{
    return m_vector[component];
}

Vec3 operator*(const Vec3& rhs, const Vec3& lhs)
{
    Vec3 result {};
    result(0) = lhs.m_vector[1]*rhs.m_vector[2] - lhs.m_vector[2]*rhs.m_vector[1];
    result(1) = lhs.m_vector[2]*rhs.m_vector[0] - lhs.m_vector[0]*rhs.m_vector[2];
    result(2) = lhs.m_vector[0]*rhs.m_vector[1] - lhs.m_vector[1]*rhs.m_vector[0];
    return result;
}

Vec3 operator*(const GLfloat lhs, const Vec3& rhs)
{
	return Vec3 {
		rhs(0)*lhs,
		rhs(1)*lhs,
		rhs(2)*lhs
	};
}
Vec3 Vec3::operator*(const GLfloat rhs) const
{
    return Vec3 {
    m_vector[0] * (GLfloat) rhs,
    m_vector[1] * (GLfloat) rhs,
    m_vector[2] * (GLfloat) rhs
    };
}

Vec3 operator+(const Vec3& lhs, const Vec3& rhs)
{
	return Vec3 {
	lhs(0)+rhs(0),
	lhs(1)+rhs(1),
	lhs(2)+rhs(2)
	};
}

Vec3 operator-(const Vec3& lhs, const Vec3& rhs)
{
    return Vec3 {
	lhs(0)-rhs(0),
	lhs(1)-rhs(1),
	lhs(2)-rhs(2)
	};

}

Vec3 Vec3::operator=(const Vec3& rhs)
{
	return Vec3 {rhs};
}

bool operator==(const Vec3& lhs, const Vec3& rhs)
{
    return (lhs(0) == rhs(0) && lhs(1) == rhs(1) && lhs(2) == rhs(2));
}

// Constructors

Vec3::Vec3()
    : m_vector {0.0f, 0.0f, 0.0f}
{
}

Vec3::Vec3(const GLfloat firstComponent, const GLfloat secondComponent, const GLfloat thirdComponent)
    : m_vector {firstComponent, secondComponent, thirdComponent}
{
}

Vec3::Vec3(const Vec3& other)
    : m_vector {0.0f, 0.0f, 0.0f}
{
    for (int i = 0; i < m_dimension; ++i)
    {
        m_vector[i] = other(i);
    }
}

// Methods

GLfloat Vec3::getLength()
{
    return sqrt( m_vector[0]*m_vector[0] + m_vector[1]*m_vector[1] + m_vector[2]*m_vector[2] );
}

GLfloat Vec3::scalarProduct(const Vec3& rhs)
{
    return ( m_vector[0]*rhs(0) + m_vector[1]*rhs(1) + m_vector[2]*rhs(2) );
}


