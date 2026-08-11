//
// Created by tomnir on 10.08.26.
//

#include "../../include/TextureData.h"

using namespace std;

TextureData::TextureData(const std::filesystem::path& relativePath)
    : m_location { ResourceLocator::getResourcePath(relativePath) }
    , m_textureName {}
{
    loadImageData();
}

TextureData::TextureData(const std::filesystem::path& relativePath, GLenum target)
    : m_location { ResourceLocator::getResourcePath(relativePath) }
    , m_target {target}
    , m_textureName {}
{
    loadImageData();
}

void TextureData::loadImageData()
{
    m_imageData = stbi_load(m_location.c_str(), &m_width, &m_height, &m_channels, 0);
    if (m_imageData == nullptr)
    {
        cout << "Error loading image data from " << m_location << " " << endl;
    }
}

GLuint TextureData::createTexture()
{
    if (m_created)
    {
        return m_textureName;
    }
    glGenTextures(1, &m_textureName);
    glBindTexture(m_target, m_textureName);
    switch (m_target) // in case of future use of 1d/3d texture expand cases to adjust
    {
    case GL_TEXTURE_2D:
        glTexImage2D(
            m_target,
            0,
            GL_RGB,
            m_width,
            m_height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            m_imageData
        );
        break;
    default:
        break;
    }
    glGenerateMipmap(m_target);
    m_created = true;
    stbi_image_free(m_imageData);
    glBindTexture(m_target, 0);
    return m_textureName;
}

GLuint TextureData::getTextureName()
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

