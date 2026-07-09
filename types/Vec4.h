//
// Created by tomnir on 08.07.26.
//

#ifndef CG1PROJEKT_VEC4_H
#define CG1PROJEKT_VEC4_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Vec4
{
private:
    const std::size_t m_dimension = 4;
    GLfloat m_vector[4];
public:
    // Operators
    GLfloat& operator() (const int);
    const GLfloat& operator() (const int) const;
    friend GLfloat operator*(const Vec4&, const Vec4&);
	friend Vec4 operator*(const GLfloat lhs, const Vec4& rhs);
    friend Vec4 operator+(const Vec4&, const Vec4&);
    friend Vec4 operator-(const Vec4&, const Vec4&);
    Vec4 operator*(const GLfloat rhs) const;
    Vec4 operator=(const Vec4& rhs);
    friend bool operator==(const Vec4&, const Vec4&);
    // Object mgmt
    Vec4();
    Vec4(const GLfloat, const GLfloat, const GLfloat, const GLfloat);
    Vec4(const Vec4&);
    // Methods
    GLfloat getLength();
};


#endif //CG1PROJEKT_VEC4_H