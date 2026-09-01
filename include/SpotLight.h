//
// Created by tomnir on 02.09.26.
//

#ifndef CG1_NEU_SPOTLIGHT_H
#define CG1_NEU_SPOTLIGHT_H
#include "Vec3.h"
#include <GL/glew.h>

class SpotLight
{
    Vec3 position, direction, color;
    GLfloat angleInnerCone, angleOuterCone;
    GLfloat intensity;
    bool dirty {true};
public:
    SpotLight(Vec3& pos, Vec3& dir, Vec3& color, GLfloat innerAngle, GLfloat outerAngle);
    void setPosition(Vec3& pos);
    void setDirection(Vec3& dir);
    void setColor(Vec3& color);
    void setIntensity(GLfloat intensity);
    void upload(GLuint shader, size_t i);
};


#endif //CG1_NEU_SPOTLIGHT_H