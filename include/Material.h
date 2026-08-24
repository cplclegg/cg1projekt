//
// Created by tomnir on 13.08.26.
//

#ifndef CG1PROJEKT_MATERIAL_H
#define CG1PROJEKT_MATERIAL_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../include/ShaderProgram.h"
#include "../../include/TextureData.h"
#include "../../include/Vec3.h"
class Material
{
private:
    GLuint m_shader;
    TextureData m_diffuseMap;
    TextureData m_normalMap;
    TextureData m_specularMap;
    TextureData m_emissiveMap;

    GLfloat m_shininess {32.0f}; // change or remove standard value if necessary
    Vec3 m_specularColor {1.0f, 1.0f, 1.0f};
    Vec3 m_diffuseColor {1.0f, 1.0f, 1.0f};
public:

    Material(
        GLuint shader,
        const TextureData& diffuse,
        const TextureData& normal,
        const TextureData& specular,
        const TextureData& emissive
        );

    Material(
        GLuint shader,
        const TextureData& diffuse,
        const TextureData& normal,
        const TextureData& specular,
        const TextureData& emissive,
        GLfloat shininess,
        const Vec3& specularColor,
        const Vec3& diffuseColor
        );

    Material(const Material& other);
    /*
    void addDiffuseMap(GLuint dm);
    void addNormalMap(GLuint nm);
    void addSpecularMap(GLuint sm);
    void addEmissiveMap(GLuint em);
    void addShaderProgram(GLuint program);
    */
    void changeShininess(GLfloat shininess);

    void changeSpecularColor(const Vec3& specColor);
    void changeSpecularColor(GLfloat red, GLfloat green, GLfloat blue);

    void changeDiffuseColor(const Vec3& diffColor);
    void changeDiffuseColor(GLfloat red, GLfloat green, GLfloat blue);

    GLuint getDiffuse();
    GLuint getNormal();
    GLuint getSpecular();
    GLuint getEmissive();
    GLuint getShader() const;

    void bind();
};


#endif //CG1PROJEKT_MATERIAL_H