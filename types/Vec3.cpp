//
// Created by tomnir on 08.07.26.
//

#include "Vec3.h"
#include <cmath>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

// Operators

GLfloat& Vec3::operator() (const size_t component)
{
    assert(component <= 2);
    return m_vector[component];
}

const GLfloat& Vec3::operator() (const size_t component) const
{
    assert(component <= 2);
    return m_vector[component];
}

GLfloat operator*(const Vec3& rhs, const Vec3& lhs)
{
    return ( lhs.m_vector[0]*rhs.m_vector[0] + lhs.m_vector[1]*rhs.m_vector[1] + lhs.m_vector[2]*rhs.m_vector[2] );
}

Vec3 operator*(const GLfloat lhs, const Vec3& rhs)
{
	return Vec3 {
		rhs.m_vector[0]*lhs,
		rhs.m_vector[1]*lhs,
		rhs.m_vector[2]*lhs
	};
}
Vec3 Vec3::operator*(const GLfloat rhs) const
{
    return Vec3 {
    m_vector[0] * rhs,
    m_vector[1] * rhs,
    m_vector[2] * rhs
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

Vec3& Vec3::operator=(const Vec3& rhs)
{
    if (this == &rhs) return *this;
    for (size_t i = 0; i < m_dimension; ++i)
    {
        m_vector[i] = rhs.m_vector[i];
    }
    return *this;
}

bool operator==(const Vec3& lhs, const Vec3& rhs)
{
    if (&lhs == &rhs) return true;
    return (lhs(0) == rhs(0) && lhs(1) == rhs(1) && lhs(2) == rhs(2));
}

bool operator!=(const Vec3& lhs, const Vec3& rhs)
{
    return !(lhs==rhs);
}

Vec3 Vec3::operator-() const
{
    return Vec3 { -m_vector[0], -m_vector[1], -m_vector[2]};
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
    : m_vector {}
{
    *this = other;
}

// Methods

GLfloat Vec3::getLength() const
{
    return sqrt( m_vector[0]*m_vector[0] + m_vector[1]*m_vector[1] + m_vector[2]*m_vector[2] );
}

bool Vec3::isParallelTo(const Vec3& other) const
{
    const GLfloat absDotProduct = abs((*this)*other);
    const GLfloat lengthProduct = getLength() *  other.getLength();
    return absDotProduct == lengthProduct;
}

bool Vec3::isZeroVector() const
{
    return (m_vector[0] != 0 && m_vector[1] != 0 && m_vector[2] != 0);
}

Vec3 Vec3::crossProduct(const Vec3& rhs) const
{
    Vec3 result {};
    result(0) = m_vector[1]*rhs.m_vector[2] - m_vector[2]*rhs.m_vector[1];
    result(1) = m_vector[2]*rhs.m_vector[0] - m_vector[0]*rhs.m_vector[2];
    result(2) = m_vector[0]*rhs.m_vector[1] - m_vector[1]*rhs.m_vector[0];
    return result;
}

void Vec3::normalize()
{
    assert(!isZeroVector());
    const GLfloat length = getLength();
    m_vector[0] = m_vector[0]/length;
    m_vector[1] = m_vector[1]/length;
    m_vector[2] = m_vector[2]/length;
}


