#include <iostream>
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <sstream>
#include <string>
#include <fstream>
#include <cassert>
#include <chrono>
#include <thread>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Macros.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"
#include "PerlinNoise.h"
// #include "MyWindow.h"

int width = 1920;
int height = 1080;

Renderer renderer;
Camera camera((float)width, (float)height, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 500.0f);

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    camera.mouseCallback(window, xposIn, yposIn);
}

int main(void){
    GLFWwindow* window;

    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Daftycraft!", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize glad after creating the OpenGL context and making it current */
    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialize glad" << std::endl;
        glfwTerminate();
        return -1;
    }

    // glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    float vertices[] = {
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.25f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.25f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.25f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.25f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 0.25f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.5f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.25f, 1.0f,

        -0.5f, -0.5f, 0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.5f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.75f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.75f, 0.0f,

        0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.25f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.25f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 0.25f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.25f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,

        4, 5, 6,
        4, 6, 7,

        8, 11, 10,
        8, 9, 10,

        12, 15, 13,
        13, 15, 14,

        16, 17, 19,
        17, 18, 19,

        20, 21, 23,
        21, 22, 23
    };

    // glm::vec3 cubePositions[] = {
    //     glm::vec3( 0.0f,  0.0f,  0.0f),
    //     glm::vec3( 2.0f,  5.0f, -15.0f),
    //     glm::vec3(-1.5f, -2.2f, -12.5f),
    //     glm::vec3(-3.8f, -2.0f, -12.3f),
    //     glm::vec3 (2.4f, -0.4f, -3.5f),
    //     glm::vec3(-1.7f,  3.0f, -7.5f),
    //     glm::vec3( 1.3f, -2.0f, -2.5f),
    //     glm::vec3( 1.5f,  2.0f, -2.5f),
    //     glm::vec3( 1.5f,  0.2f, -1.5f),
    //     glm::vec3(-1.3f,  1.0f, -1.5f)
    // };

        PerlinNoise noise(11, 11, 99, 99);
        noise.generatePerlin();
        noise.generateCubes();

    // std::cout<<"Cubes Generated Size: "<<noise.cubes.size()<<std::endl;

    // GLCall(glEnable(GL_DEPTH_CLAMP));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;
    //Define buffers to send vertext data into
    VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 3);
    layout.Push(GL_FLOAT, 2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, sizeof(indices));

    Shader shader("../res/shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(60.0f), (float)width / (float)height, 0.1f, 100.0f);

    Texture texture("../res/textures/grass-texture.png");
    texture.Bind(0);
    shader.SetUniform1i("u_Texture", 0);

    // GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    // assert(location!=-1);
    // GLCall(glBindVertexArray(0));

    //unbind all data
    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();
    texture.Unbind();

    float r = 0.0f;

    bool keypressed = false;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        shader.Bind();
        camera.updateTime();

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, mouse_callback);
        camera.keyboardCallback(window);

        struct cameraLookAt camValues = camera.getCameraView();
        glm::mat4 view = glm::lookAt(camValues.cameraPos, camValues.cameraFront, camValues.cameraUp);
        
        for(int i=0; i<noise.cubes.size(); i++){

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, noise.cubes[i]);
            // float angle = 20.0f * i;
            // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glm::mat4 mvp = projection*view*model;
            shader.SetUniformMat4f("u_MVP", mvp);

            texture.Bind();
            renderer.Draw(va, ib, shader);
        }

        // for(int i=0; i<1; i++){

        //     glm::mat4 model = glm::mat4(1.0f);
        //     model = glm::translate(model, glm::vec3(2.0f, 2.0f, 2.0f));
        //     // float angle = 20.0f * i;
        //     // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //     glm::mat4 mvp = projection*view*model;
        //     shader.SetUniformMat4f("u_MVP", mvp);

        //     texture.Bind();
        //     renderer.Draw(va, ib, shader);
        // }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        // if(r>1.0f){r=0.0f;}else{r+=0.05f;}

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // glfwTerminate();
    return 0;
}