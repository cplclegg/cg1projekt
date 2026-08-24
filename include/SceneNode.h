//
// Created by tomnir on 15.08.26.
//

#ifndef CG1PROJEKT_SCENENODE_H
#define CG1PROJEKT_SCENENODE_H
#include "Material.h"
#include "Renderable.h"
#include <vector>
class SceneNode
{
private:
    Renderable object;
    Mat4 localTransform {};
    std::vector<SceneNode> children;
public:
    SceneNode(Renderable& object);
    void addChild(SceneNode& child);
    void draw(Mat4& parentWorldTransform, Mat4& viewMatrix, Mat4& projectionMatrix);
};


#endif //CG1PROJEKT_SCENENODE_H