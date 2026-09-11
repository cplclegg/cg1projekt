//
// Created by tomnir on 05.09.26.
//
#include "../include/utilities.h"
#include "../include/types.h"
#include <cmath>
#include <thread>
using namespace std::chrono_literals;

bool isMagicActive = false;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Reagiere nur auf den Moment des Herunterdrückens = GLFW_PRESS
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        isMagicActive = !isMagicActive;
    }
}

int main()
{
    constexpr double pi = 3.14159265358979323846;
    constexpr int width {1920};
    constexpr int height {1080};
    auto window = GLContext::initializeContext(width, height);
    glfwSetKeyCallback(window,keyCallback);
    LightSources lights;
    // allgemeiner shader
    ShaderProgram generic_shader {"beispiel/shaders/vertexShader.glsl",
        "beispiel/shaders/fragmentShader.glsl"};
    // placeholder for unused texture on Material construction
    TextureData empty {};


    //
    // altar renderable setup
    //
    ObjectData altar_geometry {"beispiel/objects/altar/altar_table.obj"};
    TextureData altar_base {"beispiel/textures//table/TabMat_baseColor.jpeg"};
    altar_base.createTexture();
    TextureData altar_spec {"beispiel/textures/table/TabMat_specularf0.png"};
    altar_spec.createTexture();

    // material-object zusammenfassen
    Material altar_mat {
        generic_shader.getID(),
        altar_base,
        TextureData {},
        TextureData {},
        altar_spec,
        TextureData {}
    };

    // renderable erstellen
    Renderable altar_data {altar_geometry, altar_mat};
    // renderable in scene node einbauen
    auto altar = std::make_shared<SceneNode>(altar_data);

    //
    // candle flame renderable setup
    //
    ObjectData candle_flame_geometry {"beispiel/objects/candle/candle_flame.obj"};
    TextureData cf_base {"beispiel/textures/candles/Flame_baseColor.png"};
    cf_base.createTexture();
    TextureData cf_emissive {"beispiel/textures/candles/Flame_baseColor.png"};
    cf_emissive.createTexture();
    Material candle_fmat {
        generic_shader.getID(),
        cf_base,
        empty,
        empty,
        empty,
        cf_emissive
    };
    Renderable candle_fdata {
        candle_flame_geometry,
        candle_fmat
    };

    //
    // candles renderable setup (3 candles)
    //
    // candle 1 renderable setup
    ObjectData candle1_geometry {"beispiel/objects/candle/candle1.obj"};
    TextureData c1_base {"beispiel/textures/candles/Candle_1_baseColor.png"};
    c1_base.createTexture();
    TextureData c1_normal {"beispiel/textures/candles/Candle_1_normal.png"};
    c1_normal.createTexture();
    TextureData c1_specular{"beispiel/textures/candles/Candle_1_specular.jpg"};
    c1_specular.createTexture();
    Material candle1mat {
        generic_shader.getID(),
        c1_base,
        empty,
        c1_normal,
        c1_specular,
        empty
    };

    Renderable candle1_data {
        candle1_geometry,
        candle1mat
    };



    // candle 2 renderable setup
    ObjectData candle2_geometry {"beispiel/objects/candle/candle2.obj"};
    TextureData c2_base {"beispiel/textures/candles/Candle_2_baseColor.png"};
    c2_base.createTexture();
    TextureData c2_normal {"beispiel/textures/candles/Candle_2_normal.png"};
    c2_normal.createTexture();
    Material candle2mat {
        generic_shader.getID(),
        c2_base,
        empty,
        c2_normal,
        empty,
        empty
    };
    Renderable candle2_data {
        candle2_geometry,
        candle2mat
    };

    // candle 3 renderable setup
    ObjectData candle3_geometry {"beispiel/objects/candle/candle3.obj"};
    TextureData c3_base {"beispiel/textures/candles/Candle_3_baseColor.png"};
    c3_base.createTexture();
    TextureData c3_normal {"beispiel/textures/candles/Candle_3_normal.png"};
    c3_normal.createTexture();
    Material candle3mat {
        generic_shader.getID(),
        c3_base,
        empty,
        c3_normal,
        empty,
        empty
    };
    Renderable candle3_data {
        candle3_geometry,
        candle3mat
    };


    // light stand in
    //SceneNode light_standins {};
    //ObjectData globe {"uebungsblaetter/uebung7/earth.obj"};
    //ShaderProgram globe_shader {"beispiel/shaders/sphereVS.glsl", "beispiel/shaders/sphereFS.glsl"};
    //Material globe_mat {globe_shader.getID(), empty, empty, empty, empty, empty};
    //Renderable globe_data {globe, globe_mat};
    // candle clusters scene insertions
    auto candleCluster1 = SceneHelpers::makeCandleCluster(Vec3{1.0993350744247437, 0.0, -1.183178186416626}, candle1_data, candle2_data, candle3_data, candle_fdata);
    auto candle1_1_light = std::make_shared<PointLight>  (
        Vec3{1.0993350744247437, 0.23523379862308502+0.225, -1.183178186416626},
        Vec3{(245.0/255.0), (241.0/255.0), (217.0/255.0)},
        1.0, 0.6, 1.8
    );
    lights.addLight(candle1_1_light);
    //SceneNode l1globe {globe_data};
    //l1globe.scale(Vec3{0.05, 0.05, 0.05});
    //l1globe.translate(Vec3{1.0993350744247437, 0.23523379862308502+0.225, -1.183178186416626});
    //light_standins.addChild(l1globe);

    auto candleCluster2 = SceneHelpers::makeCandleCluster(Vec3 {-0.3676091432571411, 0.0, -1.183178186416626}, candle1_data, candle2_data, candle3_data, candle_fdata);
    auto candle1_2_light = std::make_shared<PointLight> (
        Vec3{-0.3676091432571411, 0.23523379862308502+0.225, -1.183178186416626},
        Vec3{(245.0/255.0), (241.0/255.0), (217.0/255.0)},
        1.0, 0.6, 1.8)
    ;
    lights.addLight(candle1_2_light);
    //SceneNode l2globe {globe_data};
    //l2globe.scale(Vec3{0.05, 0.05, 0.05});
    //l2globe.translate(Vec3{-0.3676091432571411, 0.23523379862308502+0.225, -1.183178186416626});
    //light_standins.addChild(l2globe);

    auto candleCluster3 = SceneHelpers::makeCandleCluster(Vec3{2.901495933532715, 0.0, 0.12495501339435577}, candle1_data, candle2_data, candle3_data, candle_fdata);
    auto candle1_3_light = std::make_shared<PointLight> (
        Vec3{2.901495933532715, 0.23523379862308502+0.225, 0.12495501339435577},
        Vec3{(245.0/255.0), (241.0/255.0), (217.0/255.0)},
        1.0, 0.6, 1.8)
    ;
    lights.addLight(candle1_3_light);
    //SceneNode l3globe {globe_data};
    //l3globe.scale(Vec3{0.05, 0.05, 0.05});
    //l3globe.translate(Vec3{2.901495933532715, 0.23523379862308502+0.225, 0.12495501339435577});
    //light_standins.addChild(l3globe);

    auto candleCluster4 = SceneHelpers::makeCandleCluster(Vec3{2.238408088684082, 0.0, 1.1504048109054565}, candle1_data, candle2_data, candle3_data, candle_fdata);
    auto candle1_4_light = std::make_shared<PointLight> (
        Vec3{2.238408088684082, 0.23523379862308502+0.225, 1.1504048109054565},
        Vec3{(245.0/255.0), (241.0/255.0), (217.0/255.0)},
        1.0, 0.6, 1.8);
    lights.addLight(candle1_4_light);

    auto candleCluster5 = SceneHelpers::makeCandleCluster(Vec3{0.3059954047203064, 0.0, 1.466347336769104}, candle1_data, candle2_data, candle3_data, candle_fdata);
    auto candle1_5_light = std::make_shared<PointLight> (
        Vec3{0.3059954047203064, 0.23523379862308502+0.225, 1.466347336769104},
        Vec3{(245.0/255.0), (241.0/255.0), (217.0/255.0)},
        1.0, 0.6, 1.8);
    lights.addLight(candle1_5_light);

    auto candleCluster6 = SceneHelpers::makeCandleCluster(Vec3{-0.4757641851902008, 0.0, 1.3738290071487427}, candle1_data, candle2_data, candle3_data, candle_fdata);
    auto candle1_6_light = std::make_shared<PointLight> (
        Vec3{-0.4757641851902008, 0.23523379862308502+0.225, 1.3738290071487427},
        Vec3{(245.0/255.0), (241.0/255.0), (217.0/255.0)},
        1.0, 0.6, 1.8);
    lights.addLight(candle1_6_light);

    auto candleCluster7 = SceneHelpers::makeCandleCluster(Vec3{-2.4770402908325195, 0.0, 0.01380294468253851}, candle1_data, candle2_data, candle3_data, candle_fdata);
    auto candle1_7_light = std::make_shared<PointLight>  (
        Vec3{-2.4770402908325195, 0.23523379862308502+0.225, 0.01380294468253851},
        Vec3{(245.0/255.0), (241.0/255.0), (217.0/255.0)},
        1.0, 0.6, 1.8);
    lights.addLight(candle1_7_light);

    altar->addChild(candleCluster1);
    altar->addChild(candleCluster2);
    altar->addChild(candleCluster3);
    altar->addChild(candleCluster4);
    altar->addChild(candleCluster5);
    altar->addChild(candleCluster6);
    altar->addChild(candleCluster7);
    //earth.addChild(light_standins);

    //
    // crystal setup
    //
    ShaderProgram crystal_shader {"beispiel/shaders/vertexShader.glsl", "beispiel/shaders/crystalFS.glsl"};
    ObjectData crystal_geometry {"beispiel/objects/crystal/crystal.obj"};
    TextureData crystal_base {"beispiel/textures/crystal/crystal_17_2_baseColor.png"};
    crystal_base.createTexture();
    Material crystal_mat {
        crystal_shader.getID(),
        crystal_base,
        empty,
        empty,
        empty,
        empty
    };
    auto crystal = std::make_shared<SceneNode>(crystal_geometry, crystal_mat);
    crystal->scale(Vec3{0.3,0.3,0.3});
    crystal->translate(Vec3{0.0, 1.35, 0.0});
    //altar->addChild(crystal);
    auto crystal_glow = std::make_shared<PointLight> (
        Vec3{0.0,1.35,0.0},
        Vec3{63.0/255.0, 34.0/255.0,238.0/255.0},
        1.0, 0.6, 1.8);
    lights.addLight(crystal_glow);
    //
    // cave renderable setup
    //
    ShaderProgram cave_shader {"beispiel/shaders/vertexShader.glsl", "beispiel/shaders/caveFS.glsl"};
    ObjectData cave_geometry {"beispiel/objects/cave/cave_v3_SCULPTED.obj"};
    TextureData cave_base {"beispiel/textures/cave/rock_texture.jpg"};
    cave_base.createTexture();
    TextureData cave_veins{"beispiel/textures/cave/ore_veins_purple.jpg"};
    cave_veins.createTexture();
    TextureData cave_oremask {"beispiel/textures/cave/cave_oremask.jpg"};
    cave_oremask.createTexture();

    Material cave_mat {
        cave_shader.getID(),
        cave_base,
        cave_veins,
        empty,
        empty,
        cave_oremask
    };
    SceneNode cave {cave_geometry, cave_mat};
    cave.addChild(altar);

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
    GLfloat far    = 20.0f;

    projection.perspective(fovy, aspect, near, far);

    PointLight light {Vec3{1.5f, 1.5f, 2.0f}, Vec3{1.0f, 1.0f, 0.0f}, 1.0, 0.022, 0.0019};

    //lights.addLight(light);

    GLfloat radius = 3.0f;
    GLfloat angle = 0.0f;
    GLfloat crystal_offset = 0.0f;
    GLfloat movement_speed = 1.0f;
    GLuint skyboxTexID {skybox.getTextureID()};
    glEnable(GL_DEPTH_TEST);
    glUseProgram(cave_shader.getID());
    GLint alphaLocation = glGetUniformLocation(crystal_shader.getID(), "alpha");
    glUseProgram(0);
    bool interactionKeyPressed {false};
    while (!glfwWindowShouldClose(window))
    {
        angle += 0.005;
        crystal_offset += 0.005;
        Vec3 crystal_animation {0.0, GLfloat(0.001*sin(crystal_offset)), 0.0};
        crystal->translate(crystal_animation);
        Vec3 eye {radius * (GLfloat)sin(angle), 1.7f, radius*(GLfloat)cos(angle)};
        view.lookAt(eye, center, up);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cave.draw(transform, view, projection, 0, lights, glfwGetTime());
        GLfloat alpha {0.1f};
        Vec3 targetColor{Vec3{245.0f / 255.0f, 241.0f / 255.0f, 217.0f / 255.0f}};
        if (isMagicActive)
        {
            targetColor(0) = 1.0f;
            targetColor(1) = 0.0f;
            targetColor(2) = 0.0f;
            alpha = 1.0f;
        }
        glUseProgram(crystal_shader.getID());
        glUniform1f(alphaLocation, alpha);
        glUseProgram(0);
        candle1_1_light->setColor(targetColor);
        candle1_2_light->setColor(targetColor);
        candle1_3_light->setColor(targetColor);
        candle1_4_light->setColor(targetColor);
        candle1_5_light->setColor(targetColor);
        candle1_6_light->setColor(targetColor);
        candle1_7_light->setColor(targetColor);
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        crystal->draw(transform, view, projection, skyboxTexID, lights, glfwGetTime());
        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);
        skybox.draw(projection, view);
        glfwPollEvents();
        glfwSwapBuffers(window);
        std::this_thread::sleep_for(16ms);
    }

}