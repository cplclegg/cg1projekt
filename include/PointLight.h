//
// Created by tomnir on 02.09.26.
//

#ifndef CG1_NEU_POINTLIGHT_H
#define CG1_NEU_POINTLIGHT_H

#include "Vec3.h"
#include <GL/glew.h>

class PointLight
{
    Vec3 m_position, m_color;
    GLfloat m_constant, m_linear, m_quadratic;
    bool m_dirty {true};
public:
    PointLight(Vec3& pos, Vec3& color, GLfloat constant, GLfloat linear, GLfloat quadratic);
    void setPosition(Vec3& pos);
    void setColor(Vec3& color);
    void setAttenuationFactors(GLfloat constant, GLfloat linear, GLfloat quadratic);
    void upload(GLuint shader, size_t i);
};


#endif //CG1_NEU_POINTLIGHT_H