cmake_minimum_required(VERSION 3.0.0)
project(opengl_tutorial VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/glad ${CMAKE_SOURCE_DIR}/src/vendor)

add_executable(opengl_tutorial src/main.cpp src/Renderer.cpp src/VertexBuffer.cpp src/IndexBuffer.cpp src/VertexArray.cpp src/Shader.cpp src/Macros.cpp src/Texture.cpp src/Camera.cpp src/PerlinNoise.cpp src/vendor/stb_image/stb_image.cpp include/glad.c)

target_link_libraries(opengl_tutorial glfw OpenGL::GL)