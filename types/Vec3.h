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
        Vec3(Vec3);
        ~Vec3();
        // Operators
        friend Vec3 operator*(Vec3& lhs, Vec3& rhs);
        friend Vec3 operator+(Vec3& lhs, Vec3& rhs);
        friend Vec3 operator-(Vec3& lhs, Vec3& rhs);
        Vec3 operator*(double rhs);
        friend Vec3 operator*(Vec3& lhs, double rhs);
        Vec3 operator=(Vec3& rhs);
        friend bool operator==(Vec3& lhs, Vec3& rhs)
        GLfloat& operator() (size_t column, size_t row);
        // Methods
        GLfloat getLength();
        GLfloat scalarProduct(Vec3& rhs);
};


#endif //CG1PROJEKT_VEC3_H