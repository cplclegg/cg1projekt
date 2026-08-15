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
    GLuint m_diffuseMap;
    GLuint m_normalMap;
    GLuint m_specularMap;
    GLuint m_emissiveMap;

    GLfloat m_shininess {32.0f}; // change or remove standard value if necessary
    Vec3 m_specularColor {1.0f, 1.0f, 1.0f};
    Vec3 m_diffuseColor {1.0f, 1.0f, 1.0f};
public:
    Material();

    Material(
        GLuint shader,
        GLuint diffuse,
        GLuint normal,
        GLuint specular,
        GLuint emissive
        );

    Material(
        GLuint shader,
        GLuint diffuse,
        GLuint normal,
        GLuint specular,
        GLuint emissive,
        GLfloat shininess,
        const Vec3& specularColor,
        const Vec3& diffuseColor
        );

    Material(const Material& other);

    void addDiffuseMap(GLuint dm);
    void addNormalMap(GLuint nm);
    void addSpecularMap(GLuint sm);
    void addEmissiveMap(GLuint em);
    void addShaderProgram(GLuint program);

    void changeShininess(GLfloat shininess);

    void changeSpecularColor(const Vec3& specColor);
    void changeSpecularColor(GLfloat red, GLfloat green, GLfloat blue);

    void changeDiffuseColor(const Vec3& diffColor);
    void changeDiffuseColor(GLfloat red, GLfloat green, GLfloat blue);

    GLuint getDiffuse() const;
    GLuint getNormal() const;
    GLuint getSpecular() const;
    GLuint getEmissive() const;
    GLuint getShader() const;

    void bind() const;
};


#endif //CG1PROJEKT_MATERIAL_H