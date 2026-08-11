//
// Created by tomnir on 09.07.26.
//
#include "../include/tests.h"

int main()
{
    int result = vec3Tests();
    result += vec4Tests();
    result += mat4Tests();
    result += shaderTests();
    result += mat3Tests();
    result += objImportTests();
    result +=  resourceLocatorTest();
    result +=  textureDataTest();
    return result;
}