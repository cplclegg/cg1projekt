//
// Created by tomnir on 31.08.26.
//

#include "../../include/LightSources.h"

LightSources::LightSources() = default;

void LightSources::addPointLight(const PointLight& pointLight)
{
    if (m_pointLights.size() >= 10) throw std::runtime_error("Max point lights exceeded. Max is 10.");
    m_pointLights.push_back(std::make_shared<PointLight>(pointLight));

}

void LightSources::addSpotLight(const SpotLight& spotLight)
{
    if (m_pointLights.size() >= 2) throw std::runtime_error("Max spot lights exceeded. Max is 2.");
    m_spotLights.push_back(std::make_shared<SpotLight>(spotLight));
}

void LightSources::clearAllLights()
{
    for (const auto& pointLight : m_pointLights) pointLight->setDirty();
    for (const auto& spotLight : m_spotLights) spotLight->setDirty();
    m_pointLights.clear();
    m_spotLights.clear();
}

void LightSources::uploadLights(const GLuint& shader) const
{
    const GLint numPointLightsLoc = glGetUniformLocation(shader, "numPointLights");
    const GLint numSpotLightsLoc = glGetUniformLocation(shader, "numSpotLights");
    glUniform1f(numPointLightsLoc, m_pointLights.size());
    glUniform1f(numSpotLightsLoc, m_spotLights.size());
    for (size_t i = 0; i < m_pointLights.size(); ++i)
    {
        m_pointLights[i]->upload(shader, i);
    }
    for (size_t j = 0; j < m_spotLights.size(); ++j)
    {
        m_spotLights[j]->upload(shader, j);
    }
}
