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

GLfloat& Vec4::operator() (const int component)
{
    return m_vector[component];
}

const GLfloat& Vec4::operator() (const int component) const
{
    return m_vector[component];
}

GLfloat operator*(const Vec4& rhs, const Vec4& lhs)
{
    assert (rhs.m_dimension == 4 && lhs.m_dimension == 4);
    GLfloat result = 0.0f;
    for (int i = 0; i<lhs.m_dimension; ++i)
    {
        result += rhs.m_vector[i]*lhs.m_vector[i];
    }
    return result;
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

Vec4 Vec4::operator=(const Vec4& rhs)
{
    return Vec4 {
        rhs(0),
        rhs(1),
        rhs(2),
        rhs(3)
    };
}

bool operator==(const Vec4& lhs, const Vec4& rhs)
{
    assert (rhs.m_dimension == 4 && lhs.m_dimension == 4);
    bool equal = true;
    for (int i = 0; i < lhs.m_dimension; ++i)
    {
        equal = equal && (lhs(i) == rhs(i));
    }
    return equal;
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
    : m_vector {0.0f, 0.0f, 0.0f, 0.0f}
{
    for (int i = 0; i < m_dimension; ++i)
    {
        m_vector[i] = other(i);
    }
}

// Methods

GLfloat Vec4::getLength()
{
    GLfloat squareSum = 0;
    for (int i = 0; i < m_dimension; ++i)
    {
        squareSum += m_vector[i]*m_vector[i];
    }
    return sqrt(squareSum);
}

