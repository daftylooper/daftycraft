#pragma once
#include "Macros.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct cameraLookAt{
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
};

class Camera{
    private:
        bool firstMouse;
        float yaw;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
        float pitch;
        float lastX;
        float lastY;

        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        float cameraSpeed;
        // timing
        float deltaTime;
        float lastFrame;

    public:
        Camera(float windowWidth, float windowHeight, glm::vec3 initCameraPos, glm::vec3 initCameraFront, glm::vec3 initCameraUp, const float cameraSpeed);
        // ~Camera();
        void updateTime();
        void mouseCallback(GLFWwindow* window, float xpos, float ypos);
        void keyboardCallback(GLFWwindow *window);
        struct cameraLookAt getCameraView();
};