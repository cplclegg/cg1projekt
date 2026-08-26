//
// Created by tomnir on 13.08.26.
//

#include "../../include/Material.h"

Material::Material(
    const GLuint shader,
    const TextureData& diffuse,
    const TextureData& normal,
    const TextureData& specular,
    const TextureData& emissive,
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
    const TextureData& diffuse,
    const TextureData& normal,
    const TextureData& specular,
    const TextureData& emissive
    )
    : m_shader {shader}
    , m_diffuseMap {diffuse}
    , m_normalMap {normal}
    , m_specularMap {specular}
    , m_emissiveMap {emissive}
{
}

Material::Material(const Material& other) = default;

void Material::bind()
{
    if (m_shader == 0) throw std::runtime_error("Missing shader program");

    glUseProgram(m_shader);

    glActiveTexture(GL_TEXTURE0);
    if (m_diffuseMap.isUsable())
    {
        glBindTexture(GL_TEXTURE_2D, m_diffuseMap.getTextureName());
        m_diffuseMap.applyParameters();
        GLint diffuseMapUniformLoc = glGetUniformLocation(m_shader, "diffuseMap");
        glUniform1i(diffuseMapUniformLoc, 0);

    } else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glActiveTexture(GL_TEXTURE1);
    if (m_normalMap.isUsable())
    {
        glBindTexture(GL_TEXTURE_2D, m_normalMap.getTextureName());
        m_normalMap.applyParameters();
        GLint normalMapUniformLoc = glGetUniformLocation(m_shader, "normalMap");
        glUniform1i(normalMapUniformLoc, 1);
    } else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glActiveTexture(GL_TEXTURE2);
    if (m_specularMap.isUsable())
    {
        glBindTexture(GL_TEXTURE_2D, m_specularMap.getTextureName());
        m_specularMap.applyParameters();
        GLint specularMapUniformLoc = glGetUniformLocation(m_shader, "specularMap");
        glUniform1i(specularMapUniformLoc, 2);
    } else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glActiveTexture(GL_TEXTURE3);
    if (m_emissiveMap.isUsable())
    {
        glBindTexture(GL_TEXTURE_2D, m_emissiveMap.getTextureName());
        m_emissiveMap.applyParameters();
        GLint emissiveMapUniformLoc = glGetUniformLocation(m_shader, "emissiveMap");
        glUniform1i(emissiveMapUniformLoc, 3);
    } else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    GLint shininessUniformLocation = glGetUniformLocation(m_shader, "shininess");
    GLint specularColorLocation = glGetUniformLocation(m_shader, "specularColor");
    GLint diffuseColorLocation = glGetUniformLocation(m_shader, "diffuseColor");
    glUniform1f(shininessUniformLocation, m_shininess);
    glUniform3fv(specularColorLocation, 1, m_specularColor.getArray());
    glUniform3fv(diffuseColorLocation, 1, m_diffuseColor.getArray());
}
/*
void Material::addDiffuseMap(const GLuint dm)
{
    m_diffuseMap {dm};
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
*/
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

GLuint Material::getDiffuse()
{
    return m_diffuseMap.getTextureName();
}

GLuint Material::getNormal()
{
    return m_normalMap.getTextureName();
}

GLuint Material::getSpecular()
{
    return m_specularMap.getTextureName();
}

GLuint Material::getEmissive()
{
    return m_emissiveMap.getTextureName();
}

GLuint Material::getShader() const
{
    return m_shader;
}