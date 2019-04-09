# Project definition
cmake_minimum_required(VERSION 3.0)
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
project(PhobosDemo)
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_REQUIRED_FLAGS -std=c++17fs)

# find_package( OpenGL REQUIRED )
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs")
# set(SOURCES "${SRC_DIR}/main.cpp")

FILE(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# glad
# set(GLAD_DIR "${LIB_DIR}/glad")
# add_library("glad" "${GLAD_DIR}/src/glad.c")
# target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
# target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
# target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# glew
set(GLEW_DIR "${LIB_DIR}/glew")
add_library("glew" "${GLEW_DIR}/src/glew.c")
target_include_directories("glew" PRIVATE "${GLEW_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLEW_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glew" "${CMAKE_DL_LIBS}")

# FreeImage
set(FREE_IMAGE_DIR "${LIB_DIR}/FreeImage")
add_subdirectory("${FREE_IMAGE_DIR}")
target_link_libraries(${PROJECT_NAME} "FreeImage")

# TinyXML2
set(TINYXML2_DIR "${LIB_DIR}/tinyxml2")
add_subdirectory("${TINYXML2_DIR}")
target_link_libraries(${PROJECT_NAME} "tinyxml2")

# GLM
set(GLM_TEST_ENABLE OFF)
# option(GLM_TEST_ENABLE OFF)
# GLM_TEST_ENABLE
set(GLM_DIR "${LIB_DIR}/glm")
add_subdirectory("${GLM_DIR}")
target_link_libraries(${PROJECT_NAME} "glm")

if (APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# target_link_libraries(PhobosDemo OpenGL)
# find_package(OpenGL REQUIRED)
