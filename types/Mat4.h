//
// Created by tomnir on 09.07.26.
//

#ifndef CG1PROJEKT_MAT4_H
#define CG1PROJEKT_MAT4_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Vec3.h"
#include "Vec4.h"

class Mat4
{
private:
	GLfloat m_matrix[16];
    size_t m_dimension = 4;
public:
    // Constructors and object maangement
    Mat4();
    Mat4(const Mat4&);

    // Operators
    friend Mat4 operator* (const Mat4&, const Mat4&);
    Mat4 operator* (const GLfloat rhs) const;
    friend Mat4 operator* (const GLfloat, const Mat4&);
    GLfloat& operator() (const size_t, const size_t);
    const GLfloat& operator() (const size_t, const size_t) const;
    friend bool operator==(const Mat4&, const Mat4&);
    friend bool operator!=(const Mat4&, const Mat4&);
    Mat4& operator=(const Mat4&);
    friend std::ostream& operator<<(std::ostream&, const Mat4&);

    // Methods
    void translate (const Vec3&);
    Mat4 translateCopy (const Vec3&) const;
    static size_t mIndex(size_t col, size_t row);

    void scale (const Vec3&);
    Mat4 scaleCopy(const Vec3&) const;

    void rotateX(const GLfloat&);
    void rotateY(const GLfloat&);
    void rotateZ(const GLfloat&);
    Mat4 rotateCopyX(const GLfloat&) const;
    Mat4 rotateCopyY(const GLfloat&) const;
    Mat4 rotateCopyZ(const GLfloat&) const;

    void lookAt(const Vec3&, const Vec3&, const Vec3&); //     params: eye, center, up
    Mat4 lookAtCopy(const Vec3&, const Vec3&, const Vec3&) const; // params: eye, center, up

    void perspective(const GLfloat, const GLfloat, const GLfloat, const GLfloat); //     params: fovy, aspect, near, far
    Mat4 perspectiveCopy(const GLfloat, const GLfloat, const GLfloat, const GLfloat) const; // params: fovy, aspect, near, far

    // Testing helpers
    void directPrint() const;
};


#endif //CG1PROJEKT_MAT4_H