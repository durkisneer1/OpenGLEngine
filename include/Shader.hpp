#pragma once

#include <string>
#include <memory>
#include <glm/glm.hpp>

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
	void setVec3(const std::string& name, const glm::vec3 &value) const;
};

std::shared_ptr<Shader> load(const std::string& dirPath, const std::string& shaderName);

void releaseAll();

void release(const std::string& shaderName);

std::shared_ptr<Shader> get(const std::string& shaderName);

}  // namespace shader
}  // namespace kn
