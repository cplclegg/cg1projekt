//
// Created by tomnir on 31.08.26.
//

#include "../../include/LightSources.h"

LightSources::LightSources()
    : m_numberOfPointLights {0}
    , m_numberOfSpotlights {0}
{
}

void LightSources::addPointLight(const PointLight& pointLight)
{
    m_pointLights.push_back(std::make_shared<PointLight>(pointLight));

}

void LightSources::addSpotLight(const SpotLight& spotLight)
{
    m_spotLights.push_back(std::make_shared<SpotLight>(spotLight));
}

void LightSources::clearAllLights()
{
    m_pointLights.clear();
    m_spotLights.clear();
    m_numberOfPointLights = 0;
    m_numberOfSpotlights = 0;
}

void LightSources::uploadLights(GLuint shader)
{

}
