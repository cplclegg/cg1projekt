//
// Created by tomnir on 02.09.26.
//

#include "../../include/SpotLight.h"

#include <string>

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

void SpotLight::upload(const GLuint shader, const size_t i)
{
    if (!m_dirty) return;
    const std::string posUniformName {"spotLights[" + std::to_string(i) + "].sl_pos"};
    const std::string colorUniformName {"spotLights[" + std::to_string(i) + "].sl_color"};
    const std::string directionUniformName {"spotLights[" + std::to_string(i) + "].sl_direction"};
    const std::string innerAngleUniformName {"spotLights[" + std::to_string(i) + "].innerAngle"};
    const std::string outerAngleUniformName {"spotLights[" + std::to_string(i) + "].outerAngle"};
    const std::string intensityUniformName {"spotLights[" + std::to_string(i) + "].intensity"};

    const GLint posLocation = glGetUniformLocation(shader, posUniformName.c_str());
    const GLint colorLocation = glGetUniformLocation(shader, colorUniformName.c_str());
    const GLint directionLocation = glGetUniformLocation(shader, directionUniformName.c_str());
    const GLint innerAngleLocation = glGetUniformLocation(shader, innerAngleUniformName.c_str());
    const GLint outerAngleLocation = glGetUniformLocation(shader, outerAngleUniformName.c_str());
    const GLint intensityLocation = glGetUniformLocation(shader, intensityUniformName.c_str());

    glUniform3fv(posLocation, 1, m_position.getArray());
    glUniform3fv(colorLocation, 1, m_color.getArray());
    glUniform3fv(directionLocation, 1, m_direction.getArray());
    glUniform1f(innerAngleLocation, m_angleInnerCone);
    glUniform1f(outerAngleLocation, m_angleOuterCone);
    glUniform1f(intensityLocation, m_intensity);

    m_dirty = false;
}