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

void SceneNode::draw(Mat4& parentWorldTransform, Mat4& viewMatrix, Mat4& projectionMatrix)
{
    Mat4 worldTransform {parentWorldTransform*localTransform};
    if (!children.empty())
    {
        for (auto& child : children)
        {
            child.draw(worldTransform, viewMatrix, projectionMatrix);
        }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    object.getMaterial().bind();
    glBindVertexArray(object.getVao());

    GLint transformLocation = glGetUniformLocation(object.getMaterial().getShader(), "mWorld");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, worldTransform.getMatrix());
    GLint viewLocation = glGetUniformLocation(object.getMaterial().getShader(), "mView");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, viewMatrix.getMatrix());
    GLint projLocation = glGetUniformLocation(object.getMaterial().getShader(), "mProj");
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, projectionMatrix.getMatrix());

    glDrawArrays(GL_TRIANGLES, 0, object.getVertexCount());
}