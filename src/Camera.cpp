#include "Camera.h"

Camera::Camera(float windowWidth, float windowHeight, glm::vec3 initCameraPos, glm::vec3 initCameraFront, glm::vec3 initCameraUp, float cameraSpeed)
    :lastX(windowWidth/2.0f), lastY(windowHeight/2.0f), cameraPos(initCameraPos), cameraFront(initCameraFront), cameraUp(initCameraUp), cameraSpeed(cameraSpeed) {
    yaw = -90.0f;
    pitch = 0.0f;
    firstMouse = true;
    deltaTime = 0.0f;
    lastFrame = 0.0f;
}

void Camera::updateTime(){
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Camera::mouseCallback(GLFWwindow* window, float xpos, float ypos){

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void Camera::keyboardCallback(GLFWwindow *window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(Camera::cameraSpeed * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

struct cameraLookAt Camera::getCameraView(){
    // glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    // float radius = 10.0f;
    // float camX = static_cast<float>(sin(glfwGetTime()) * radius);
    // float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
    struct cameraLookAt retObj = {cameraPos, cameraPos+cameraFront, cameraUp};
    return retObj;
}
