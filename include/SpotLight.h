//
// Created by tomnir on 02.09.26.
//

#ifndef CG1_NEU_SPOTLIGHT_H
#define CG1_NEU_SPOTLIGHT_H
#include "Vec3.h"
#include <GL/glew.h>

class SpotLight
{
    Vec3 m_position, m_direction, m_color;
    GLfloat m_angleInnerCone, m_angleOuterCone;
    GLfloat m_intensity;
    bool m_dirty {true};
public:
    SpotLight(Vec3& pos, Vec3& dir, Vec3& color, GLfloat innerAngle, GLfloat outerAngle, GLfloat intensity);
    void setPosition(Vec3& pos);
    void setDirection(Vec3& dir);
    void setColor(Vec3& color);
    void setIntensity(GLfloat intensity);
    void setCone(GLfloat innerAngle, GLfloat outerAngle);
    void setDirty();
    void upload(const GLuint shader, size_t i) const;
};


#endif //CG1_NEU_SPOTLIGHT_H