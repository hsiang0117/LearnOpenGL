#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
	glm::vec3 color;
	float ambient;
	float diffuse;
	float specular;
};

class DirLight :public Light {
public:
	glm::vec3 direction;
	DirLight(glm::vec3 color, float ambient, float diffuse, float specular, glm::vec3 direction);
};

class PointLight :public Light{
public:
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
	PointLight(glm::vec3 color, float ambient, float diffuse, float specular, glm::vec3 position, float constant, float linear, float quadratic);
};

class SpotLight :public Light {
public:
	glm::vec3 position;
	glm::vec3 direction;
	float phi;
	SpotLight(glm::vec3 color, float ambient, float diffuse, float specular, glm::vec3 position, glm::vec3 direction, float phi);
};

#endif // !LIGHT_H