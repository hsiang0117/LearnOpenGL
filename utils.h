#include <string>
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shader.h"
#include "light.h"

unsigned int load_texture(const char* path)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned int texture;
	glGenTextures(1, &texture);
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1) {
			format = GL_RED;
		}
		else if (nrChannels == 3) {
			format = GL_RGB;
		}
		else if (nrChannels == 4) {
			format = GL_RGBA;
		}
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "Load texture failed" << std::endl;
	}
	stbi_image_free(data);
	return texture;
}

void set_material(Shader shader, const char* diffuse, const char* specular, const float shininess)
{
	unsigned int diffuseMap = load_texture(diffuse);
	unsigned int specularMap = load_texture(specular);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);
	shader.setFloat("material.shininess", shininess);
}

void set_pointLight(Shader shader, std::vector<PointLight> pointLight) {
	if (pointLight.size() > 9) {
		std::cout << "Too many point light source";
	}
	else {
		for (int i = 0; i < pointLight.size(); i++) {
			shader.setVec3("pointLight[" + std::to_string(i) + "].color", pointLight[i].color);
			shader.setVec3("pointLight[" + std::to_string(i) + "].position", pointLight[i].position);
			shader.setFloat("pointLight[" + std::to_string(i) + "].ambient", pointLight[i].ambient);
			shader.setFloat("pointLight[" + std::to_string(i) + "].diffuse", pointLight[i].diffuse);
			shader.setFloat("pointLight[" + std::to_string(i) + "].specular", pointLight[i].specular);
			shader.setFloat("pointLight[" + std::to_string(i) + "].constant", pointLight[i].constant);
			shader.setFloat("pointLight[" + std::to_string(i) + "].linear", pointLight[i].linear);
			shader.setFloat("pointLight[" + std::to_string(i) + "].quadratic", pointLight[i].quadratic);
			shader.setInt("pointLightAmount", pointLight.size());
		}
	}
}

void set_dirLight(Shader shader, std::vector<DirLight> dirLight) {
	if (dirLight.size() > 9) {
		std::cout << "Too many direct light source";
	}
	else {
		for (int i = 0; i < dirLight.size(); i++) {
			shader.setVec3("dirLight[" + std::to_string(i) + "].color", dirLight[i].color);
			shader.setVec3("dirLight[" + std::to_string(i) + "].direction", dirLight[i].direction);
			shader.setFloat("dirLight[" + std::to_string(i) + "].ambient", dirLight[i].ambient);
			shader.setFloat("dirLight[" + std::to_string(i) + "].diffuse", dirLight[i].diffuse);
			shader.setFloat("dirLight[" + std::to_string(i) + "].specular", dirLight[i].specular);
			shader.setInt("dirLightAmount", dirLight.size());
		}
	}
}

void set_spotLight(Shader shader, SpotLight spotLight) {
	shader.setVec3("spotLight.color", spotLight.color);
	shader.setVec3("spotLight.position", spotLight.position);
	shader.setFloat("spotLight.ambient", spotLight.ambient);
	shader.setFloat("spotLight.diffuse", spotLight.diffuse);
	shader.setFloat("spotLight.specular", spotLight.specular);
	shader.setVec3("spotLight.direction", spotLight.direction);
	shader.setFloat("spotLight.phi", spotLight.phi);
}