//
// Created by tomnir on 10.08.26.
//

#ifndef CG1PROJEKT_TEXTUREDATA_H
#define CG1PROJEKT_TEXTUREDATA_H

#include "../../include/ResourceLocator.h"
#include <iostream>
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TextureData
{
private:
    int m_width {0};
    int m_height {0};
    int m_channels {0};
    unsigned char *m_imageData {nullptr};
    std::filesystem::path m_location;
    bool m_created {false};
    GLenum m_target {GL_TEXTURE_2D};
    GLuint m_textureName {0};
    GLint m_wrappingS {GL_REPEAT};
    GLint m_wrappingT {GL_REPEAT};
    GLint m_filteringMIN {GL_NEAREST};
    GLint m_filteringMAG {GL_NEAREST};

public:
    TextureData();
    explicit TextureData(const std::filesystem::path& relativePath);
    explicit TextureData(const std::filesystem::path& relativePath, GLenum target);

    void loadImageData();

    GLuint createTexture();
    GLuint getTextureName();

    void setFiltering(GLint minFiltering, GLint magFiltering);
    void setWrapping(GLint sWrapping, GLint tWrapping);

    void applyParameters() const;

    bool isUsable() const;
};


#endif //CG1PROJEKT_TEXTUREDATA_H