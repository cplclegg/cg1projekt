//
// Created by tomnir on 29.08.26.
//

#ifndef CG1PROJEKT_CUBEMAP_H
#define CG1PROJEKT_CUBEMAP_H
#include <filesystem>
#include <vector>
#include <GL/glew.h>
#include "ShaderProgram.h"

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
    ShaderProgram m_shader;
    GLuint m_vbo {0};
    GLuint m_vao {0};
public:
    CubeMap(
        ShaderProgram& shader,
        const std::filesystem::path& posX,
        const std::filesystem::path& negX,
        const std::filesystem::path& posY,
        const std::filesystem::path& negY,
        const std::filesystem::path& posZ,
        const std::filesystem::path& negZ
    );
    void loadImageData();
    GLuint createTexture();
    GLuint getTextureName();

    void setFiltering(GLint minFiltering, GLint magFiltering);
    void setWrapping(GLint sWrapping, GLint tWrapping, GLint rWrapping);

    void createVboAndVao();

    void applyParameters() const;

    bool isUsable() const;

    void draw(const Mat4& projection, const Mat4& view) const;
};


#endif //CG1PROJEKT_CUBEMAP_H