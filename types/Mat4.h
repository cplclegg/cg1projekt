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
    //GLfloat m_matrix[4][4];
	GLfloat m_matrix[16];
    size_t m_dimension = 4;
    size_t index(const size_t, const size_t);
public:
    // Constructors and object maangement
    Mat4();
    Mat4(const Mat4&);

    // Operators
    friend Mat4 operator* (const Mat4&, const Mat4&);
    Mat4 operator* (const GLfloat rhs);
    friend Mat4 operator* (const GLfloat, const Mat4&);
    GLfloat& operator() (const size_t, const size_t);
    const GLfloat& operator() (const size_t, const size_t) const;
    friend bool operator==(const Mat4&, const Mat4&);
    Mat4 operator=(const Mat4&);
    friend std::ostream& operator<<(std::ostream&, const Mat4&);

    // Methods

    void translate (const Vec3&);
    Mat4 translateCopy (const Vec3&);

    void scale (const Vec3&);
    Mat4 scaleCopy(const Vec3&);

    void rotateX(const GLfloat);
    void rotateY(const GLfloat);
    void rotateZ(const GLfloat);
    Mat4 rotateCopyX(const GLfloat);
    Mat4 rotateCopyY(const GLfloat);
    Mat4 rotateCopyZ(const GLfloat);

    void lookAt(const GLfloat, const GLfloat, const GLfloat); //     params: eye, center, up
    Mat4 lookAtCopy(const GLfloat, const GLfloat, const GLfloat); // params: eye, center, up

    void perspective(const GLfloat, const GLfloat, const GLfloat, const GLfloat); //     params: fovy, aspect, near, far
    void perspectiveCopy(const GLfloat, const GLfloat, const GLfloat, const GLfloat); // params: fovy, aspect, near, far

    // Testing helpers
    void directPrint();
	friend void accessorTest();
};


#endif //CG1PROJEKT_MAT4_H