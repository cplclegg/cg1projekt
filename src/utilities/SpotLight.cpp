//
// Created by tomnir on 02.09.26.
//

#include "../../include/SpotLight.h"

SpotLight::SpotLight(Vec3& pos, Vec3& dir, Vec3& color, GLfloat innerAngle, GLfloat outerAngle)
    : position{pos}
    , direction {dir}
    , color {color}
    , angleInnerCone {innerAngle}
    , angleOuterCone {outerAngle}
{
}

void SpotLight::setColor(Vec3& color)
{
    color = color;
    dirty = true;
}

void SpotLight::setIntensity(GLfloat intensity)
{
    intensity = intensity;
    dirty = true;
}

void SpotLight::setDirection(Vec3& dir)
{
    direction = dir;
    dirty = true;
}

void SpotLight::setPosition(Vec3& pos)
{
    position = pos;
    dirty = true;
}

void SpotLight::upload(GLuint shader, site_t i)
{
    if (!dirty) return;
    /*
     * todo
     */
    dirty = false;
}