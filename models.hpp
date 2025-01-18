#ifndef MODEL_H
#define MODEL_H

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

class PointLight :public Light {
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

DirLight::DirLight(glm::vec3 color, float ambient, float diffuse, float specular, glm::vec3 direction)
{
	this->color = color;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->direction = direction;
}

PointLight::PointLight(glm::vec3 color, float ambient, float diffuse, float specular, glm::vec3 position, float constant, float linear, float quadratic)
{
	this->color = color;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

SpotLight::SpotLight(glm::vec3 color, float ambient, float diffuse, float specular, glm::vec3 position, glm::vec3 direction, float phi)
{
	this->color = color;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->position = position;
	this->direction = direction;
	this->phi = phi;
}


#endif // !MODEL_H