//
// Created by tomnir on 08.07.26.
//

#ifndef CG1PROJEKT_VEC3_H
#define CG1PROJEKT_VEC3_H
#include <GL/glew>
#include <GL/glfw>
class Vec3
{
private:
        const std::size_t m_dimension;
        GLfloat m_vector[m_dimension];
public:
        // Object mgmt
        Vec3();
        Vec3(const GLfloat firstComponent, const GLfloat secondComponen, const GLfloat thirdComponent);
        Vec3(Vec3);
        // Operators
        friend Vec3 operator*(const Vec3& lhs, const Vec3& rhs);
        friend Vec3 operator+(const Vec3& lhs, const Vec3& rhs);
        friend Vec3 operator-(const Vec3& lhs, const Vec3& rhs);
        Vec3 operator*(const double rhs);
        Vec3& operator=(const Vec3& rhs);
        friend bool operator==(const Vec3& lhs, const Vec3& rhs);
        GLfloat& operator() (const size_t component);
        // Methods
        GLfloat getLength();
        GLfloat scalarProduct(const Vec3& rhs);
};
#endif //CG1PROJEKT_VEC3_H