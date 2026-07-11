//
// Created by tomnir on 11.07.26.
//

/*
 * THIS HAS NOT BEEN TESTED YET
 */

#include "ShaderSource.h"
#include <fstream>
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
    ifstream fs;
    fs.open(path);
    fs.seekg(0,ios::end);
    int length = fs.tellg();
    fs.seekg(0,ios::beg);
    char* buf = new char[length];
    fs.read(buf, length);
    fs.close();
    return buf;
}

const char* ShaderSource::getSourceString() const
{
    return buffer;
}
