//
// Created by tomnir on 02.09.26.
//

#include "../../include/PointLight.h"

#include <string>

PointLight::PointLight(const Vec3& pos, const Vec3& color, const GLfloat constant, const GLfloat linear, const GLfloat quadratic)
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
    //if (!m_dirty) return;

    const std::string posUniformName {"pointLights[" + std::to_string(i) + "].pl_pos"};
    const std::string colorUniformName {"pointLights[" + std::to_string(i) + "].pl_color"};
    const std::string constantUniformName {"pointLights[" + std::to_string(i) + "].constant"};
    const std::string linearUniformName {"pointLights[" + std::to_string(i) + "].linear"};
    const std::string quadraticUniformName {"pointLights[" + std::to_string(i) + "].quadratic"};

    const GLint posLocation = glGetUniformLocation(shader, posUniformName.c_str());
    const GLint colorLocation = glGetUniformLocation(shader, colorUniformName.c_str());
    const GLint constantLocation = glGetUniformLocation(shader, constantUniformName.c_str());
    const GLint linearLocation = glGetUniformLocation(shader, linearUniformName.c_str());
    const GLint quadraticLocation = glGetUniformLocation(shader, quadraticUniformName.c_str());

    glUniform3fv(posLocation, 1, m_position.getArray());
    glUniform3fv(colorLocation, 1, m_color.getArray());
    glUniform1f(constantLocation, m_constant);
    glUniform1f(linearLocation, m_linear);
    glUniform1f(quadraticLocation, m_quadratic);

    m_dirty = false;
}

