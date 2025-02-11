#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int shaderProgram;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 mat) const;
    void setVec3(const std::string& name, glm::vec3 vec) const;

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};

#endif