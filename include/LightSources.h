//
// Created by tomnir on 31.08.26.
//

#ifndef CG1PROJEKT_LIGHTSOURCES_H
#define CG1PROJEKT_LIGHTSOURCES_H
#include <iostream>
#include <filesystem>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SpotLight.h"
#include "PointLight.h"
#include "Vec3.h"

class LightSources
{
private:
    std::vector<std::shared_ptr<PointLight>> m_pointLights;
    std::vector<std::shared_ptr<SpotLight>> m_spotLights;
public:
    LightSources();
    void addSpotLight(std::shared_ptr<SpotLight> spotLight);
    void addPointLight(std::shared_ptr<PointLight> pointLight);
    void addLight(std::shared_ptr<PointLight> pointLight);
    void addLight(std::shared_ptr<SpotLight>spotLight);
    void clearAllLights();
    void uploadLights(const GLuint& shader) const;
};


#endif //CG1PROJEKT_LIGHTSOURCES_H