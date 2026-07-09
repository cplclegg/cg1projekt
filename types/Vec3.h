//
// Created by tomnir on 08.07.26.
//

#ifndef CG1PROJEKT_VEC3_H
#define CG1PROJEKT_VEC3_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Vec3
{
private:
        const std::size_t m_dimension = 3;
        GLfloat m_vector[3];
public:
        // Operators
        GLfloat& operator() (const int);
        const GLfloat& operator() (const int) const;
        friend Vec3 operator*(const Vec3&, const Vec3&);
		friend Vec3 operator*(const GLfloat, const Vec3&);
        friend Vec3 operator+(const Vec3&, const Vec3&);
        friend Vec3 operator-(const Vec3&, const Vec3&);
        Vec3 operator*(const GLfloat rhs) const;
        Vec3 operator=(const Vec3& rhs);
        friend bool operator==(const Vec3&, const Vec3&);
        // Object mgmt
        Vec3();
        Vec3(const GLfloat, const GLfloat, const GLfloat);
        Vec3(const Vec3&);
        // Methods
        GLfloat getLength();
        GLfloat scalarProduct(const Vec3&);
};
#endif //CG1PROJEKT_VEC3_H