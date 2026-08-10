//
// Created by tomnir on 04.08.26.
//
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../include/ObjectData.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int objImportTests()
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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glewInit();
    cout << "Running tests for ObjectData" << endl;
    GLuint vbo {};
    ObjectData ojd1 {};
    ojd1.importObjectData("tests/teapot.obj");
    cout << "data imported\n";
    GLfloat* buffer = nullptr;
    buffer = ojd1.getBuffer();
    // cout << "testprint of buffer beginning here" << endl;
    // ojd1.printBuffer();
    // cout << "end of buffer testprint" << endl;
    vbo = ojd1.makeVBO();
    if (vbo != 0 && buffer != nullptr)
    {
        cout << "OK - VBO created and buffer returned." << endl;
        return 0;
    } else
    {
        cout << "VBO creation failed." << endl;
        return 1;
    }
}