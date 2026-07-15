//
// Created by tomnir on 09.07.26.
//

#include "Mat4.h"
#include <cmath>
#include <cassert>
#include <iostream>
using namespace std;

// ------------- Constructors -------------- //

Mat4::Mat4()
    : m_matrix {1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f}
{

}

Mat4::Mat4(const Mat4& other)
    : m_matrix {}
{
    *this = other;
}

Mat4::~Mat4()
{

}

// ------------- Operators -------------- //

GLfloat& Mat4::operator() (const size_t col, const size_t row)
{
    assert(col <= 3 && row <= 3);
    return m_matrix[mIndex(col, row)];
}

const GLfloat& Mat4::operator() (const size_t col, const size_t row) const
{
    assert(col <= 3 && row <= 3);
    return m_matrix[mIndex(col, row)];
}

Mat4 operator*(const Mat4& lhs, const Mat4& rhs)
{
    Mat4 result {};
    for (size_t col = 0; col < lhs.m_dimension; ++col)
    {
        for (size_t row = 0; row < lhs.m_dimension; ++row)
        {
            result(col, row)  = lhs(0, row)*rhs(col, 0);
            result(col, row) += lhs(1, row)*rhs(col,1);
            result(col, row) += lhs(2, row)*rhs(col,2);
            result(col, row) += lhs(3, row)*rhs(col,3);
        }
    }
    return result;
}

Mat4 Mat4::operator* (const GLfloat rhs)  const
{
    Mat4 result {};
    for (size_t col = 0; col < m_dimension; ++col)
    {
        for (size_t row = 0; row < m_dimension; ++row)
        {
            result(col, row) = m_matrix[mIndex(col, row)] * rhs;
        }
    }
    return result;
}

Mat4 operator*(const GLfloat lhs, const Mat4& rhs)
{
    Mat4 result {};
    for (size_t col = 0; col < rhs.m_dimension; ++col)
    {
        for (size_t row = 0; row < rhs.m_dimension; ++row)
        {
            result(col, row) = rhs(col, row)*lhs;
        }
    }
    return result;
}

bool operator==(const Mat4& lhs, const Mat4& rhs)
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

bool operator!=(const Mat4& lhs, const Mat4& rhs)
{
    return !(lhs==rhs);
}

Mat4& Mat4::operator=(const Mat4& rhs)
{
    if (this == &rhs) return *this;
    for (size_t col = 0; col < m_dimension; ++col)
    {
        for (size_t row = 0; row < m_dimension; ++row)
        {
            m_matrix[Mat4::mIndex(col, row)] = rhs.m_matrix[mIndex(col, row)];
        }
    }
    return *this;
}

ostream& operator<<(ostream& os, const Mat4& matrix)
{
    for (size_t col = 0; col < matrix.m_dimension; ++col)
    {
        for (size_t row = 0; row < matrix.m_dimension; ++row)
        {
            os << matrix.m_matrix[Mat4::mIndex(col, row)] << " ";
        }
    }
    return os;
}

// ------------- Methods -------------- //

// ------------- Translations -------------- //

void Mat4::translate(const Vec3& vector)
{
    Mat4 translationMatrix {};
    Mat4 oldMatrix {*this};
    translationMatrix(3,0) = vector(0);
    translationMatrix(3,1) = vector(1);
    translationMatrix(3,2) = vector(2);
    Mat4 temp { translationMatrix*oldMatrix };
    for (size_t i = 0; i<16; ++i)
    {
        m_matrix[i] = temp.m_matrix[i];
    }
}

Mat4 Mat4::translateCopy(const Vec3& vector) const
{
    Mat4 temp {*this};
    temp.translate(vector);
    return temp;
}

// ------------- Scaling -------------- //

void Mat4::scale(const Vec3& vector)
{
    assert(!vector.isZeroVector());
    Mat4 scaleMatrix {};
    Mat4 oldMatrix {*this};
    for (size_t i = 0; i < 3; ++i)
    {
        scaleMatrix(i,i) = vector(i);
    }
    Mat4 temp {scaleMatrix*oldMatrix};
    for (size_t i = 0; i<16; ++i)
    {
        m_matrix[i] = temp.m_matrix[i];
    }
}

Mat4 Mat4::scaleCopy(const Vec3& vector) const
{
    Mat4 temp {*this};
    temp.scale(vector);
    return temp;
}

// ------------- Rotations -------------- //

void Mat4::rotateX(const GLfloat& angle)
{
    Mat4 rotationMatrix {};
    rotationMatrix(1,1) = cos(angle);
    rotationMatrix(2,1) = -sin(angle);
    rotationMatrix(1,2) = sin(angle);
    rotationMatrix(2,2) = cos(angle);
    Mat4 oldMatrix{ *this };
    Mat4 temp { rotationMatrix*oldMatrix };
    for (size_t i = 0; i<16; ++i)
    {
        m_matrix[i] = temp.m_matrix[i];
    }
}

void Mat4::rotateY(const GLfloat& angle)
{
    Mat4 rotationMatrix {};
    rotationMatrix(0,0) = cos(angle);
    rotationMatrix(0,2) = -sin(angle);
    rotationMatrix(2,0) = sin(angle);
    rotationMatrix(2,2) = cos(angle);
    Mat4 oldMatrix{ *this };
    Mat4 temp { rotationMatrix*oldMatrix };
    for (size_t i = 0; i<16; ++i)
    {
        m_matrix[i] = temp.m_matrix[i];
    }
}

void Mat4::rotateZ(const GLfloat& angle)
{
    Mat4 rotationMatrix {};
    rotationMatrix(0,0) = cos(angle);
    rotationMatrix(1,0) = -sin(angle);
    rotationMatrix(0,1) = sin(angle);
    rotationMatrix(1,1) = cos(angle);
    Mat4 oldMatrix{ *this };
    Mat4 temp { rotationMatrix*oldMatrix };
    for (size_t i = 0; i<16; ++i)
    {
        m_matrix[i] = temp.m_matrix[i];
    }
}

Mat4 Mat4::rotateCopyX(const GLfloat& angle) const
{
    Mat4 result {*this};
    result.rotateX(angle);
    return result;
}

Mat4 Mat4::rotateCopyY(const GLfloat& angle) const
{
    Mat4 result {*this};
    result.rotateY(angle);
    return result;
}

Mat4 Mat4::rotateCopyZ(const GLfloat& angle) const
{
    Mat4 result {*this};
    result.rotateZ(angle);
    return result;
}

// ------------- Camera -------------- //

void Mat4::lookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
{
    assert (eye != center);
    Mat4 translationMatrix {};
    translationMatrix.translate(-eye);
    Vec3 n {eye-center};
    assert (!up.isParallelTo(n));
    Vec3 u {up.crossProduct(n)};
    Vec3 v {n.crossProduct(u)};
    n.normalize();
    u.normalize();
    v.normalize();
    Mat4 rotationMatrix {};
    for (size_t i = 0; i<3; ++i)
    {
        rotationMatrix(i, 0) = u(i);
        rotationMatrix(i, 1) = v(i);
        rotationMatrix(i, 2) = n(i);
    }
    Mat4 temp { rotationMatrix*translationMatrix };
    for (size_t i = 0; i<16; ++i)
    {
        m_matrix[i] = temp.m_matrix[i];
    }
}

Mat4 Mat4::lookAtCopy(const Vec3& eye, const Vec3& center, const Vec3& up) const
{
    Mat4 result {*this};
    result.lookAt(eye, center, up);
    return result;
}

void Mat4::perspective(const GLfloat fovy, const GLfloat aspect, const GLfloat near, const GLfloat far)
{
    assert(fovy >= 0 && fovy <= M_PI);
    assert(far > near);
    const GLfloat& alpha {fovy};
    GLfloat beta = aspect*alpha;
    const GLfloat& n {near};
    const GLfloat& f {far};
    GLfloat l = -near*tan(beta/2);
    GLfloat r = near*tan(beta/2);
    GLfloat b = -near*tan(alpha/2);
    GLfloat t = near*tan(alpha/2);

    Mat4 frustumMatrix {};
    frustumMatrix(0,0) = 2 / (r-l);
    frustumMatrix(1,1) = 2 / (t-t);
    frustumMatrix(2,0) = ((r+l) / (r-l)) / n;
    frustumMatrix(2,1) = ((t+b) / (t-b)) / n;
    frustumMatrix(2,2) = ((f+n) / (f-n)) / -n;
    frustumMatrix(2,3) = -(1/n);
    frustumMatrix(3,2) = -((2*f) / (f-n));
    for (size_t i=0; i<16; ++i)
    {
        m_matrix[i]=frustumMatrix.m_matrix[i];
    }
}

Mat4 Mat4::perspectiveCopy(const GLfloat fovy, const GLfloat aspect, const GLfloat near, const GLfloat far) const
{
    Mat4 result {*this};
    result.perspective(fovy, aspect, near, far);
    return result;
}

// ------------- Utility -------------- //

void Mat4::directPrint() const
{
	for (size_t i = 0; i < 16; ++i)
	{
		if (i%4==0) cout << endl;
		cout << m_matrix[i] << " ";
	}
	cout << endl;
}

size_t Mat4::mIndex(const size_t col, const size_t row)
{
    assert(col <= 3 && row <= 3);
    const size_t index = row*4+col;
    return index;
}