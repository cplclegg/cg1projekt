//
// Created by tomnir on 03.08.26.
//

#ifndef CG1PROJEKT_VERTEX_H
#define CG1PROJEKT_VERTEX_H
#include <types.h>

class Vertex
{
private:
    Vec3 m_vpos;
    Vec3 m_vnormal;
    Vec3 m_vtextureCoord;
public:
    Vec3 getPosition() const;
    Vec3 getNormal() const;
    Vec3 getTextureCoord() const;
    void setPosition(const GLfloat& x, const GLfloat& y, const GLfloat& z);
    void setPosition(const Vec3& vector);
    void setNormal(const GLfloat& x, const GLfloat& y, const GLfloat& z);
    void setNormal(const Vec3& vector);
    void setTextureCoord(const GLfloat& u, const GLfloat& v);
    void setTextureCoord(const GLfloat& u, const GLfloat& v, const GLfloat& w);
};


#endif //CG1PROJEKT_VERTEX_H