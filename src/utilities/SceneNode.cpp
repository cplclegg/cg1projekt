//
// Created by tomnir on 15.08.26.
//

#include "../../include/SceneNode.h"

SceneNode::SceneNode(Renderable& object)
    : object {object}
    , children {}
{
}

SceneNode::SceneNode(ObjectData& geometry, Material& material)
    : object { Renderable{geometry, material} }
    , children {}
{
}

void SceneNode::addChild(SceneNode& child)
{
    children.push_back(child);
}
// hier wird die ID der skybox textur mit uebergeben, damit sie an alle shaderprogramme weitergegeben werden kann
void SceneNode::draw(Mat4& parentWorldTransform, Mat4& viewMatrix, Mat4& projectionMatrix, GLuint skyboxTextureID, LightSources& lights)
{
    Mat4 worldTransform {parentWorldTransform*localTransform};

    //Mat4 worldTransform {};
    if (!children.empty())
    {
        std::cout << "entered if case for child scene nodes" << std::endl;
        for (auto& child : children)
        {
            std::cout << "drawing child" << std::endl;
            child.draw(worldTransform, viewMatrix, projectionMatrix, skyboxTextureID, lights);
        }
    }

    Mat3 normalMatrix { (projectionMatrix * viewMatrix * worldTransform).getNormalMatrix() };

    object.getMaterial().bind();
    lights.uploadLights(object.getMaterial().getShader());
    glBindVertexArray(object.getVao());

    if (skyboxTextureID != 0)
    {
        // hier wird die skybox an den shader uebergeben
        GLint skyboxLocation = glGetUniformLocation(object.getMaterial().getShader(), "skybox");
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
        glUniform1i(skyboxLocation, 6);
    }

    GLint transformLocation = glGetUniformLocation(object.getMaterial().getShader(), "mWorld");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, worldTransform.getMatrix());
    GLint viewLocation = glGetUniformLocation(object.getMaterial().getShader(), "mView");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, viewMatrix.getMatrix());
    GLint projLocation = glGetUniformLocation(object.getMaterial().getShader(), "mProj");
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, projectionMatrix.getMatrix());
    GLint normalLocation = glGetUniformLocation(object.getMaterial().getShader(), "mNormal");
    glUniformMatrix3fv(normalLocation, 1, GL_FALSE, normalMatrix.getMatrix());
    std::cout << "world transform:\n";
    worldTransform.directPrint();
    std::cout << std::endl;
    glDrawArrays(GL_TRIANGLES, 0, object.getVertexCount());
}

void SceneNode::translate(const Vec3& vector)
{
    localTransform.translate(vector);
}

void SceneNode::scale(const Vec3& vector)
{
    localTransform.scale(vector);
}

void SceneNode::rotateX(const GLfloat& vector)
{
    localTransform.rotateX(vector);
}

void SceneNode::rotateY(const GLfloat& vector)
{
    localTransform.rotateY(vector);
}

void SceneNode::rotateZ(const GLfloat& vector)
{
    localTransform.rotateZ(vector);
}
