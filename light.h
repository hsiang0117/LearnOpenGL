#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

typedef struct DirLight
{
    glm::vec3 direction;
    glm::vec3 color;
    float ambient;
    float diffuse;
    float specular;
}DirLight;

typedef struct PointLight {
    glm::vec3 position;
    glm::vec3 color;
    float ambient;
    float diffuse;
    float specular;
    float constant;
    float linear;
    float quadratic;
}PointLight;

typedef struct SpotLight {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 direction;
    float phi;
    float ambient;
    float diffuse;
    float specular;
}SpotLight;

#endif // !LIGHT_H