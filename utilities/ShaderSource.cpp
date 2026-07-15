//
// Created by tomnir on 11.07.26.
//

/*
 * THIS HAS NOT BEEN TESTED YET
 */

#include "ShaderSource.h"
#include <cassert>
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
    delete[](buffer);
}

void ShaderSource::loadSourceFile(const string& path)
{
    sourcePath = sourcePath;
    buffer = readSourceFile(path);
}

char* ShaderSource::readSourceFile(const string& path)
{
    assert(!path.empty());

    ifstream fs {path, ifstream::in};
    if (!fs.is_open()) throw runtime_error("Error opening shader file: " + path);

    fs.seekg(0,ifstream::end);
    const auto length {fs.tellg()};
    if (length == streampos(-1)) throw runtime_error("Error determining shader file size: " + path);
    fs.seekg(0,ifstream::beg);

    const auto buf = static_cast<char*>(malloc(sizeof(char)*length));
    if(!fs.read(buf, length)) throw runtime_error("Error reading shader source code from: " + path);
    fs.close();
    return buf;
}

char* ShaderSource::getSourceString() const
{
    printf("%s\n\n", buffer);
    return buffer;
}
