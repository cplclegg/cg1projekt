#include "../../include/ObjectData.h"
#include "../../include/ShaderSource.h"
#include "../../include/ShaderProgram.h"
#include "../../include/Mat4.h"
#include "../../include/TextureData.h"


#define PI 3.14159265358979323846


/*Struct notwendig um sowohl Programm-ID, Texture-ID, Vertex-Anzahl als auch VAO
  aus der Init Funktion in die Draw Funktion hineinzubringen
*/
struct RenderData {
    GLuint programmID;
    GLuint textureID;
    size_t vertexCount;
    GLuint vao;
};

RenderData init(void) {
    ShaderProgram shader{"src/shaders/shaderTests/testTexture/VertexShader.glsl", "src/shaders/shaderTests/testTexture/FragmentShader.glsl"};
    ObjectData testObject{"tests/cubefinish2.obj"};
    GLuint vbo = testObject.makeVBO();
    TextureData textureObject{"tests/crate.png", GL_TEXTURE_2D};
    GLuint texture = textureObject.createTexture();
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
        (void*)0         //Offset in Bytes
    );
    glEnableVertexAttribArray(0);

    //jetzt die Texture
    glVertexAttribPointer(
        1,        
        2,        
        GL_FLOAT, 
        GL_FALSE, 
        8 * sizeof(GLfloat),        
        (void*) (3 * sizeof(GLfloat))         
    );
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Initiale Hintergrundfarbe der Szene
    glViewport(0, 0, 800, 600);

    RenderData data{
      shader.getID(),
      texture,
      testObject.getVertexCount(),
      vao
    };

    return data;
}

void draw(RenderData& data) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glUseProgram(data.programmID);
    glBindVertexArray(data.vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, data.textureID);

    //Transformation berechnen
    Mat4 modelM{};
    modelM.translate(Vec3{-53.42f, -53.62f, 0.0f});
    modelM.rotateY(10.0f);
    modelM.rotateX(10.0f);

    Mat4 ViewM{};
    Vec3 eye{0.0f, 0.0f, 20.0f};
    Vec3 center{0.0f, 0.0f, 0.0f};
    Vec3 up{0.0f, 1.0f, 0.0f};
    ViewM.lookAt(eye, center, up);

    Mat4 projM{};
    projM.perspective(45.0f * (PI / 180.f), 800.0f/600.0f, 0.1f, 100.0f);


    //Matrix an Shader schicken
    GLuint modelLoc = glGetUniformLocation(data.programmID, "modelM");
    GLuint viewLoc = glGetUniformLocation(data.programmID, "viewM");
    GLuint projMLoc = glGetUniformLocation(data.programmID, "projM");
    GLuint textLoc = glGetUniformLocation(data.programmID, "boxTexture");
    glUniformMatrix4fv(modelLoc, 1, GL_TRUE, modelM.getMatrix());
    glUniformMatrix4fv(viewLoc, 1, GL_TRUE, ViewM.getMatrix());
    glUniformMatrix4fv(projMLoc, 1, GL_TRUE, projM.getMatrix());
    glUniform1i(textLoc, 0);
    

    glDrawArrays(GL_TRIANGLES, 0, data.vertexCount);
    glBindVertexArray(0);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
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