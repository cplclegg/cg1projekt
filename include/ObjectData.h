//
// Created by tomnir on 03.08.26.
//

/**
 * Loads and stores vertex positions, normals, texture coordinates, and object face data from a .obj file.
 * This is just a simple demonstration. Wavefront OBJ is not fully supported!
 * Use with triangulated meshes, only!
 * Provides methods that access the data buffer or outright create a VBO from the data.
 */

#ifndef CG1PROJEKT_OBJECTDATA_H
#define CG1PROJEKT_OBJECTDATA_H
#include <filesystem>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
typedef GLfloat Vector2[2];
typedef GLfloat Vector3[3];

typedef struct Vertex {
    Vector3 v;
    Vector2 vt;
    Vector3 vn;
} Vertex;

typedef Vertex Triangle[3];

class ObjectData
{
private:
    size_t m_vertexCount = 0;
    size_t m_vCount = 0;
    size_t m_vtCount = 0;
    size_t m_vnCount = 0;
    size_t m_fCount = 0;
    size_t m_lineLength = 1024;
    size_t m_bufferSize = 0;
    GLfloat* m_buffer = nullptr;
    GLfloat* loadObj(const char* location);
public:
    ObjectData();
    explicit ObjectData(const std::string& relativePath);
    ObjectData(const ObjectData& other);
    ~ObjectData();

    void importObjectData(const std::filesystem::path& path);

    void printBuffer() const;

    size_t getVertexCount() const;
    GLfloat* getBuffer() const;
    GLuint makeVBO() const;
};

#endif //CG1PROJEKT_OBJECTDATA_H