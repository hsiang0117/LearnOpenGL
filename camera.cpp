#include"camera.h"

Camera::Camera() {
    this->cameraPos = default_cameraPos;
    this->cameraFront = default_cameraFront;
    this->cameraUp = default_cameraUp;
    this->fov = default_fov;
    this->sensitivity = default_sensitivity;
    this->pitch = default_pitch;
    this->yaw = default_yaw;
}

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float fov, float sensitivity) {
    this->cameraPos = cameraPos;
    this->cameraFront = cameraFront;
    this->cameraUp = cameraUp;
    this->fov = fov;
    this->sensitivity = sensitivity;
    this->pitch = default_pitch;
    this->yaw = default_yaw;
}

glm::vec3 Camera::getCameraPos()
{
    return cameraPos;
}

glm::mat4 Camera::getViewMat() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::getProjectionMat(float width, float height)
{
    return glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
}

void Camera::processKeyboard(direction d) {
    float cameraSpeed = 2.5f * deltaTime;
    switch (d) {
    case FRONT:
        cameraPos += cameraSpeed * cameraFront;
        break;
    case BACK:
        cameraPos -= cameraSpeed * cameraFront;
        break;
    case LEFT:
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        break;
    case RIGHT:
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        break;
    case UP:
        cameraPos += glm::normalize(cameraUp) * cameraSpeed;
        break;
    case DOWN:
        cameraPos -= glm::normalize(cameraUp) * cameraSpeed;
        break;
    }
}

void Camera::processMouseMovement(double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

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

void Camera::processMouseScroll(double yoffset) {
    if (fov >= 1.0f && fov <= 70.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 70.0f)
        fov = 70.0f;
}

void Camera::updateDeltaTime() {
    float currentFrameTime = glfwGetTime();
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}