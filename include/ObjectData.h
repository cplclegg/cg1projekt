//
// Created by tomnir on 03.08.26.
//

#ifndef CG1PROJEKT_OBJECTDATA_H
#define CG1PROJEKT_OBJECTDATA_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "types.h"
using namespace std;
class ObjectData
{
private:
    vector<Vertex> m_vertices;
    size_t m_vertexCount;
public:
    GLuint getVBO() const;
};

#endif //CG1PROJEKT_OBJECTDATA_H