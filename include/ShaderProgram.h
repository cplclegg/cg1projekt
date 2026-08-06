//
// Created by tomnir on 06.08.26.
//

#ifndef CG1PROJEKT_SHADERPROGRAM_H
#define CG1PROJEKT_SHADERPROGRAM_H
#include <vector>
#include "types.h"
#include "ShaderSource.h"
class ShaderProgram
{
private:
    std::vector<ShaderSource> m_vertexShaders;
    std::vector<ShaderSource> m_fragmentShaders;
    GLuint m_programID;
public:
    void addVertexShaderSource(const std::string& path);
    void addFragmentShaderSource(const std::string& path);
    void assignProgramToID(GLuint program);
};


#endif //CG1PROJEKT_SHADERPROGRAM_H