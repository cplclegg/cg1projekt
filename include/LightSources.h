//
// Created by tomnir on 31.08.26.
//

#ifndef CG1PROJEKT_LIGHTSOURCES_H
#define CG1PROJEKT_LIGHTSOURCES_H
#include "include/ResourceLocator.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vec3.h"

struct PointLight
{
    Vec3 position, color;
    GLfloat attenuation;
    GLfloat intensity;
};

struct SpotLight
{
    Vec3 position, color, direction;
    GLfloat intensity;
};

class LightSources
{
private:
    int m_numberOfPointLights;
    int m_numberOfSpotlights;
    std::vector<std::shared_ptr<PointLight>> m_pointLights;
    std::vector<std::shared_ptr<SpotLight>> m_spotLights;
public:
    LightSources();
    void addSpotLight(const SpotLight& spotLight);
    void addPointLight(const PointLight& pointLight);
    void clearAllLights();
    void uploadLights();
};


#endif //CG1PROJEKT_LIGHTSOURCES_H