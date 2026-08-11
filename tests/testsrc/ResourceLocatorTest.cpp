//
// Created by tomnir on 10.08.26.
//
#include "../../include/ResourceLocator.h"
#include <iostream>
#include <string>
using namespace std;
int resourceLocatorTest()
{
    cout << "Running tests for ResourceLocator" << endl;
    string path {"tests/testShaderSource.glsl"};
    string absPath {ResourceLocator::getResourcePath(path)};
    string sourcePath {PROJECT_SOURCE_ROOT};
    string referencePath {sourcePath+"/"+path};
    if (absPath == referencePath)
    {
        cout << "OK - Completion of absolute resource path successful." << endl;
        cout << "End of tests for resource locator" << endl;
        return 0;
    } else
    {
        cout << "Completion of absolute resource path failed. Expected: " << referencePath << endl;
        cout << "Actual result: " << absPath << endl;
        cout << "End of tests for resource locator" << endl;
        return 1;
    }
}