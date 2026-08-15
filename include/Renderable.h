//
// Created by tomnir on 15.08.26.
//

#ifndef CG1PROJEKT_RENDERABLE_H
#define CG1PROJEKT_RENDERABLE_H
#include "ObjectData.h"
#include "Material.h"
#include "Mat4.h"
class Renderable
{
private:
    GLuint m_vbo {0};
    GLuint m_vao {0};
    size_t m_vertexCount {0};
    Material m_material;
public:
    Renderable(ObjectData& object, const Material& material);
};


#endif //CG1PROJEKT_RENDERABLE_H