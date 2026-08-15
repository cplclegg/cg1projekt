//
// Created by tomnir on 11.07.26.
//

/*
 * THIS HAS NOT BEEN TESTED YET
 */

#include "../../include/ShaderSource.h"
#include "../../include/ResourceLocator.h"
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
    , buffer {readSourceFile(sourcePath)}
    , loadSuccess{true}
{
}

ShaderSource::ShaderSource(const ShaderSource& other)
    : sourcePath {other.sourcePath}
    , buffer {readSourceFile(sourcePath)}
    , loadSuccess{true}
{
}

ShaderSource::~ShaderSource()
{
    if (buffer) {
        free(buffer);
        buffer = nullptr;
    }
}

void ShaderSource::loadSourceFile(const string& path)
{
    sourcePath = sourcePath;
    buffer = readSourceFile(path);
    loadSuccess = true;
}

char* ShaderSource::readSourceFile(const std::filesystem::path& relativePath)
{
    std::filesystem::path path {ResourceLocator::getResourcePath(relativePath)};
    ifstream fs {path, ifstream::in};
    if (!fs.is_open()) throw runtime_error("Error opening shader file: " + path.string());

    fs.seekg(0,ifstream::end);
    const auto length {fs.tellg()};
    if (length == streampos(-1)) throw runtime_error("Error determining shader file size: " + path.string());
    fs.seekg(0,ifstream::beg);

    const auto buf = static_cast<char*>(malloc(sizeof(char)*length + 1));
    if(!fs.read(buf, length)) throw runtime_error("Error reading shader source code from: " + path.string());

    buf[length] = '\0';
    fs.close();
    return buf;
}

char* ShaderSource::getSourceString() const
{
    return buffer;
}

bool ShaderSource::isValid() const
{
    return loadSuccess;
}
