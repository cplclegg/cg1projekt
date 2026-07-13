//
// Created by tomnir on 11.07.26.
//

/*
 * THIS HAS NOT BEEN TESTED YET
 */

#include "ShaderSource.h"
#include <fstream>
#include <iostream>
using namespace std;
ShaderSource::ShaderSource()
    : buffer {nullptr}
{
}

ShaderSource::ShaderSource(const string& path)
    : sourcePath{path}
    , buffer {readSourceFile(path)}
{
}

ShaderSource::ShaderSource(const ShaderSource& other)
    : sourcePath {other.sourcePath}
    , buffer {readSourceFile(sourcePath)}
{
}

ShaderSource::~ShaderSource()
{
    delete(buffer);
}

void ShaderSource::loadSourceFile(const string& path)
{
    sourcePath = sourcePath;
    buffer = readSourceFile(path);
}

char* ShaderSource::readSourceFile(const string& path)
{
    ifstream fs {path, ifstream::in};
    fs.seekg(0,ifstream::end);
    int length = fs.tellg();
    fs.seekg(0,ifstream::beg);
    printf("%d\n", length);
    char* buf = (char*)malloc(sizeof(char)*length);
    fs.read(buf, length);
    fs.close();
    return buf;
}

char* ShaderSource::getSourceString() const
{
    printf("%s\n\n", buffer);
    return buffer;
}
