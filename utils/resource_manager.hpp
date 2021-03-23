#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <glad/glad.h>
#include <map>
#include <string>

#include "shader.hpp"

class ResourceManager
{
public:
    static std::map<std::string, Shader> Shaders;
    static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, std::string name);
    static Shader GetShader(std::string name);
    static void Clear();

private:
    ResourceManager() {}
    static Shader loadShaderFromFile(const char *vShader, const char *fShader);
};

#endif