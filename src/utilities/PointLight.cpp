//
// Created by tomnir on 02.09.26.
//

#include "../../include/PointLight.h"

PointLight::PointLight(Vec3& pos, Vec3& color, GLfloat constant, GLfloat linear, GLfloat quadratic)
    : m_position{pos}
    , m_color{color}
    , m_constant {constant}
    , m_linear {linear}
    , m_quadratic {quadratic}
{
}

void PointLight::setPosition(Vec3& pos)
{
    m_position = pos;
    m_dirty = true;
}

void PointLight::setColor(Vec3& color)
{
    m_color = color;
    m_dirty = true;
}

void PointLight::setAttenuationFactors(GLfloat constant, GLfloat linear, GLfloat quadratic)
{
    m_constant = constant;
    m_linear = linear;
    m_quadratic = quadratic;
    m_dirty = true;
}

void PointLight::setDirty()
{
    m_dirty = true;
}

void PointLight::upload(const GLuint shader, const size_t i)
{
    if (!m_dirty) return;
    /*
     * todo
     */
    m_dirty = false;
}

