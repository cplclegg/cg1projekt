//
// Created by tomnir on 12.07.26.
//
#include "../utilities/utilities.h"
#include <cstring>
#include <iostream>
using namespace std;
void shaderSourceTest()
{
    ShaderSource s1 {"/home/tomnir/Documents/devel/hshbin/cg1projekt/tests/testShaderSource.glsl"};
    ShaderSource s2 {};
    s2.loadSourceFile("/home/tomnir/Documents/devel/hshbin/cg1projekt/tests/testShaderSource.glsl");
    char* s1text {s1.getSourceString()};
    char* s2text {s2.getSourceString()};
    const char* text =
    "#version 330 core\n"
    "void main() {\n"
    "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";
    bool s1ok = strcmp(s1text, text) != 0;
    bool s2ok = strcmp(s2text, text) != 0;
    if (s1ok && s2ok)
    {
        cout << "OK - ShaderSource liest Datei korrekt ein." << endl;
    } else
    {
        cout << "ShaderSource liest Datei nicht korrekt ein. Text:" << endl << s1text << endl << s2text;
    }
}

void shaderTests()
{
    cout << "Running tests for Shader related classes" << endl << endl;
    shaderSourceTest();
    cout << endl << "End of tests for Shader related classes" << endl;
}