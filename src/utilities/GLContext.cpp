//
// Created by tomnir on 28.08.26.
//

#include "GLContext.h"

#include <cstdio>
#include <cstdlib>

void GLContext::framebufferSizeCallback([[maybe_unused]]GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* GLContext::initializeContext(int width, int height)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, "Computergrafik 1 - Projektarbeit - Team FireBrick", NULL, NULL);

    if(!window) {
        printf("Failed to crate window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetFramebufferSizeCallback(window, GLContext::framebufferSizeCallback);
    glfwMakeContextCurrent(window);
    glewInit();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Initiale Hintergrundfarbe der Szene
    glViewport(0, 0, width, height);
    return window;
}