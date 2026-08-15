//
// Created by tomnir on 15.08.26.
//

#include "../../include/SceneNode.h"

SceneNode::SceneNode(Renderable& object)
    : object {object}
    , children {}
{
}

void SceneNode::addChild(SceneNode& child)
{
    children.push_back(child);
}

void SceneNode::draw(Mat4& parentWorldTransform, Mat4& cameraTransform)
{
    Mat4 worldTransform {parentWorldTransform*localTransform};
    if (!children.empty())
    {
        for (auto& child : children)
        {
            child.draw(worldTransform, cameraTransform);
        }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    object.getMaterial().bind();
    glBindVertexArray(object.getVao());

    GLint transformLocation = glGetUniformLocation(object.getMaterial().getShader(), "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, worldTransform.getMatrix());

    glDrawArrays(GL_TRIANGLES, 0, object.getVertexCount());
}