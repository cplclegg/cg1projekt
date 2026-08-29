//
// Created by tomnir on 11.08.26.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <iostream>
#include "../../include/TextureData.h"

void framebuffer_size_callback_t([[maybe_unused]]GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int textureDataTest()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(800, 600, "Computergrafik 1", NULL, NULL);

    if (!window)
    {
        printf("Failed to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback_t);
    glfwMakeContextCurrent(window);
    glewInit();
    std::cout << "Running tests for TextureData" << std::endl;
    TextureData testtd {"resources/textures/placeholder.png"};
    GLuint id {testtd.createTexture()};
    if (id != 0)
    {
        std::cout << "OK - Texture object generated." << std::endl;
        std::cout << "End of tests for TextureData" << std::endl;
        return 0;
    } else
    {
        std::cout << "FAILED - Texture object not generated." << std::endl;
        std::cout << "End of tests for TextureData" << std::endl;
        return 1;
    }
}