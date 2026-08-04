project(
    'CG1 Projektarbeit Team FireBrick',
    'cpp',
    default_options : [
        'cpp_std=c++14',
        'warning_level=3'
        ]
)

glew_dep = dependency('glew')
glfw_dep = dependency('glfw3')
opengl_dep = dependency('opengl')

graphics_deps = [
    glew_dep,
    glfw_dep,
    opengl_dep
]

inc = include_directories('include')

core_sources = files(
    'src/types/Mat3.cpp',
    'src/types/Mat4.cpp',
    'src/types/Vec3.cpp',
    'src/types/Vec4.cpp',
    'src/utilities/ShaderSource.cpp',
    'src/utilities/ObjectData.cpp'
)

test_sources = files(
    'tests/testsrc/Mat4Test.cpp',
    'tests/testsrc/Mat3Test.cpp',
    'tests/testsrc/ShaderTest.cpp',
    'tests/testsrc/Vec3Test.cpp',
    'tests/testsrc/Vec4Test.cpp',
    'tests/testsrc/ObjectDataTest.cpp'
)

core_lib = static_library(
    'core',
    core_sources,
    include_directories : inc,
    dependencies : graphics_deps
)

test_exe = executable(
    'unit_tests',
    'tests/unit_tests.cpp',
    test_sources,
    include_directories : inc,
    link_with : core_lib,
    dependencies : graphics_deps
)

test(
    'unit_tests',
    test_exe
)