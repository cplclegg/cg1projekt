//
// Created by tomnir on 10.08.26.
//

#include "../../include/TextureData.h"
#include <cassert>
#include "stb_image.h"
using namespace std;

TextureData::TextureData() = default;

TextureData::TextureData(const std::filesystem::path& relativePath)
    : m_location { ResourceLocator::getResourcePath(relativePath) }
{
    loadImageData();
}

TextureData::TextureData(const std::filesystem::path& relativePath, GLenum target)
    : m_location { ResourceLocator::getResourcePath(relativePath) }
    , m_target {target}
{
    loadImageData();
}

void TextureData::loadImageData()
{
    stbi_set_flip_vertically_on_load(true);
    m_imageData = stbi_load(m_location.c_str(), &m_width, &m_height, &m_channels, 0);
    if (m_imageData == nullptr)
    {
        cout << "Error loading image data from " << m_location << " " << endl;
        throw std::runtime_error("Failed to load texture file!");
    }
}

GLuint TextureData::createTexture()
{
    assert(m_imageData != nullptr);
    assert(m_width > 0);
    assert(m_height > 0);
    assert(m_target == GL_TEXTURE_2D);
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

    // Format auf RGBA evtl setzen
    GLenum format = (m_channels == 4) ? GL_RGBA : GL_RGB;

    switch (m_target) // in case of future use of 1d/3d texture expand cases to adjust
    {
    case GL_TEXTURE_2D:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(
            m_target,
            0,
            format,
            m_width,
            m_height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            m_imageData
        );
        break;
    default:
        break;
    }
    glGenerateMipmap(m_target);
    stbi_image_free(m_imageData);
    m_imageData = nullptr;
    m_created = true;
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

void TextureData::setFiltering(GLint minFiltering, GLint magFiltering)
{
    m_filteringMIN = minFiltering;
    m_filteringMAG = magFiltering;
}

void TextureData::setWrapping(const GLint sWrapping, const GLint tWrapping)
{
    m_wrappingS = sWrapping;
    m_wrappingT = tWrapping;
}

void TextureData::applyParameters() const
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, m_wrappingS);
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, m_wrappingT);
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, m_filteringMIN);
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, m_filteringMAG);
}

bool TextureData::isUsable() const
{
    return m_created;
}
