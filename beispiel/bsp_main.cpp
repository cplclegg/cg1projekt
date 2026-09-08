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
    //shader tisch
    ShaderProgram tableshader {"beispiel/shaders/vertexShader.glsl",
    "beispiel/shaders/fragmentShader.glsl"};
    // shader kerze
    ShaderProgram candleshader {"beispiel/shaders/vertexShader.glsl",
"beispiel/shaders/fragmentShader.glsl"};
    // shader flamme
    ShaderProgram flameshader {"beispiel/shaders/vertexShader.glsl",
"beispiel/shaders/fragmentShader.glsl"};
    // texturen erdkugel
    TextureData earth_day {"beispiel/textures//table/TabMat_baseColor.jpeg"};
    earth_day.createTexture();
    TextureData earth_clouds {"beispiel/textures/table/TabMat_specularf0.png"};
    earth_clouds.createTexture();

    // erdkugel object laden
    ObjectData earth_geometry {"beispiel/objects/altar/altar_table.obj"};
    ObjectData candle1_geometry {"beispiel/objects/candle/candle1.obj"};
    ObjectData candle_flame_geometry {"beispiel/objects/candle/candle_flame.obj"};

    //
    TextureData empty {};
    TextureData c1_base {"beispiel/textures/candles/Candle_1_baseColor.png"};
    c1_base.createTexture();
    TextureData c1_normal {"beispiel/textures/candles/Candle_1_normal.png"};
    c1_normal.createTexture();
    TextureData cf_base {"beispiel/textures/candles/Flame_baseColor.png"};
    cf_base.createTexture();
    TextureData cf_emissive {"beispiel/textures/candles/Flame_baseColor.png"};
    cf_emissive.createTexture();

    Material candle_fmat {
        flameshader.getID(),
        cf_base,
        empty,
        empty,
        empty,
        cf_emissive
    };

    Material candle1mat {
        candleshader.getID(),
        c1_base,
        empty,
        c1_normal,
        empty,
        empty
    };
    // material-object zusammenfassen
    Material earth_mat {
        earthshader.getID(),
        earth_day,
        TextureData {},
        TextureData {},
        earth_clouds,
        TextureData {}
    };

    Renderable candle1_data {
        candle1_geometry,
        candle1mat
    };

    Renderable candle_fdata {
        candle_flame_geometry,
        candle_fmat
    };



    SceneNode candle1_1 {candle1_data};
    SceneNode candle1_1_f {candle_fdata};
    candle1_1.translate(Vec3{1.0993350744247437, 0.23523379862308502, -1.183178186416626});
    candle1_1_f.translate(Vec3{0.0, 0.225, 0.0});
    candle1_1.addChild(candle1_1_f);
    SceneNode candle1_2_f {candle_fdata};

    SceneNode candle1_2 {candle1_data};
    candle1_2.translate(Vec3{-0.3676091432571411, 0.23523379862308502, -1.183178186416626});
    Material table_mat {
        earthshader.getID(),
        earth_day,
        TextureData {},
        TextureData {},
        earth_clouds,
        TextureData {}
    };

    // renderable erstellen
    Renderable earth_data {earth_geometry, earth_mat};
    // renderable in scene node einbauen
    SceneNode earth {earth_data};
    earth.addChild(candle1_1);
    earth.addChild(candle1_2);
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
        //candle1_1.draw(transform, view, projection, 0, lights);
        skybox.draw(projection, view);
        glfwPollEvents();
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(16ms);
    }

}