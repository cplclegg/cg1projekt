//
// Created by tomnir on 10.08.26.
//

#ifndef CG1PROJEKT_TEXTUREDATA_H
#define CG1PROJEKT_TEXTUREDATA_H

#include "include/ResourceLocator.h"
#include <iostream>
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TextureData
{
private:
    int m_width = 0;
    int m_height = 0;
    int m_channels = 0;
    unsigned char *m_imageData = nullptr;
    std::filesystem::path m_location;
    bool m_created = false;
    GLenum m_target = GL_TEXTURE_2D;
    GLuint m_textureName;

public:

    explicit TextureData(const std::filesystem::path& relativePath);
    explicit TextureData(const std::filesystem::path& relativePath, GLenum target);

    void loadImageData();

    GLuint createTexture();
    GLuint getTextureName();
};


#endif //CG1PROJEKT_TEXTUREDATA_H