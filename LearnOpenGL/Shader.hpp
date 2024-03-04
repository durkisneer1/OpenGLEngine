#pragma once

#include <glad/glad.h>

#include <string>


class Shader
{
public:
	unsigned int ID;  // The shader program

	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void free();

	// Utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
};
