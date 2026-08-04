//
// Created by tomnir on 03.08.26.
//
#include "../../include/ObjectData.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <stdexcept>

#include <bits/error_constants.h>
using namespace std;

ObjectData::ObjectData()
{
}

ObjectData::ObjectData(const ObjectData& other)
    : m_vertexCount {other.m_vertexCount}
    , m_vCount {other.m_vCount}
    , m_vtCount {other.m_vtCount}
    , m_vnCount {other.m_vnCount}
    , m_fCount {other.m_fCount}
    , m_lineLength {other.m_lineLength}
    , m_buffer {other.m_buffer}
{
}

ObjectData::ObjectData(const std::string& path)
    : m_buffer {loadObj(path.c_str())}
{
}

ObjectData::~ObjectData() // do NOT delete or free m_buffer, its heap allocated
{
}

GLfloat* ObjectData::getBuffer() const
{
    return m_buffer;
}

void ObjectData::makeVBO(GLuint& vbo) const
{
    assert(m_buffer != nullptr);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, m_bufferSize, m_buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLfloat* ObjectData::loadObj(const char* location)
{
    FILE* file = fopen(location, "r");
    if (file == nullptr) throw errc::no_such_file_or_directory;

    ssize_t read = 0;

    // line buffer for getline
    char* line = static_cast<char*>(malloc(m_lineLength));

    // count number of lines
    m_vCount = 0;
    m_vtCount = 0;
    m_vnCount = 0;
    m_fCount = 0;
    while ((read = getline(&line, &m_lineLength, file)) != -1) {
        if (strncmp(line, "v ", 2) == 0) ++m_vCount;
        else if (strncmp(line, "vt ", 3) == 0) ++m_vtCount;
        else if (strncmp(line, "vn ", 3) == 0) ++m_vnCount;
        else if (strncmp(line, "f ", 2) == 0) ++m_fCount;
    }

    // allocate temporary buffers
    Vector3* v  = static_cast<Vector3*>(malloc(m_vCount * sizeof(Vector3)));
    Vector2* vt = static_cast<Vector2*>(malloc(m_vtCount * sizeof(Vector2)));
    Vector3* vn = static_cast<Vector3*>(malloc(m_vnCount * sizeof(Vector3)));

    // allocate output buffer
    m_bufferSize = m_fCount * sizeof(Triangle);
    Triangle* buffer = static_cast<Triangle*>(malloc(m_bufferSize));

    // reset counters
    m_vCount = 0;
    m_vtCount = 0;
    m_vnCount = 0;
    m_fCount = 0;

    // jump to start of file
    fseek(file, 0, SEEK_SET);

    // process each line
    while ((read = getline(&line, &m_lineLength, file)) != -1) {
        if (strncmp(line, "v ", 2) == 0) {
            sscanf(line, "v %f %f %f\n", &v[m_vCount][0], &v[m_vCount][1], &v[m_vCount][2]);
            ++m_vCount;
        }
        else if (strncmp(line, "vt ", 3) == 0) {
            sscanf(line, "vt %f %f\n", &vt[m_vtCount][0], &vt[m_vtCount][1]);
            ++m_vtCount;
        }
        else if (strncmp(line, "vn ", 3) == 0) {
            sscanf(line, "vn %f %f %f\n", &vn[m_vnCount][0], &vn[m_vnCount][1], &vn[m_vnCount][2]);
            ++m_vnCount;
        }
        else if (strncmp(line, "f ", 2) == 0) {
            size_t idx[3][3];
            sscanf(line,
              "f %lu/%lu/%lu %lu/%lu/%lu %lu/%lu/%lu",
              &idx[0][0], &idx[0][1], &idx[0][2],
              &idx[1][0], &idx[1][1], &idx[1][2],
              &idx[2][0], &idx[2][1], &idx[2][2]
            );

            // copy data from temporary buffers to output buffer
            for (size_t i = 0; i < 3; ++i) {
                memcpy(buffer[m_fCount][i].v, v[idx[i][0]-1], sizeof(Vector3));
                memcpy(buffer[m_fCount][i].vt, vt[idx[i][1]-1], sizeof(Vector2));
                memcpy(buffer[m_fCount][i].vn, vn[idx[i][2]-1], sizeof(Vector3));
            }
            ++m_fCount;
        }
    }

    // free temporary buffers
    free(line);
    free(v);
    free(vt);
    free(vn);

    m_vertexCount = 3 * m_fCount;
    return reinterpret_cast<GLfloat*>(buffer);
}