//
// Created by tomnir on 15.08.26.
//

#include "../../include/SceneNode.h"

SceneNode::SceneNode()
    : m_object {}
    , m_children {}
{

}

SceneNode::SceneNode(Renderable& object)
    : m_object {object}
    , m_children {}
{
}

SceneNode::SceneNode(ObjectData& geometry, Material& material)
    : m_object { Renderable{geometry, material} }
    , m_children {}
{
}

void SceneNode::addChild(std::shared_ptr<SceneNode>& child)
{
    m_children.push_back(child);
}
// hier wird die ID der skybox textur mit uebergeben, damit sie an alle shaderprogramme weitergegeben werden kann
void SceneNode::draw(Mat4& parentWorldTransform, Mat4& viewMatrix, Mat4& projectionMatrix, GLuint skyboxTextureID, LightSources& lights, GLfloat time)
{
    Mat4 worldTransform {parentWorldTransform*m_localTransform};

    //Mat4 worldTransform {};
    if (!m_children.empty())
    {
        //std::cout << "entered if case for child scene nodes" << std::endl;
        for (auto& child : m_children)
        {
            //std::cout << "drawing child" << std::endl;
            child->draw(worldTransform, viewMatrix, projectionMatrix, skyboxTextureID, lights, time);
        }
    }
    if (!m_object) return;
    Mat4 mvpMatrix {(projectionMatrix * viewMatrix * worldTransform)};
    Mat3 normalMatrix { mvpMatrix.getNormalMatrix() };
    Mat4 cameraWorld {viewMatrix.inverseCopy()};
    m_object->getMaterial().bind();
    lights.uploadLights(m_object->getMaterial().getShader());
    glBindVertexArray(m_object->getVao());

    if (skyboxTextureID != 0)
    {
        // hier wird die skybox an den shader uebergeben
        GLint skyboxLocation = glGetUniformLocation(m_object->getMaterial().getShader(), "skybox");
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
        glUniform1i(skyboxLocation, 6);
    }
    GLint timeLocation = glGetUniformLocation(m_object->getMaterial().getShader(), "time");
    glUniform1f(timeLocation, time);
    GLint transformLocation = glGetUniformLocation(m_object->getMaterial().getShader(), "mWorld");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, worldTransform.getMatrix());
    GLint viewLocation = glGetUniformLocation(m_object->getMaterial().getShader(), "mView");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, viewMatrix.getMatrix());
    GLint projLocation = glGetUniformLocation(m_object->getMaterial().getShader(), "mProj");
    glUniformMatrix4fv(projLocation, 1, GL_FALSE, projectionMatrix.getMatrix());
    GLint normalLocation = glGetUniformLocation(m_object->getMaterial().getShader(), "mNormal");
    glUniformMatrix3fv(normalLocation, 1, GL_FALSE, normalMatrix.getMatrix());
    GLint viewPosLocation = glGetUniformLocation(m_object->getMaterial().getShader(), "viewPos");
    glUniform3f(viewPosLocation, cameraWorld(3,0), cameraWorld(3,1), cameraWorld(3,2));
    glDrawArrays(GL_TRIANGLES, 0, m_object->getVertexCount());
}

void SceneNode::translate(const Vec3& vector)
{
    m_localTransform.translate(vector);
}

void SceneNode::scale(const Vec3& vector)
{
    m_localTransform.scale(vector);
}

void SceneNode::rotateX(const GLfloat& vector)
{
    m_localTransform.rotateX(vector);
}

void SceneNode::rotateY(const GLfloat& vector)
{
    m_localTransform.rotateY(vector);
}

void SceneNode::rotateZ(const GLfloat& vector)
{
    m_localTransform.rotateZ(vector);
}
