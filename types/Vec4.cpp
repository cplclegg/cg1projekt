//
// Created by tomnir on 08.07.26.
//
#include "Vec4.h"
#include <cmath>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

// Operators

GLfloat& Vec4::operator() (const size_t component)
{
    assert(component <= 3);
    return m_vector[component];
}

const GLfloat& Vec4::operator() (const size_t component) const
{
    assert(component <= 3);
    return m_vector[component];
}

GLfloat operator*(const Vec4& rhs, const Vec4& lhs)
{
    GLfloat result = 0.0f;
    for (int i = 0; i<lhs.m_dimension; ++i)
    {
        result += rhs.m_vector[i]*lhs.m_vector[i];
    }
    return result;
}

Vec4 operator*(const GLfloat lhs, const Vec4& rhs)
{
	return Vec4 {
		rhs(0)*lhs,
		rhs(1)*lhs,
		rhs(2)*lhs,
		rhs(3)*lhs
	};
}

Vec4 Vec4::operator*(const GLfloat rhs) const
{
    return Vec4 {
        m_vector[0] * rhs,
        m_vector[1] * rhs,
        m_vector[2] * rhs,
        m_vector[3] * rhs
    };
}

Vec4 operator+(const Vec4& lhs, const Vec4& rhs)
{
    return Vec4 {
        lhs(0)+rhs(0),
        lhs(1)+rhs(1),
        lhs(2)+rhs(2),
        lhs(3)+rhs(3)
    };
}

Vec4 operator-(const Vec4& lhs, const Vec4& rhs)
{
    return Vec4 {
        lhs(0)-rhs(0),
        lhs(1)-rhs(1),
        lhs(2)-rhs(2),
        lhs(3)-rhs(3)
    };
}

Vec4& Vec4::operator=(const Vec4& rhs)
{
    if (this == &rhs) return *this;
    for (size_t i = 0; i < m_dimension; ++i)
    {
        m_vector[i] = rhs.m_vector[i];
    }
    return *this;
}

Vec4 Vec4::operator-() const
{
    return Vec4 { -m_vector[0], -m_vector[1], -m_vector[2], -m_vector[3]};
}

bool operator==(const Vec4& lhs, const Vec4& rhs)
{
    if (&lhs == &rhs) return true;
    bool equal = true;
    for (int i = 0; i < lhs.m_dimension; ++i)
    {
        equal = equal && (lhs(i) == rhs(i));
    }
    return equal;
}

bool operator!=(const Vec4& lhs, const Vec4& rhs)
{
    return !(lhs==rhs);
}

// Constructors

Vec4::Vec4()
    : m_vector {0.0f, 0.0f, 0.0f, 0.0f}
{
}

Vec4::Vec4(const GLfloat firstComponent, const GLfloat secondComponent, const GLfloat thirdComponent, const GLfloat fourthComponent)
    : m_vector {firstComponent, secondComponent, thirdComponent, fourthComponent}
{
}

Vec4::Vec4(const Vec4& other)
    : m_vector {}
{
    *this = other;
}

// Methods

GLfloat Vec4::getLength() const
{
    GLfloat squareSum = 0;
    for (int i = 0; i < m_dimension; ++i)
    {
        squareSum += m_vector[i]*m_vector[i];
    }
    return sqrt(squareSum);
}

bool Vec4::isParallelTo(const Vec4& other) const
{
    const GLfloat absDotProduct = abs((*this)*other);
    const GLfloat lengthProduct = getLength() *  other.getLength();
    return absDotProduct == lengthProduct;
}

bool Vec4::isZeroVector() const
{
    return (m_vector[0] != 0 && m_vector[1] != 0 && m_vector[2] != 0 && m_vector[3] != 0);
}

void Vec4::normalize()
{
    assert(!isZeroVector());
    const GLfloat length = getLength();
    m_vector[0] = m_vector[0]/length;
    m_vector[1] = m_vector[1]/length;
    m_vector[2] = m_vector[2]/length;
    m_vector[3] = m_vector[3]/length;
}

