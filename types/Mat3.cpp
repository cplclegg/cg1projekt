//
// Created by tomnir on 15.07.26.
//

#include "Mat3.h"
#include <cassert>
#include <iostream>
using namespace std;
// ------------- Constructors -------------- //

Mat3::Mat3()
    : m_matrix{0.0f, 0.0f, 0.0f,
               0.0f, 0.0f, 0.0f,
               0.0f, 0.0f, 0.0f}
{
}

Mat3::Mat3(const Mat3& other)
    : m_matrix{}
{
    *this = other;
}

Mat3::~Mat3()
{
}

// ------------- Operators -------------- //

GLfloat& Mat3::operator() (const size_t col, const size_t row)
{
    assert(col <= 2 && row <= 2);
    return m_matrix[mIndex(col, row)];
}

const GLfloat& Mat3::operator() (const size_t col, const size_t row) const
{
    assert(col <= 2 && row <= 2);
    return m_matrix[mIndex(col, row)];
}

Mat3 operator*(const Mat3& lhs, const Mat3& rhs)
{
    Mat3 result {};
    for (size_t col = 0; col < lhs.m_dimension; ++col)
    {
        for (size_t row = 0; row < lhs.m_dimension; ++row)
        {
            result(col, row)  = lhs(0, row)*rhs(col, 0);
            result(col, row) += lhs(1, row)*rhs(col,1);
            result(col, row) += lhs(2, row)*rhs(col,2);
        }
    }
    return result;
}

Mat3 Mat3::operator* (const GLfloat rhs)  const
{
    Mat3 result {};
    for (size_t col = 0; col < m_dimension; ++col)
    {
        for (size_t row = 0; row < m_dimension; ++row)
        {
            result(col, row) = m_matrix[mIndex(col, row)] * rhs;
        }
    }
    return result;
}

Mat3 operator*(const GLfloat lhs, const Mat3& rhs)
{
    Mat3 result {};
    for (size_t col = 0; col < rhs.m_dimension; ++col)
    {
        for (size_t row = 0; row < rhs.m_dimension; ++row)
        {
            result(col, row) = rhs(col, row)*lhs;
        }
    }
    return result;
}

bool operator==(const Mat3& lhs, const Mat3& rhs)
{
    if (&rhs == &lhs) return true;
    bool equal = true;
    for (size_t col = 0; col < lhs.m_dimension; ++col)
    {
        for (size_t row = 0; row < lhs.m_dimension; ++row)
        {
            equal = equal && (lhs(col, row) == rhs(col, row));
        }
    }
    return equal;
}

bool operator!=(const Mat3& lhs, const Mat3& rhs)
{
    return !(lhs==rhs);
}

Mat3& Mat3::operator=(const Mat3& rhs)
{
    if (this == &rhs) return *this;
    for (size_t col = 0; col < m_dimension; ++col)
    {
        for (size_t row = 0; row < m_dimension; ++row)
        {
            m_matrix[mIndex(col, row)] = rhs.m_matrix[mIndex(col, row)];
        }
    }
    return *this;
}

// ------------- Methods -------------- //

GLfloat Mat3::determinant() const
{
    // using Sarrus rule
    GLfloat result {0};
    result += m_matrix[mIndex(0,0)]*m_matrix[mIndex(1,1)]*m_matrix[mIndex(2,2)];
    result += m_matrix[mIndex(0,1)]*m_matrix[mIndex(1,2)]*m_matrix[mIndex(2,0)];
    result += m_matrix[mIndex(0,2)]*m_matrix[mIndex(1,0)]*m_matrix[mIndex(2,1)];
    result -= m_matrix[mIndex(0,2)]*m_matrix[mIndex(1,1)]*m_matrix[mIndex(2,0)];
    result -= m_matrix[mIndex(0,0)]*m_matrix[mIndex(1,2)]*m_matrix[mIndex(2,1)];
    result -= m_matrix[mIndex(0,1)]*m_matrix[mIndex(1,0)]*m_matrix[mIndex(2,2)];
    return result;
}

bool Mat3::isInvertible() const
{
    return determinant() != 0;
}

void Mat3::invert()
{
    assert(isInvertible());

    GLfloat a {m_matrix[mIndex(0,0)]};
    GLfloat b {m_matrix[mIndex(1,0)]};
    GLfloat c {m_matrix[mIndex(2,0)]};
    GLfloat d {m_matrix[mIndex(0,1)]};
    GLfloat e {m_matrix[mIndex(1,1)]};
    GLfloat f {m_matrix[mIndex(2,1)]};
    GLfloat g {m_matrix[mIndex(0,2)]};
    GLfloat h {m_matrix[mIndex(1,2)]};
    GLfloat i {m_matrix[mIndex(2,2)]};

    Mat3 adjunct {};

    adjunct(0,0) = e*i-f*h;
    adjunct(0,1) = f*g-d*i;
    adjunct(0,2) = d*h-e*g;

    adjunct(1,0) = c*h-b*i;
    adjunct(1,1) = a*i-c*g;
    adjunct(1,2) = b*g-a*h;

    adjunct(2,0) = b*f-c*e;
    adjunct(2,1) = c*d-a*f;
    adjunct(2,2) = a*e-b*d;

    Mat3 temp {(1/determinant())*adjunct };

    for (size_t j = 0; j < 9; ++j)
    {
        m_matrix[j] = temp.m_matrix[j];
    }
}

Mat3 Mat3::invertCopy() const
{
    Mat3 result {*this};
    result.invert();
    return result;
}

void Mat3::transpose()
{
    Vec3 col1 {m_matrix[mIndex(0,0)], m_matrix[mIndex(0,1)], m_matrix[mIndex(0,2)]};
    Vec3 col2 {m_matrix[mIndex(1,0)], m_matrix[mIndex(1,1)], m_matrix[mIndex(1,2)]};
    Vec3 col3 {m_matrix[mIndex(2,0)], m_matrix[mIndex(2,1)], m_matrix[mIndex(2,2)]};

    for (size_t i = 0; i < 3; ++i)
    {
        m_matrix[mIndex(i, 0)] = col1(i);
        m_matrix[mIndex(i, 1)] = col2(i);
        m_matrix[mIndex(i, 2)] = col3(i);
    }
}

Mat3 Mat3::transposeCopy() const
{
    Mat3 result {*this};
    result.transpose();
    return result;
}

// ------------- Utility -------------- //

void Mat3::directPrint() const
{
    for (size_t i = 0; i < 16; ++i)
    {
        if (i%3==0) cout << endl;
        cout << m_matrix[i] << " ";
    }
    cout << endl;
}

size_t Mat3::mIndex(const size_t col, const size_t row)
{
    assert(col <= 2 && row <= 2);
    const size_t index = row*3+col;
    return index;
}