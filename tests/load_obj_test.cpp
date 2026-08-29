#include "../../include/ObjectData.h"
#include "../../include/ShaderSource.h"
#include "../../include/ShaderProgram.h"
#include "../../include/Mat4.h"


/*Struct notwendig um sowohl Programm-ID, Vertex-Anzahl als auch VAO
  aus der Init Funktion in die Draw Funktion hineinzubringen
*/
struct RenderData {
    GLuint programmID;
    size_t vertexCount;
    GLuint vao;
};

RenderData init(void) {
    ShaderProgram shader{"src/shaders/testshaders/VertexShader.glsl", "src/shaders/testshaders/FragmentShader.glsl"};
    ObjectData testObject{"tests/teapot.obj"};
    GLuint vbo = testObject.makeVBO();
    GLuint vao;


    //VAO erzeugen und Attribpointer setzen
    //Zuerst für die Position
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
        0,        //Location
        3,        //Dimensionen
        GL_FLOAT, //Typ der Daten
        GL_FALSE, //Normalisieren
        8 * sizeof(GLfloat),        //Abstand in Bytes zwischen zwei Vertices
        0         //Offset in Bytes
    );
    glEnableVertexAttribArray(0);

    //Jetzt für die Normalen
    glVertexAttribPointer(
        1,        
        3,        
        GL_FLOAT, 
        GL_FALSE, 
        8 * sizeof(GLfloat),        
        (GLvoid*) (5 * sizeof(GLfloat))         
    );
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Initiale Hintergrundfarbe der Szene
    glViewport(0, 0, 800, 600);

    RenderData data{
      shader.getID(),
      testObject.getVertexCount(),
      vao
    };

    return data;
}

void draw(RenderData& data) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(data.programmID);
    glBindVertexArray(data.vao);

    //Transformation berechnen

    Vec3 scaleVector{0.2f, 0.2f, 0.2f};
    Mat4 scaleMatrix{};
    scaleMatrix.scale(scaleVector);

    Mat4 rotateMatrix{};
    rotateMatrix.rotateY(45.0f);
    rotateMatrix.rotateX(70.0f);

    Mat4 transformM = rotateMatrix * scaleMatrix;

    //Matrix an Shader schicken
    GLint transformLoc = glGetUniformLocation(data.programmID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transformM.getMatrix());


    glDrawArrays(GL_TRIANGLES, 0, data.vertexCount);
}

void framebuffer_size_callback([[maybe_unused]]GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height); 
}

int main(void) {
    
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Computergrafik 1", NULL, NULL);

    if(!window) {
        printf("Failed to crate window\n");
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window); 
    glewInit();

    RenderData data = init();

    while(!glfwWindowShouldClose(window)) {
        draw(data);
        glfwSwapBuffers(window); 
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}