//
// Created by tomnir on 06.08.26.
//

#include "../../include/ShaderProgram.h"

ShaderProgram::ShaderProgram()
    : m_vertexShader {}
    , m_fragmentShader {}
    , m_programID {0}
{
}

ShaderProgram::ShaderProgram(const std::string& vertexShaderLocation, const std::string& fragmentShaderLocation, GLuint program)
    : m_vertexShader {vertexShaderLocation}
    , m_fragmentShader {fragmentShaderLocation}
    , m_programID {program}
{
    createProgram();
}

ShaderProgram::ShaderProgram(const ShaderProgram& other)
    : m_vertexShader {other.m_vertexShader}
    , m_fragmentShader {other.m_fragmentShader}
    , m_programID {other.m_programID}
    , m_exists {other.m_exists}
    , m_vertexStatus {other.m_vertexStatus}
    , m_fragmentStatus {other.m_fragmentStatus}
    , m_linkerStatus {other.m_linkerStatus}
    , m_validationStatus {other.m_validationStatus}
{
    createProgram();
}

void ShaderProgram::addVertexShaderSource(const std::string& path)
{
    m_vertexShader.loadSourceFile(path);
}

void ShaderProgram::addFragmentShaderSource(const std::string& path)
{
    m_fragmentShader.loadSourceFile(path);
}

void ShaderProgram::assignProgramID(GLuint program)
{
    m_programID = program;
}

bool ShaderProgram::checkSuccessfulCreation() const
{
    const bool totalStatus {m_vertexStatus && m_fragmentStatus && m_linkerStatus && m_validationStatus};
    if (!m_vertexStatus)
    {
        printf("Error compiling vertex shader:");
        printf(m_vertexInfoLog);
    }
    if (!m_fragmentStatus)
    {
        printf("Error compiling fragment shader:");
        printf(m_fragmentInfoLog);
    }
    if (!m_linkerStatus)
    {
        printf("Error linking program:");
        printf(m_linkerInfoLog);
    }
    if (!m_validationStatus)
    {
        printf("Error alidating program:");
        printf(m_validationInfoLog);
    }
    return totalStatus;
}

void ShaderProgram::createProgram()
{
    // create+compile vertex shader
    const char* vertexText = m_vertexShader.getSourceString();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexText, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &m_vertexStatus);
    if (!m_vertexStatus)
    {
        glGetShaderInfoLog(vertexShader, 1024, NULL, m_vertexInfoLog);
    }

    // create+compile fragment shader
    const char* fragmentText = m_fragmentShader.getSourceString();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentText, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &m_fragmentStatus);
    if (!m_fragmentStatus)
    {
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
    }

    // create and link shader program
    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertexShader);
    glAttachShader(m_programID, fragmentShader);
    glLinkProgram(m_programID);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &m_linkerStatus);
    if (m_linkerStatus)
    {
        glGetProgramInfoLog(m_programID, 1024, NULL, m_linkerInfoLog);
    }

    // validate shader program
    glValidateProgram(m_programID);
    glGetProgramiv(m_programID, GL_VALIDATE_STATUS, &m_validationStatus);
    if (!m_validationStatus)
    {
        glGetProgramInfoLog(m_programID, 1024, NULL, m_vertexInfoLog);
    }

    m_exists = checkSuccessfulCreation();
}
