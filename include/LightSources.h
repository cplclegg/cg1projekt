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
#include "SpotLight.h"
#include "PointLight.h"
#include "Vec3.h"

/* Idea/Concept
 *
 * make the structs below into classes. Same member attributes, but acces via getters/setters.
 * add member attributes: bool dirty (false when changed after or not uploaded, true when current state uploaded)
 * add member function: upload(GLuint shader, size_t i). If dirty, uploads the current state and sets dirty=false.
 * Dirty only ever set to false after state was uploaded.
 *
 * The aggregate class LightSources just delegates the upload of all numOfPoint/SpotLights to the objects.
 * They only upload themselves if dirty.
 *
 */

class LightSources
{
private:
    std::vector<std::shared_ptr<PointLight>> m_pointLights;
    std::vector<std::shared_ptr<SpotLight>> m_spotLights;
public:
    LightSources();
    void addSpotLight(const SpotLight& spotLight);
    void addPointLight(const PointLight& pointLight);
    void addLight(const PointLight& pointLight);
    void addLight(const SpotLight& spotLight);
    void clearAllLights();
    void uploadLights(const GLuint& shader) const;
};


#endif //CG1PROJEKT_LIGHTSOURCES_H