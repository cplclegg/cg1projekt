//
// Created by tomnir on 06.08.26.
//

#ifndef CG1PROJEKT_SHADERPROGRAM_H
#define CG1PROJEKT_SHADERPROGRAM_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "types.h"
#include "ShaderSource.h"
class ShaderProgram
{
private:
    ShaderSource m_vertexShader;
    ShaderSource m_fragmentShader;

    GLuint m_programID;

    bool m_exists = false;

    GLint m_vertexStatus;
    GLchar m_vertexInfoLog[1024];

    GLint m_fragmentStatus;
    GLchar m_fragmentInfoLog[1024];

    GLint m_linkerStatus;
    GLchar m_linkerInfoLog[1024];

    GLint m_validationStatus;
    GLchar m_validationInfoLog[1024];
public:
    ShaderProgram();
    ShaderProgram(const std::string& vertexShaderLocation, const std::string& fragmentShaderLocation, GLuint program);
    ShaderProgram(const ShaderProgram& other); // deep copy
    void addVertexShaderSource(const std::string& path);
    void addFragmentShaderSource(const std::string& path);
    void assignProgramID(GLuint program);
    void createProgram(); // needs to check m_exists and also set m_exists=true after successfully completing
    bool checkSuccessfulCreation() const;
};


#endif //CG1PROJEKT_SHADERPROGRAM_H