//
// Created by tomnir on 15.08.26.
//

#include "Renderable.h"


Renderable::Renderable(ObjectData& object, const Material& material)
    : m_vbo {object.makeVBO()}
    , m_vao {object.makeVAO()}
    , m_vertexCount {object.getVertexCount()}
    , m_material {material}
{
}

