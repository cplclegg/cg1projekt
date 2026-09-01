//
// Created by tomnir on 02.09.26.
//

#ifndef CG1_NEU_POINTLIGHT_H
#define CG1_NEU_POINTLIGHT_H

#include "Vec3.h"
#include <GL/glew.h>

class PointLight
{
    Vec3 position, color;
    GLfloat intensity;
    bool dirty {true};
public:
    PointLight(Vec3& pos, Vec3& color, GLfloat intensity);
    void setPosition(Vec3& pos);
    void setColor(Vec3& color);
    void setIntensity(GLfloat intensity);
    void upload(GLuint shader, size_t i);
};


#endif //CG1_NEU_POINTLIGHT_H