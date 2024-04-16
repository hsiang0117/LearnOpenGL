#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

enum direction {
	FRONT,
	BACK,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//default camera settings
const glm::vec3 default_cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
const glm::vec3 default_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 default_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
const float default_pitch = 0.0f;
const float default_yaw = -90.0f;
const float default_fov = 55.0f;
const float default_sensitivity = 0.05f;


class Camera
{
public:
	Camera();
	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float fov, float sensitivity);
	glm::vec3 getCameraPos();
	glm::mat4 getViewMat();
	glm::mat4 getProjectionMat(float width, float height);
	void processKeyboard(direction d);
	void processMouseMovement(double xpos, double ypos);
	void processMouseScroll(double yoffset);
	void updateDeltaTime();
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float fov;
	float sensitivity;
	float pitch;
	float yaw;
	bool firstMouse = true;
	float lastX;
	float lastY;
	float lastFrameTime = 0;
	float deltaTime = 0;
};

#endif // !CAMERA_H
