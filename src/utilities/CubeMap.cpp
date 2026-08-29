//
// Created by tomnir on 29.08.26.
//

#include "CubeMap.h"
#include "ResourceLocator.h"
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;
CubeMap::CubeMap(
    ShaderProgram& shader,
    const std::filesystem::path& right,
    const std::filesystem::path& left,
    const std::filesystem::path& top,
    const std::filesystem::path& bot,
    const std::filesystem::path& back,
    const std::filesystem::path& front
    )
        : m_locations
        {
            ResourceLocator::getResourcePath(right),
            ResourceLocator::getResourcePath(left),
            ResourceLocator::getResourcePath(top),
            ResourceLocator::getResourcePath(bot),
            ResourceLocator::getResourcePath(back),
            ResourceLocator::getResourcePath(front)
        }
        , m_shader {shader}
{
    loadImageData();
    createVboAndVao();
}

void CubeMap::createVboAndVao()
{
    GLfloat skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 36, skyboxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3*sizeof(GLfloat),
        0
    );
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CubeMap::loadImageData()
{
    bool success {true};
    for (size_t i = 0; i < 6; ++i)
    {
        m_imageData.push_back(stbi_load(
            m_locations[i].c_str(),
            &m_width,
            &m_height,
            &m_channels,
            0
            ));
        success = success && m_imageData[i];
    }
    if (!success)
    {
        throw std::runtime_error("Error loading image data on cube map creation");
    }

}

GLuint CubeMap::createTexture()
{
    assert(m_width > 0);
    assert(m_height > 0);
    assert(m_target == GL_TEXTURE_CUBE_MAP);
    if (m_created)
    {
        return m_textureName;
    }
    GLenum format;
    switch (m_channels)
    {
    case 1:
        format = GL_RED;
        break;
    case 2:
        format = GL_RG;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    default:
        throw std::runtime_error("Texture channel count not supported");
    }
    glGenTextures(1, &m_textureName);
    glBindTexture(m_target, m_textureName);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned int i = 0; i < m_imageData.size(); ++i)
    {
        glTexImage2D(
           GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
           0,
           format,
           m_width,
           m_height,
           0,
           format,
           GL_UNSIGNED_BYTE,
           m_imageData[i]
       );
        stbi_image_free(m_imageData[i]);
        m_imageData[i] = nullptr;
    }
    m_created = true;
    glBindTexture(m_target, 0);
    return m_textureName;
}

GLuint CubeMap::getTextureName()
{
    if (m_created)
    {
        return m_textureName;
    } else
    {
        createTexture();
        return m_textureName;
    }
}

void CubeMap::setFiltering(GLint minFiltering, GLint magFiltering)
{
    m_filteringMIN = minFiltering;
    m_filteringMAG = magFiltering;
}

void CubeMap::setWrapping(GLint sWrapping, GLint tWrapping, GLint rWrapping)
{
    m_wrappingS = sWrapping;
    m_wrappingT = tWrapping;
    m_wrappingR = rWrapping;
}

void CubeMap::applyParameters() const
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, m_wrappingS);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, m_wrappingT);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_R, m_wrappingR);
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, m_filteringMIN);
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, m_filteringMAG);
}

bool CubeMap::isUsable() const
{
    return m_created;
}

void CubeMap::draw(const Mat4& projection, const Mat4& view) const
{
    glDepthFunc(GL_LEQUAL);
    glUseProgram(m_shader.getID());
    glBindVertexArray(m_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(m_target, m_textureName);
    applyParameters();
    const GLint cubeMapUniformLocation = glGetUniformLocation(m_shader.getID(), "skybox");
    glUniform1i(cubeMapUniformLocation, 0);
    const Mat4 cubeView {view.copyWithoutTranslation()};
    const GLint viewLocation = glGetUniformLocation(m_shader.getID(), "mView");
    const GLint projectionLocation = glGetUniformLocation(m_shader.getID(), "mProjection");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, cubeView.getMatrix());
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projection.getMatrix());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}
