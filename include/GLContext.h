//
// Created by tomnir on 28.08.26.
//

#ifndef CG1PROJEKT_GLCONTEXT_H
#define CG1PROJEKT_GLCONTEXT_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLContext
{
public:
    [[nodiscard]] static GLFWwindow* initializeContext();
    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
};


#endif //CG1PROJEKT_GLCONTEXT_H