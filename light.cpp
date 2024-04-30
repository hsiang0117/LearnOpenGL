#include "light.h"

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
