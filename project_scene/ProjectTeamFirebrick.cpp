//
// Created by tomnir on 05.09.26.
//
#include "../include/utilities.h"
#include "../include/types.h"
#include <cmath>
#include <thread>
using namespace std::chrono_literals;

bool isMagicActive = false;

void keyCallback([[maybe_unused]] GLFWwindow* window, [[maybe_unused]] int key, [[maybe_unused]] int scancode,
                 int action, [[maybe_unused]] int mods)
{
    // Reagiere nur auf den Moment des Herunterdrückens = GLFW_PRESS
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        isMagicActive = !isMagicActive;
    }
}

Vec3 rotateAroundAxis(const Vec3& v, const Vec3& axis, GLfloat angle)
{
    Vec3 a{axis};
    a.normalize();

    return v * cos(angle)
        + a.crossProduct(v) * (GLfloat)sin(angle)
        + a * (a * v * (1.0f - (GLfloat)cos(angle)));
}

int main()
{
    constexpr double pi = 3.14159265358979323846;
    constexpr int width{1920};
    constexpr int height{1080};
    auto window = GLContext::initializeContext(width, height);
    glfwSetKeyCallback(window, keyCallback);
    LightSources lights;
    // allgemeiner shader
    ShaderProgram generic_shader{
        "project_scene/shaders/vertexShader.glsl",
        "project_scene/shaders/fragmentShader.glsl"
    };
    // placeholder for unused texture on Material construction
    TextureData empty{};


    //
    // altar renderable setup
    //
    ObjectData altar_geometry{"project_scene/objects/altar/altar_table.obj"};
    TextureData altar_base{"project_scene/textures//table/TabMat_baseColor.jpeg"};
    altar_base.createTexture();
    TextureData altar_spec{"project_scene/textures/table/TabMat_specularf0.png"};
    altar_spec.createTexture();

    // material-object zusammenfassen
    Material altar_mat{
        generic_shader.getID(),
        altar_base,
        TextureData{},
        TextureData{},
        altar_spec,
        TextureData{}
    };

    // renderable erstellen
    Renderable altar_data{altar_geometry, altar_mat};
    // renderable in scene node einbauen
    auto altar = std::make_shared<SceneNode>(altar_data);

    //
    // candle flame renderable setup
    //
    ObjectData candle_flame_geometry{"project_scene/objects/candle/candle_flame.obj"};
    TextureData cf_base{"project_scene/textures/candles/Flame_baseColor.png"};
    cf_base.createTexture();
    TextureData cf_emissive{"project_scene/textures/candles/Flame_baseColor.png"};
    cf_emissive.createTexture();
    Material candle_fmat{
        generic_shader.getID(),
        cf_base,
        empty,
        empty,
        empty,
        cf_emissive
    };
    Renderable candle_fdata{
        candle_flame_geometry,
        candle_fmat
    };

    //
    // candles renderable setup (3 candles)
    //
    ShaderProgram candle_shader{"project_scene/shaders/vertexShader.glsl", "project_scene/shaders/candleFS.glsl"};
    // candle 1 renderable setup
    ObjectData candle1_geometry{"project_scene/objects/candle/candle1.obj"};
    TextureData c1_base{"project_scene/textures/candles/Candle_1_baseColor.png"};
    c1_base.createTexture();
    TextureData c1_normal{"project_scene/textures/candles/Candle_1_normal.png"};
    c1_normal.createTexture();
    TextureData c1_specular{"project_scene/textures/candles/Candle_1_specular.jpg"};
    c1_specular.createTexture();
    Material candle1mat{
        candle_shader.getID(),
        c1_base,
        empty,
        c1_normal,
        c1_specular,
        empty
    };

    Renderable candle1_data{
        candle1_geometry,
        candle1mat
    };


    // candle 2 renderable setup
    ObjectData candle2_geometry{"project_scene/objects/candle/candle2.obj"};
    TextureData c2_base{"project_scene/textures/candles/Candle_2_baseColor.png"};
    c2_base.createTexture();
    TextureData c2_normal{"project_scene/textures/candles/Candle_2_normal.png"};
    c2_normal.createTexture();
    Material candle2mat{
        candle_shader.getID(),
        c2_base,
        empty,
        c2_normal,
        c1_specular,
        empty
    };
    Renderable candle2_data{
        candle2_geometry,
        candle2mat
    };

    // candle 3 renderable setup
    ObjectData candle3_geometry{"project_scene/objects/candle/candle3.obj"};
    TextureData c3_base{"project_scene/textures/candles/Candle_3_baseColor.png"};
    c3_base.createTexture();
    TextureData c3_normal{"project_scene/textures/candles/Candle_3_normal.png"};
    c3_normal.createTexture();
    Material candle3mat{
        candle_shader.getID(),
        c3_base,
        empty,
        c3_normal,
        c1_specular,
        empty
    };
    Renderable candle3_data{
        candle3_geometry,
        candle3mat
    };

    // offset vectors
    Vec3 c1offset{0.0, 0.23523379862308502f, 0.0};
    Vec3 cf1offset{0.0, 0.225, 0.0};
    Vec3 c2offset{-0.01172077655, 0.14632247388362885, -0.26494348049};
    Vec3 cf2offset{0.0, 0.125, 0.0};
    Vec3 c3offset{0.28967034816, 0.10961973667144775, -0.14722788333};
    Vec3 cf3offset{0.0, 0.072, 0.0};


    // candle clusters scene insertions
    auto candleCluster1 = SceneHelpers::makeCandleCluster(Vec3{1.0993350744247437, 0.0, -1.183178186416626},
                                                          candle1_data, candle2_data, candle3_data, candle_fdata);
    candleCluster1->translate(Vec3{0.0, 0.1, 0.0});
    auto candle1_1_light = std::make_shared<PointLight>(
        Vec3{1.0993350744247437, 0.23523379862308502 + 0.1, -1.183178186416626} + c1offset + cf1offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.6, 1.8
    );
    auto candle2_1_light = std::make_shared<PointLight>(
        Vec3{1.0993350744247437, 0.23523379862308502 + 0.1, -1.183178186416626} + c2offset + cf2offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.6, 1.8
    );
    auto candle3_1_light = std::make_shared<PointLight>(
        Vec3{1.0993350744247437, 0.23523379862308502 + 0.1, -1.183178186416626} + c3offset + cf3offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.6, 1.8
    );
    lights.addLight(candle1_1_light);
    lights.addLight(candle2_1_light);
    lights.addLight(candle3_1_light);

    auto candleCluster2 = SceneHelpers::makeCandleCluster(Vec3{-0.3676091432571411, 0.0, -1.183178186416626},
                                                          candle1_data, candle2_data, candle3_data, candle_fdata);
    candleCluster2->translate(Vec3{0.0, 0.08, 0.0});
    auto candle1_2_light = std::make_shared<PointLight>(
        Vec3{-0.3676091432571411, 0.08, -1.183178186416626}+c1offset + cf1offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.6, 1.8);
    auto candle2_2_light = std::make_shared<PointLight>(
        Vec3{-0.3676091432571411, 0.08, -1.183178186416626} + c2offset + cf2offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.6, 1.8
    );
    auto candle3_2_light = std::make_shared<PointLight>(
        Vec3{-0.3676091432571411, 0.08, -1.183178186416626} + c3offset + cf3offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.6, 1.8
    );
    lights.addLight(candle1_2_light);
    lights.addLight(candle2_2_light);
    lights.addLight(candle3_2_light);

    auto candleCluster3 = SceneHelpers::makeCandleCluster(Vec3{2.901495933532715, 0.0, 0.12495501339435577},
                                                          candle1_data, candle2_data, candle3_data, candle_fdata);
    candleCluster3->translate(Vec3{0.0, 0.06, 0.0});

    auto candle1_3_light = std::make_shared<PointLight>(
    Vec3{2.901495933532715, 0.06, 0.12495501339435577}+c1offset + cf1offset,
    Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
    1.5, 0.6, 1.8);
    auto candle2_3_light = std::make_shared<PointLight>(
        Vec3{2.901495933532715, 0.06, 0.12495501339435577} + c2offset + cf2offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.6, 1.8
    );
    auto candle3_3_light = std::make_shared<PointLight>(
        Vec3{2.901495933532715, 0.06, 0.12495501339435577} + c3offset + cf3offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.6, 1.8
    );
    lights.addLight(candle1_3_light);
    lights.addLight(candle2_3_light);
    lights.addLight(candle3_3_light);

    auto candleCluster4 = SceneHelpers::makeCandleCluster(Vec3{2.238408088684082, 0.0, 1.1504048109054565},
                                                          candle1_data, candle2_data, candle3_data, candle_fdata);
    auto candle1_4_light = std::make_shared<PointLight>(
    Vec3{2.238408088684082, 0.0, 1.1504048109054565}+c1offset + cf1offset,
    Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
    1.5, 0.6, 1.8);
    auto candle2_4_light = std::make_shared<PointLight>(
        Vec3{2.238408088684082, 0.0, 1.1504048109054565} + c2offset + cf2offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.6, 1.8
    );
    auto candle3_4_light = std::make_shared<PointLight>(
        Vec3{2.238408088684082, 0.0, 1.1504048109054565} + c3offset + cf3offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.6, 1.8
    );
    lights.addLight(candle1_4_light);
    lights.addLight(candle2_4_light);
    lights.addLight(candle3_4_light);

    auto candleCluster5 = SceneHelpers::makeCandleCluster(Vec3{0.3059954047203064, 0.0, 1.466347336769104},
                                                          candle1_data, candle2_data, candle3_data, candle_fdata);
    candleCluster5->translate(Vec3{0.0, 0.06, 0.0});
    auto candle1_5_light = std::make_shared<PointLight>(
        Vec3{0.3059954047203064, 0.06, 1.466347336769104}+c1offset + cf1offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        2.0, 0.6, 1.8);
    auto candle2_5_light = std::make_shared<PointLight>(
        Vec3{0.3059954047203064, 0.06, 1.466347336769104} + c2offset + cf2offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        2.0, 0.6, 1.8
    );
    auto candle3_5_light = std::make_shared<PointLight>(
        Vec3{0.3059954047203064, 0.06, 1.466347336769104} + c3offset + cf3offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        2.0, 0.6, 1.8
    );
    lights.addLight(candle1_5_light);
    lights.addLight(candle2_5_light);
    lights.addLight(candle3_5_light);


    auto candleCluster6 = SceneHelpers::makeCandleCluster(Vec3{-0.4757641851902008, 0.0, 1.3738290071487427},
                                                          candle1_data, candle2_data, candle3_data, candle_fdata);
    candleCluster6->translate(Vec3{0.0, 0.1, 0.0});
    auto candle1_6_light = std::make_shared<PointLight>(
        Vec3{-0.4757641851902008, 0.1, 1.3738290071487427}+c1offset + cf1offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        2.0, 0.4, 1.8);
    auto candle2_6_light = std::make_shared<PointLight>(
        Vec3{-0.4757641851902008, 0.1, 1.3738290071487427} + c2offset + cf2offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        2.0, 0.4, 1.8
    );
    auto candle3_6_light = std::make_shared<PointLight>(
        Vec3{-0.4757641851902008, 0.1, 1.3738290071487427} + c3offset + cf3offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        2.0, 0.4, 1.8
    );
    lights.addLight(candle1_6_light);
    lights.addLight(candle2_6_light);
    lights.addLight(candle3_6_light);

    auto candleCluster7 = SceneHelpers::makeCandleCluster(Vec3{-2.4770402908325195, 0.0, 0.01380294468253851},
                                                          candle1_data, candle2_data, candle3_data, candle_fdata);
    candleCluster7->translate(Vec3{0.0, 0.02, 0.0});
    auto candle1_7_light = std::make_shared<PointLight>(
        Vec3{-2.4770402908325195, 0.02, 0.01380294468253851}+c1offset + cf1offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.4, 1.8);
    auto candle2_7_light = std::make_shared<PointLight>(
        Vec3{-2.4770402908325195, 0.02, 0.01380294468253851} + c2offset + cf2offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.4, 1.8
    );
    auto candle3_7_light = std::make_shared<PointLight>(
        Vec3{-2.4770402908325195, 0.02, 0.01380294468253851} + c3offset + cf3offset,
        Vec3{(245.0 / 255.0), (241.0 / 255.0), (217.0 / 255.0)},
        1.5, 0.4, 1.8
    );
    lights.addLight(candle1_7_light);
    lights.addLight(candle2_7_light);
    lights.addLight(candle3_7_light);

    altar->addChild(candleCluster1);
    altar->addChild(candleCluster2);
    altar->addChild(candleCluster3);
    altar->addChild(candleCluster4);
    altar->addChild(candleCluster5);
    altar->addChild(candleCluster6);
    altar->addChild(candleCluster7);

    //
    // crystal setup
    //
    ShaderProgram crystal_shader{"project_scene/shaders/vertexShader.glsl", "project_scene/shaders/crystalFS.glsl"};
    ObjectData crystal_geometry{"project_scene/objects/crystal/crystal.obj"};
    TextureData crystal_base{"project_scene/textures/crystal/crystal_17_2_baseColor.png"};
    crystal_base.createTexture();
    Material crystal_mat{
        crystal_shader.getID(),
        crystal_base,
        empty,
        empty,
        empty,
        empty
    };
    auto crystal = std::make_shared<SceneNode>(crystal_geometry, crystal_mat);
    crystal->scale(Vec3{0.3, 0.3, 0.3});
    crystal->translate(Vec3{0.0, 1.35, 0.0});

    auto crystal_glow = std::make_shared<PointLight>(
        Vec3{0.0, 1.35, 0.0},
        Vec3{63.0 / 255.0, 34.0 / 255.0, 238.0 / 255.0},
        1.0, 0.6, 1.8);
    lights.addLight(crystal_glow);

    //
    // cave renderable setup
    //
    ShaderProgram cave_shader{"project_scene/shaders/vertexShader.glsl", "project_scene/shaders/caveFS.glsl"};
    ObjectData cave_geometry{"project_scene/objects/cave/cave_v3_SCULPTED.obj"};
    TextureData cave_base{"project_scene/textures/cave/rock_texture.jpg"};
    cave_base.createTexture();
    TextureData cave_veins{"project_scene/textures/cave/ore_veins_purple.jpg"};
    cave_veins.createTexture();
    TextureData cave_oremask{"project_scene/textures/cave/cave_oremask.jpg"};
    cave_oremask.createTexture();

    Material cave_mat{
        cave_shader.getID(),
        cave_base,
        cave_veins,
        empty,
        empty,
        cave_oremask
    };
    SceneNode cave{cave_geometry, cave_mat};
    cave.addChild(altar);

    //
    // cube map
    //
    ShaderProgram skybox_shader{
        "project_scene/shaders/skyboxVertexShader.glsl",
        "project_scene/shaders/skyboxFragmentShader.glsl"
    };
    CubeMap skybox{
        skybox_shader,
        "project_scene/textures/skybox/CubeMap_Sides_Mountains(1).png",
        "project_scene/textures/skybox/CubeMap_Sides_Mountains(1).png",
        "project_scene/textures/skybox/CG_Auge_Himmel_BlackHoleV2.png",
        "project_scene/textures/skybox/CubeMap_Ground_2.png",
        "project_scene/textures/skybox/CubeMap_Sides_Mountains(1).png",
        "project_scene/textures/skybox/CubeMap_Sides_Mountains(1).png"
    };
    skybox.createTexture();
    skybox.applyParameters();


    Mat4 transform{};

    Mat4 view{};
    Vec3 eye{-4.35794, 1.7, 21.8992};
    Vec3 center{0.0, 1.7, 0.0};
    Vec3 up{0.0, 1.0, 0.0};


    Mat4 projection{};

    GLfloat fovy = pi / 2.0f;
    GLfloat aspect = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
    GLfloat near = 0.1f;
    GLfloat far = 30.0f;

    projection.perspective(fovy, aspect, near, far);

    GLfloat crystal_offset = 0.0f;
    GLfloat movement_speed = 2.0f;
    GLfloat turn_speed = 1.5f;
    GLfloat time;
    GLfloat prevTime{0.0f};
    GLfloat deltaTime;

    Vec3 camForward = (center - eye);
    camForward.normalize();
    glEnable(GL_DEPTH_TEST);
    GLint alphaLocation = glGetUniformLocation(crystal_shader.getID(), "alpha");
    GLint crystalFogDensityLocation = glGetUniformLocation(crystal_shader.getID(), "fogDensity");
    GLint caveFogDensityLocation = glGetUniformLocation(cave_shader.getID(), "fogDensity");
    GLint genericFogDensityLocation = glGetUniformLocation(generic_shader.getID(), "fogDensity");
    constexpr GLfloat maxPitch = 1.55334f;
    GLfloat pitch{0};
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    //
    // reflection cubemap
    //
    constexpr GLint reflectionCubemapResolutionXY{1024};
    constexpr GLfloat reflectionRenderFOVY{pi / 2};
    constexpr GLint reflectionAspect{1};
    constexpr GLfloat reflectionNear = 0.1f;
    constexpr GLfloat reflectionFar = 30.0f;

    Vec3 reflectionEyeVector{0.0, 1.35, 0.0};
    std::vector reflectionViewVectors{
        Vec3{1.0, 0.0, 0.0},
        Vec3{-1.0, 0.0, 0.0},
        Vec3{0.0, -1.0, 0.0},
        Vec3{0.0, 1.0, 0.0},
        Vec3{0.0, 0.0, 1.0},
        Vec3{0.0, 0.0, -1.0},
    };
    std::vector reflectionUpVectors{
        Vec3{0.0, -1.0, 0.0},
        Vec3{0.0, -1.0, 0.0},
        Vec3{0.0, 0.0, -1.0},
        Vec3{0.0, 0.0, 1.0},
        Vec3{0.0, -1.0, 0.0},
        Vec3{0.0, -1.0, 0.0}
    };
    Mat4 reflectionRenderView{};
    Mat4 reflectionRenderProj{};
    reflectionRenderProj.perspective(reflectionRenderFOVY, reflectionAspect, reflectionNear, reflectionFar);

    Vec3 targetColorREFLECTION{};
    GLfloat fogDensityREFLECTION = 0.0001f;
    targetColorREFLECTION(0) = 157.0f / 255.0f;
    targetColorREFLECTION(1) = 0.0f;
    targetColorREFLECTION(2) = 1.0f;

    glUseProgram(generic_shader.getID());
    glUniform1f(genericFogDensityLocation, fogDensityREFLECTION);
    glUseProgram(cave_shader.getID());
    glUniform1f(caveFogDensityLocation, fogDensityREFLECTION);
    glUseProgram(0);
    candle1_1_light->setColor(targetColorREFLECTION);
    candle1_2_light->setColor(targetColorREFLECTION);
    candle1_3_light->setColor(targetColorREFLECTION);
    candle1_4_light->setColor(targetColorREFLECTION);
    candle1_5_light->setColor(targetColorREFLECTION);
    candle1_6_light->setColor(targetColorREFLECTION);
    candle1_7_light->setColor(targetColorREFLECTION);

    GLuint captureFBO, captureRBO;
    glGenFramebuffers(1, &captureFBO);
    glGenRenderbuffers(1, &captureRBO);

    GLuint reflectionCubemap;
    glGenTextures(1, &reflectionCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionCubemap);

    for (GLuint i = 0; i < 6; ++i)
    {
        GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
        glTexImage2D(
            face,
            0,
            GL_RGB,
            reflectionCubemapResolutionXY,
            reflectionCubemapResolutionXY,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    Mat4 reflectionUnityMatrix{};


    while (!glfwWindowShouldClose(window))
    {
        time = glfwGetTime();
        deltaTime = time - prevTime;
        prevTime = time;
        GLint keyStateW = glfwGetKey(window, GLFW_KEY_W);
        GLint keyStateA = glfwGetKey(window, GLFW_KEY_A);
        GLint keyStateS = glfwGetKey(window, GLFW_KEY_S);
        GLint keyStateD = glfwGetKey(window, GLFW_KEY_D);
        GLint keyStateSpace = glfwGetKey(window, GLFW_KEY_SPACE);
        GLint keyStateX = glfwGetKey(window, GLFW_KEY_X);
        GLint keyStateQ = glfwGetKey(window, GLFW_KEY_Q);
        GLint keyStateE = glfwGetKey(window, GLFW_KEY_E);
        GLint keyStateZ = glfwGetKey(window, GLFW_KEY_Z);
        GLint keyStateC = glfwGetKey(window, GLFW_KEY_C);
        Vec3 cameraRight = camForward.crossProduct(up);
        cameraRight.normalize();
        if (keyStateW == GLFW_PRESS)
        {
            eye = eye + camForward * movement_speed * deltaTime;
        }
        if (keyStateS == GLFW_PRESS)
        {
            eye = eye - camForward * movement_speed * deltaTime;
        }
        if (keyStateSpace == GLFW_PRESS)
        {
            eye = eye + (up * movement_speed * deltaTime);
        }
        if (keyStateX == GLFW_PRESS)
        {
            eye = eye - (up * movement_speed * deltaTime);
        }
        if (keyStateA == GLFW_PRESS)
        {
            GLfloat turnDistance = turn_speed * deltaTime;
            GLfloat oldX = camForward(0);
            GLfloat oldZ = camForward(2);

            camForward = Vec3{
                oldX * (GLfloat)cos(turnDistance) + oldZ * (GLfloat)sin(turnDistance),
                camForward(1),
                -oldX * (GLfloat)sin(turnDistance) + oldZ * (GLfloat)cos(turnDistance)
            };
            camForward.normalize();
        }
        if (keyStateD == GLFW_PRESS)
        {
            GLfloat turnDistance = -turn_speed * deltaTime;
            GLfloat oldX = camForward(0);
            GLfloat oldZ = camForward(2);

            camForward = Vec3{
                oldX * (GLfloat)cos(turnDistance) + oldZ * (GLfloat)sin(turnDistance),
                camForward(1),
                -oldX * (GLfloat)sin(turnDistance) + oldZ * (GLfloat)cos(turnDistance)
            };
            camForward.normalize();
        }
        if (keyStateC == GLFW_PRESS)
        {
            GLfloat pitchAmount = turn_speed * deltaTime;
            if (pitch + pitchAmount < maxPitch)
            {
                camForward = rotateAroundAxis(camForward, cameraRight, pitchAmount);
                pitch += pitchAmount;
            }
            camForward.normalize();
        }
        if (keyStateZ == GLFW_PRESS)
        {
            GLfloat pitchAmount = turn_speed * deltaTime;
            if (pitch - pitchAmount > -maxPitch)
            {
                camForward = rotateAroundAxis(camForward, cameraRight, -pitchAmount);
                pitch -= pitchAmount;
            }
            camForward.normalize();
        }
        if (keyStateQ)
        {
            eye = eye - cameraRight * movement_speed * deltaTime;
        }
        if (keyStateE == GLFW_PRESS)
        {
            eye = eye + cameraRight * movement_speed * deltaTime;
        }
        crystal_offset += 0.005;
        Vec3 crystal_animation{0.0, GLfloat(0.001 * sin(crystal_offset)), 0.0};
        crystal->translate(crystal_animation);

        view.lookAt(eye, eye + camForward, up);

        GLfloat alpha{0.1f};
        Vec3 targetColor{Vec3{245.0f / 255.0f, 241.0f / 255.0f, 217.0f / 255.0f}};
        GLfloat fogDensity = 0.01;
        if (isMagicActive)
        {
            targetColor(0) = 157.0f / 255.0f;
            targetColor(1) = 0.0f;
            targetColor(2) = 1.0f;
            alpha = 1.0f;
            fogDensity = 0.0001f;
        }
        for (size_t i = 0; i < 6; ++i)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
            glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, reflectionCubemapResolutionXY,
                                  reflectionCubemapResolutionXY);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

            // render passes
            glViewport(0, 0, reflectionCubemapResolutionXY, reflectionCubemapResolutionXY);
            GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, face, reflectionCubemap, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            reflectionRenderView.lookAt(reflectionEyeVector, reflectionEyeVector + reflectionViewVectors[i],
                                        reflectionUpVectors[i]);
            cave.drawNodeOnly(reflectionUnityMatrix, reflectionRenderView, reflectionRenderProj, 0, lights,
                              glfwGetTime());
            candleCluster1->draw(reflectionUnityMatrix, reflectionRenderView, reflectionRenderProj, 0, lights,
                                 glfwGetTime());
            candleCluster2->draw(reflectionUnityMatrix, reflectionRenderView, reflectionRenderProj, 0, lights,
                                 glfwGetTime());
            candleCluster3->draw(reflectionUnityMatrix, reflectionRenderView, reflectionRenderProj, 0, lights,
                                 glfwGetTime());
            candleCluster4->draw(reflectionUnityMatrix, reflectionRenderView, reflectionRenderProj, 0, lights,
                                 glfwGetTime());
            candleCluster5->draw(reflectionUnityMatrix, reflectionRenderView, reflectionRenderProj, 0, lights,
                                 glfwGetTime());
            candleCluster6->draw(reflectionUnityMatrix, reflectionRenderView, reflectionRenderProj, 0, lights,
                                 glfwGetTime());
            candleCluster7->draw(reflectionUnityMatrix, reflectionRenderView, reflectionRenderProj, 0, lights,
                                 glfwGetTime());
            skybox.draw(reflectionRenderProj, reflectionRenderView);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glViewport(0, 0, width, height);
        glUseProgram(crystal_shader.getID());
        glUniform1f(alphaLocation, alpha);
        glUniform1f(crystalFogDensityLocation, fogDensity);
        glUseProgram(generic_shader.getID());
        glUniform1f(genericFogDensityLocation, fogDensity);
        glUseProgram(cave_shader.getID());
        glUniform1f(caveFogDensityLocation, fogDensity);
        glUseProgram(0);
        candle1_1_light->setColor(targetColor);
        candle2_1_light->setColor(targetColor);
        candle3_1_light->setColor(targetColor);
        candle1_2_light->setColor(targetColor);
        candle2_2_light->setColor(targetColor);
        candle3_2_light->setColor(targetColor);
        candle1_3_light->setColor(targetColor);
        candle2_3_light->setColor(targetColor);
        candle3_3_light->setColor(targetColor);
        candle1_4_light->setColor(targetColor);
        candle2_4_light->setColor(targetColor);
        candle3_4_light->setColor(targetColor);
        candle1_5_light->setColor(targetColor);
        candle2_5_light->setColor(targetColor);
        candle3_5_light->setColor(targetColor);
        candle1_6_light->setColor(targetColor);
        candle2_6_light->setColor(targetColor);
        candle3_6_light->setColor(targetColor);
        candle1_7_light->setColor(targetColor);
        candle2_7_light->setColor(targetColor);
        candle3_7_light->setColor(targetColor);
        // draw calls
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cave.draw(transform, view, projection, 0, lights, glfwGetTime());
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        crystal->draw(transform, view, projection, reflectionCubemap, lights, glfwGetTime());
        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);
        skybox.draw(projection, view);
        // end of draw calls
        glfwPollEvents();
        glfwSwapBuffers(window);
        //std::this_thread::sleep_for(16ms);
    }
}
