//
// Created by tomnir on 13.08.26.
//

#include "../../include/Material.h"

Material::Material()
    : m_shader {0}
    , m_diffuseMap {0}
    , m_normalMap {0}
    , m_specularMap {0}
    , m_emissiveMap {0}
{
}

Material::Material(
    const GLuint shader,
    const GLuint diffuse,
    const GLuint normal,
    const GLuint specular,
    const GLuint emissive,
    const GLfloat shininess,
    const Vec3& specularColor,
    const Vec3& diffuseColor
    )
    : m_shader {shader}
    , m_diffuseMap {diffuse}
    , m_normalMap {normal}
    , m_specularMap {specular}
    , m_emissiveMap {emissive}
    , m_shininess {shininess}
    , m_specularColor {specularColor}
    , m_diffuseColor {diffuseColor}
{
}

Material::Material(
    const GLuint shader,
    const GLuint diffuse,
    const GLuint normal,
    const GLuint specular,
    const GLuint emissive
    )
    : m_shader {shader}
    , m_diffuseMap {diffuse}
    , m_normalMap {normal}
    , m_specularMap {specular}
    , m_emissiveMap {emissive}
{
}

void Material::addDiffuseMap(const GLuint dm)
{
    m_diffuseMap = dm;
}

void Material::addNormalMap(const GLuint nm)
{
    m_normalMap = nm;
}

void Material::addSpecularMap(const GLuint sm)
{
    m_specularMap = sm;
}

void Material::addEmissiveMap(const GLuint em)
{
    m_emissiveMap = em;
}

void Material::addShaderProgram(const GLuint program)
{
    m_shader = program;
}

void Material::changeShininess(const GLfloat shininess)
{
    m_shininess = shininess;
}

void Material::changeSpecularColor(const Vec3& specColor)
{
    m_specularColor = specColor;
}

void Material::changeSpecularColor(const GLfloat red, const GLfloat green, const GLfloat blue)
{
    m_specularColor = Vec3 {red, green, blue};
}

void Material::changeDiffuseColor(const Vec3& diffColor)
{
    m_diffuseColor = diffColor;
}

void Material::changeDiffuseColor(const GLfloat red, const GLfloat green, const GLfloat blue)
{
    m_diffuseColor = Vec3 {red, green, blue};
}

GLuint Material::getDiffuse() const
{
    return m_diffuseMap;
}

GLuint Material::getNormal() const
{
    return m_normalMap;
}

GLuint Material::getSpecular() const
{
    return m_specularMap;
}

GLuint Material::getEmissive() const
{
    return m_emissiveMap;
}

GLuint Material::getShader() const
{
    return m_shader;
}