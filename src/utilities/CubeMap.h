//
// Created by tomnir on 29.08.26.
//

#ifndef CG1PROJEKT_CUBEMAP_H
#define CG1PROJEKT_CUBEMAP_H
#include <filesystem>
#include <vector>
#include <GL/glew.h>

class CubeMap
{
private:
    int m_width {0};
    int m_height {0};
    int m_channels {0};
    GLenum m_target {GL_TEXTURE_CUBE_MAP};
    GLuint m_textureName {0};
    GLint m_wrappingS {GL_CLAMP_TO_EDGE};
    GLint m_wrappingT {GL_CLAMP_TO_EDGE};
    GLint m_wrappingR {GL_CLAMP_TO_EDGE};
    GLint m_filteringMIN {GL_LINEAR};
    GLint m_filteringMAG {GL_LINEAR};
    bool m_created {false};
    std::vector<std::filesystem::path> m_locations;
    std::vector<unsigned char *>m_imageData;
public:
    CubeMap(
        const std::filesystem::path& right,
        const std::filesystem::path& left,
        const std::filesystem::path& top,
        const std::filesystem::path& bot,
        const std::filesystem::path& back,
        const std::filesystem::path& front
    );
    void loadImageData();
    GLuint createTexture();
    GLuint getTextureName();

    void setFiltering(GLint minFiltering, GLint magFiltering);
    void setWrapping(GLint sWrapping, GLint tWrapping, GLint rWrapping);

    void applyParameters() const;

    bool isUsable() const;
};


#endif //CG1PROJEKT_CUBEMAP_H