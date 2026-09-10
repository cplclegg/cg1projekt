//
// Created by tomnir on 09.09.26.
//

#ifndef CG1PROJEKT_SCENEHELPERS_H
#define CG1PROJEKT_SCENEHELPERS_H
#include "Renderable.h"
#include "SceneNode.h"


class SceneHelpers
{
public:
    static std::shared_ptr<SceneNode> makeCandleCluster(const Vec3& xzPosition, Renderable& c1, Renderable& c2, Renderable& c3, Renderable& cf);
};


#endif //CG1PROJEKT_SCENEHELPERS_H