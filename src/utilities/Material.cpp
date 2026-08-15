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

Material::Material(const Material& other)
    : m_shader {other.m_shader}
    , m_diffuseMap {other.m_diffuseMap}
    , m_normalMap {other.m_normalMap}
    , m_specularMap {other.m_specularMap}
    , m_emissiveMap {other.m_emissiveMap}
    , m_shininess {other.m_shininess}
    , m_specularColor {other.m_specularColor}
    , m_diffuseColor {other.m_diffuseColor}
{
}

void Material::bind() const
{
    if (m_shader == 0) throw std::runtime_error("Missing shader program");

    glUseProgram(m_shader);

    glActiveTexture(GL_TEXTURE0);
    if (m_diffuseMap)
    {
        glBindTexture(GL_TEXTURE_2D, m_diffuseMap);
    } else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glActiveTexture(GL_TEXTURE1);
    if (m_normalMap)
    {
        glBindTexture(GL_TEXTURE_2D, m_normalMap);
    } else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glActiveTexture(GL_TEXTURE2);
    if (m_specularMap)
    {
        glBindTexture(GL_TEXTURE_2D, m_specularMap);
    } else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glActiveTexture(GL_TEXTURE3);
    if (m_emissiveMap)
    {
        glBindTexture(GL_TEXTURE_2D, m_emissiveMap);
    } else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
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