//
// Created by tomnir on 11.07.26.
//

/*
 * THIS HAS NOT BEEN TESTED YET
 */

#include "../../include/ShaderSource.h"
#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;
ShaderSource::ShaderSource()
    : m_buffer {nullptr}
{
}

ShaderSource::ShaderSource(const string& path)
    : m_sourcePath{path}
    , m_buffer {readSourceFile(m_sourcePath)}
{
}

ShaderSource::ShaderSource(const ShaderSource& other)
    : m_sourcePath {other.m_sourcePath}
    , m_buffer {readSourceFile(m_sourcePath)}
{
}

ShaderSource::~ShaderSource()
{
    if (m_buffer) {
        free(m_buffer);
        m_buffer = nullptr;
    }
}

void ShaderSource::loadSourceFile(const string& path)
{
    m_sourcePath = m_sourcePath;
    m_buffer = readSourceFile(path);
}

char* ShaderSource::readSourceFile(const std::filesystem::path& relativePath)
{
    std::filesystem::path path {relativePath};
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
    m_loadSuccess = true;
    return buf;
}

char* ShaderSource::getSourceString() const
{
    return m_buffer;
}

bool ShaderSource::isValid() const
{
    return m_loadSuccess;
}
