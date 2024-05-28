#include "Shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

namespace kn
{
namespace shader
{

static std::map<std::string, std::shared_ptr<Shader>> shaderMap;

void releaseAll()
{
    for (const auto& pair : shaderMap) {
        glDeleteProgram(pair.second->ID);
    }
    shaderMap.clear();
}

void release(const std::string& shaderName)
{
    auto it = shaderMap.find(shaderName);
    if (it != shaderMap.end())
    {
        glDeleteProgram(it->second->ID);
        shaderMap.erase(it);
    }
    else
    {
        std::cout << "KN::SHADER::RELEASE::KEY_NOT_FOUND" << std::endl;
    }
}

std::shared_ptr<Shader> get(const std::string& shaderName)
{
    auto it = shaderMap.find(shaderName);
    if (it != shaderMap.end())
        return it->second;
    else
        return nullptr;
}

std::shared_ptr<Shader> load(const std::string& dirPath, const std::string& shaderName)
{
    auto it = shaderMap.find(shaderName);
    if (it != shaderMap.end() && it->second->path == dirPath)
        return it->second;

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::string vertexPath = dirPath + shaderName + ".vert";
    std::string fragmentPath = dirPath + shaderName + ".frag";

    // Ensure ifstream objects can throw exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        // Read files' buffer contents into streams
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure const&)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    int success;
    char infoLog[512];

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX:COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT:COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    Shader shader;

    shader.ID = glCreateProgram();
    glAttachShader(shader.ID, vertex);
    glAttachShader(shader.ID, fragment);
    glLinkProgram(shader.ID);
    glGetProgramiv(shader.ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader.ID, 512, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // Delete shaders from RAM as they are in the GPU now
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    auto shaderPtr = std::make_shared<Shader>(shader);
    shaderMap[std::move(shaderName)] = shaderPtr;

    return shaderPtr;
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}

}  // namespace shader
}  // namespace kn
