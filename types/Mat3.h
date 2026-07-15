//
// Created by tomnir on 15.07.26.
//

#ifndef CG1PROJEKT_MAT3_H
#define CG1PROJEKT_MAT3_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Vec3.h"

class Mat3
{
private:
    GLfloat m_matrix[9];
    size_t m_dimension =3;
public:
    // Constructors and object maangement
    Mat3();
    Mat3(const Mat3&);
    ~Mat3();
    // Operators
    friend Mat3 operator* (const Mat3&, const Mat3&);
    Mat3 operator* (const GLfloat rhs) const;
    friend Mat3 operator* (const GLfloat, const Mat3&);
    GLfloat& operator() (const size_t, const size_t);
    const GLfloat& operator() (const size_t, const size_t) const;
    friend bool operator==(const Mat3&, const Mat3&);
    friend bool operator!=(const Mat3&, const Mat3&);
    Mat3& operator=(const Mat3&);

    // Methods
    bool isInvertible() const;
    void invert();
    Mat3 invertCopy() const;
    void transpose();
    Mat3 transposeCopy() const;

};


#endif //CG1PROJEKT_MAT3_H