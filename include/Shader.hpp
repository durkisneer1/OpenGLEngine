#pragma once

#include <glm/glm.hpp>

#include <string>
#include <memory>

namespace kn
{
namespace shader
{

struct Shader
{
	unsigned int ID;

	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, const glm::mat4 &value) const;
};

std::shared_ptr<Shader> load(const std::string& dirPath, const std::string& shaderName);

void releaseAll();

void release(const std::string shaderName);

std::shared_ptr<Shader> get(const std::string& shaderName);

}  // namespace shader
}  // namespace kn
