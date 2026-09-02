//
// Created by tomnir on 02.09.26.
//

#include "../../include/SpotLight.h"

SpotLight::SpotLight(Vec3& pos, Vec3& dir, Vec3& color, GLfloat innerAngle, GLfloat outerAngle, GLfloat intensity)
    : m_position{pos}
    , m_direction {dir}
    , m_color {color}
    , m_angleInnerCone {innerAngle}
    , m_angleOuterCone {outerAngle}
    , m_intensity {intensity}
{
}

void SpotLight::setColor(Vec3& color)
{
    m_color = color;
    m_dirty = true;
}

void SpotLight::setIntensity(GLfloat intensity)
{
    m_intensity = intensity;
    m_dirty = true;
}

void SpotLight::setDirection(Vec3& dir)
{
    m_direction = dir;
    m_dirty = true;
}

void SpotLight::setPosition(Vec3& pos)
{
    m_position = pos;
    m_dirty = true;
}

void SpotLight::setCone(GLfloat innerAngle, GLfloat outerAngle)
{
    m_angleInnerCone = innerAngle;
    m_angleOuterCone = outerAngle;
    m_dirty = true;
}

void SpotLight::setDirty()
{
    m_dirty = true;
}

void SpotLight::upload(const GLuint shader, site_t i) const
{
    if (!m_dirty) return;
    /*
     * todo
     */


    m_dirty = false;
}