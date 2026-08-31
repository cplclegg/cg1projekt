//
// Created by tomnir on 31.08.26.
//

#ifndef CG1PROJEKT_LIGHTSOURCES_H
#define CG1PROJEKT_LIGHTSOURCES_H
#include "include/ResourceLocator.h"
#include <iostream>
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class LightSources
{
private:
    int m_numberOfPointLights;
    int m_numberOfSpotlights;
};


#endif //CG1PROJEKT_LIGHTSOURCES_H