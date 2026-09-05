//
// Created by tomnir on 05.09.26.
//
#include "../include/utilities.h"
#include "../include/types.h"
#include <cmath>
#include <thread>
using namespace std::chrono_literals;
int main()
{
    constexpr double pi = 3.14159265358979323846;
    constexpr int width {1920};
    constexpr int height {1080};
    auto window = GLContext::initializeContext(width, height);

    // shader erdkugel
    ShaderProgram earthshader {"beispiel/shaders/vertexShader.glsl",
        "beispiel/shaders/fragmentShader.glsl"};

    // texturen erdkugel
    TextureData earth_day {"beispiel/textures/earth_day.png"};
    earth_day.createTexture();
    TextureData earth_clouds {"beispiel/textures/earth_clouds.png"};
    earth_clouds.createTexture();

    // erdkugel object laden
    ObjectData earth_geometry {"beispiel/objects/earth.obj"};

    // material-object zusammenfassen
    Material earth_mat {
        earthshader.getID(),
        earth_day,
        earth_clouds,
        TextureData {},
        TextureData {},
        TextureData {}
    };

    // renderable erstellen
    Renderable earth_data {earth_geometry, earth_mat};
    // renderable in scene node einbauen
    SceneNode earth {earth_data};

    //
    // cube map
    //
    ShaderProgram skybox_shader {"beispiel/shaders/skyboxVertexShader.glsl",
        "beispiel/shaders/skyboxFragmentShader.glsl"};
    CubeMap skybox {
        skybox_shader,
        "beispiel/skybox/jettelly_space_nebulas_black_RIGHT.png",
        "beispiel/skybox/jettelly_space_nebulas_black_LEFT.png",
        "beispiel/skybox/jettelly_space_nebulas_black_UP.png",
        "beispiel/skybox/jettelly_space_nebulas_black_DOWN.png",
        "beispiel/skybox/jettelly_space_nebulas_black_FRONT.png",
        "beispiel/skybox/jettelly_space_nebulas_black_BACK.png"
    };
    skybox.createTexture();
    skybox.applyParameters();

    Mat4 transform {};

    Mat4 view {};

    Vec3 center{0.0, 0.0, 0.0};
    Vec3 up{0.0, 1.0, 0.0};


    Mat4 projection {};

    GLfloat fovy   = pi / 2.0f;
    GLfloat aspect = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
    GLfloat near   = 0.1f;
    GLfloat far    = 10.0f;

    projection.perspective(fovy, aspect, near, far);

    PointLight light {Vec3{1.5f, 1.5f, 2.0f}, Vec3{1.0f, 1.0f, 0.0f}, 1.0, 0.022, 0.0019};
    LightSources lights;
    lights.addLight(light);

    GLfloat radius = 3.0f;
    GLfloat angle = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        angle += 0.005;
        Vec3 eye {radius * (GLfloat)sin(angle), 0.3f, radius*(GLfloat)cos(angle)};
        view.lookAt(eye, center, up);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        earth.draw(transform, view, projection, 0, lights);
        skybox.draw(projection, view);
        glfwPollEvents();
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(16ms);
    }

}