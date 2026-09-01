//
// Created by tomnir on 02.09.26.
//

#include "../../include/PointLight.h"

PointLight::PointLight(Vec3& pos, Vec3& color, GLfloat intensity)
    : position{pos}
    , color{color}
    , intensity {intensity}
{
}

void PointLight::setPosition(Vec3& pos)
{
    position = pos;
    dirty = true;
}

void PointLight::setColor(Vec3& color)
{
    color = color;
    dirty = true;
}

void PointLight::setIntensity(GLfloat intensity)
{
    intensity = intensity;
    dirty = true;
}

void PointLight::upload(GLuint shader, size_t i)
{
    if (!dirty) return;
    /*
     * todo
     */
    dirty = false;
}

