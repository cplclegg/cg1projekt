# GNU Make build for CG12026 Projektarbeit Team FireBrick
# Equivalent to the current meson.build for the main project and unit tests.

CXX := g++
AR  := ar

BUILD_DIR := build
INCLUDE_DIR := include

CPPFLAGS := -I$(INCLUDE_DIR)
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic
ARFLAGS := rcs

# Prefer pkg-config when available, with a direct-link fallback suitable for
# typical Ubuntu installations of libglew-dev, libglfw3-dev and OpenGL dev libs.
PKG_CFLAGS := $(shell pkg-config --cflags glew glfw3 2>/dev/null)
PKG_LIBS   := $(shell pkg-config --libs glew glfw3 2>/dev/null)

CPPFLAGS += $(PKG_CFLAGS)

ifeq ($(strip $(PKG_LIBS)),)
LDLIBS := -lGLEW -lglfw -lGL
else
LDLIBS := $(PKG_LIBS) -lGL
endif

CORE_SOURCES := \
	src/types/Mat3.cpp \
	src/types/Mat4.cpp \
	src/types/Vec3.cpp \
	src/types/Vec4.cpp \
	src/utilities/ShaderSource.cpp \
	src/utilities/ShaderProgram.cpp \
	src/utilities/ObjectData.cpp \
	src/utilities/TextureData.cpp \
	src/utilities/CubeMap.cpp \
	src/utilities/Material.cpp \
	src/utilities/Renderable.cpp \
	src/utilities/SceneNode.cpp \
	src/utilities/GLContext.cpp \
	src/utilities/PointLight.cpp \
	src/utilities/SpotLight.cpp \
	src/utilities/LightSources.cpp \
	src/utilities/SceneHelpers.cpp

TEST_SOURCES := \
	tests/testsrc/Mat4Test.cpp \
	tests/testsrc/Mat3Test.cpp \
	tests/testsrc/ShaderTest.cpp \
	tests/testsrc/Vec3Test.cpp \
	tests/testsrc/Vec4Test.cpp \
	tests/testsrc/ObjectDataTest.cpp \
	tests/testsrc/TextureDataTest.cpp

UNIT_TEST_MAIN := tests/unit_tests.cpp
PROJECT_MAIN := project_scene/ProjectTeamFirebrick.cpp

CORE_OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CORE_SOURCES))
TEST_OBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEST_SOURCES))
UNIT_TEST_MAIN_OBJECT := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(UNIT_TEST_MAIN))
PROJECT_MAIN_OBJECT := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(PROJECT_MAIN))

CORE_LIB := $(BUILD_DIR)/libcore.a
UNIT_TEST_EXE := $(BUILD_DIR)/unit_tests
PROJECT_EXE := $(BUILD_DIR)/ProjectTeamFirebrick

.PHONY: all clean test run

all: $(PROJECT_EXE) $(UNIT_TEST_EXE)

$(CORE_LIB): $(CORE_OBJECTS)
	@mkdir -p $(dir $@)
	$(AR) $(ARFLAGS) $@ $^

$(PROJECT_EXE): $(PROJECT_MAIN_OBJECT) $(CORE_LIB)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

$(UNIT_TEST_EXE): $(UNIT_TEST_MAIN_OBJECT) $(TEST_OBJECTS) $(CORE_LIB)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

test: $(UNIT_TEST_EXE)
	./$(UNIT_TEST_EXE)

# Run this from the repository root so relative resource paths resolve there.
run: $(PROJECT_EXE)
	./$(PROJECT_EXE)

clean:
	rm -rf $(BUILD_DIR)

# Optional/demo executables from the Meson file. Uncomment/adapt if needed.
#
# TEAPOT_MAIN := tests/load_obj_test.cpp
# TEAPOT_OBJECT := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEAPOT_MAIN))
# TEAPOT_EXE := $(BUILD_DIR)/teapot_demo
# $(TEAPOT_EXE): $(TEAPOT_OBJECT) $(CORE_LIB)
# 	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@
#
# TEXTURE_DEMO_MAIN := tests/load_texture_test.cpp
# TEXTURE_DEMO_OBJECT := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(TEXTURE_DEMO_MAIN))
# TEXTURE_DEMO_EXE := $(BUILD_DIR)/texture_demo
# $(TEXTURE_DEMO_EXE): $(TEXTURE_DEMO_OBJECT) $(CORE_LIB)
# 	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@
#
# GLOBE_MAIN := uebungsblaetter/uebung7/earth.cpp
# GLOBE_OBJECT := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(GLOBE_MAIN))
# GLOBE_EXE := $(BUILD_DIR)/globe_demo
# $(GLOBE_EXE): $(GLOBE_OBJECT) $(CORE_LIB)
# 	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@
