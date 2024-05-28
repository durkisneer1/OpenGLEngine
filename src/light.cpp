#include <vector>
#include <stdexcept>
#include <iostream>

#include "Light.hpp"
#include "Shader.hpp"

namespace kn {
namespace light {

static std::vector<std::shared_ptr<PointLight>> _pointLights;
static std::vector<std::shared_ptr<SpotLight>> _spotLights;
static std::shared_ptr<shader::Shader> _shaderPtr;

void setShader(std::shared_ptr<shader::Shader> shaderPtr)
{
    _shaderPtr = shaderPtr;
}

std::shared_ptr<PointLight> createPointLight()
{
    if (!_shaderPtr)
    {
        std::cout << "KN::LIGHT::CREATE_POINT_LIGHT::SHADER_NOT_SET\n" << std::endl;
        return nullptr;
    }
    if (_pointLights.size() >= 4)
    {
        std::cout << "KN::LIGHT::CREATE_POINT_LIGHT::TOO_MANY_POINT_LIGHTS\n" << std::endl;
        return nullptr;
    }

    PointLight light;
    auto lightPtr = std::make_shared<PointLight>(light);
    _pointLights.push_back(lightPtr);
    return lightPtr;
}

std::shared_ptr<SpotLight> createSpotLight()
{
    if (!_shaderPtr)
    {
        std::cout << "KN::LIGHT::CREATE_SPOT_LIGHT::SHADER_NOT_SET\n" << std::endl;
        return nullptr;
    }
    if (_spotLights.size() >= 4)
    {
        std::cout << "KN::LIGHT::CREATE_SPOT_LIGHT::TOO_MANY_SPOT_LIGHTS\n" << std::endl;
        return nullptr;
    }

    SpotLight light;
    auto lightPtr = std::make_shared<SpotLight>(light);
    _spotLights.push_back(lightPtr);
    return lightPtr;
}

PointLight::PointLight()
: m_index(_pointLights.size())
{
    setPos(glm::vec3(0.0f));
    setAmbient(glm::vec3(0.05f));
    setDiffuse(glm::vec3(0.8f));
    setSpecular(glm::vec3(1.0f));
    setLinearAttenuation(0.09f);
    setQuadraticAttenuation(0.032f);
    _shaderPtr->setFloat("pointLights[" + std::to_string(m_index) + "].constant", 1.0f);
}

void PointLight::setPos(const glm::vec3& position)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("pointLights[" + std::to_string(m_index) + "].position", position);
}

void PointLight::setAmbient(const glm::vec3& ambient)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("pointLights[" + std::to_string(m_index) + "].ambient", ambient);
}

void PointLight::setDiffuse(const glm::vec3& diffuse)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("pointLights[" + std::to_string(m_index) + "].diffuse", diffuse);
}

void PointLight::setSpecular(const glm::vec3& specular)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("pointLights[" + std::to_string(m_index) + "].specular", specular);
}

void PointLight::setLinearAttenuation(float linear)
{
    _shaderPtr->use();
    _shaderPtr->setFloat("pointLights[" + std::to_string(m_index) + "].linear", linear);
}

void PointLight::setQuadraticAttenuation(float quadratic)
{
    _shaderPtr->use();
    _shaderPtr->setFloat("pointLights[" + std::to_string(m_index) + "].quadratic", quadratic);
}

SpotLight::SpotLight()
: m_index(_spotLights.size())
{
    setPos(glm::vec3(0.0f));
    setDir(glm::vec3(0.0f, 0.0f, -1.0f));
    setAmbient(glm::vec3(0.0f));
    setDiffuse(glm::vec3(1.0f));
    setSpecular(glm::vec3(1.0f));
    setLinearAttenuation(0.09f);
    setQuadraticAttenuation(0.032f);
    setCutOff(12.5f);
    setOuterCutOff(17.5f);
    _shaderPtr->setFloat("spotLight.constant", 1.0f);
}

void SpotLight::setPos(const glm::vec3& position)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("spotLight.position", position);
}

void SpotLight::setDir(const glm::vec3& direction)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("spotLight.direction", direction);
}

void SpotLight::setAmbient(const glm::vec3& ambient)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("spotLight.ambient", ambient);
}

void SpotLight::setDiffuse(const glm::vec3& diffuse)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("spotLight.diffuse", diffuse);
}

void SpotLight::setSpecular(const glm::vec3& specular)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("spotLight.specular", specular);
}

void SpotLight::setLinearAttenuation(float linear)
{
    _shaderPtr->use();
    _shaderPtr->setFloat("spotLight.linear", linear);
}

void SpotLight::setQuadraticAttenuation(float quadratic)
{
    _shaderPtr->use();
    _shaderPtr->setFloat("spotLight.quadratic", quadratic);
}

void SpotLight::setCutOff(float cutOff)
{
    float angle = glm::cos(glm::radians(cutOff));
    _shaderPtr->use();
    _shaderPtr->setFloat("spotLight.cutOff", angle);
}

void SpotLight::setOuterCutOff(float outerCutOff)
{
    float angle = glm::cos(glm::radians(outerCutOff));
    _shaderPtr->use();
    _shaderPtr->setFloat("spotLight.outerCutOff", angle);
}

namespace sun {

void setDirection(const glm::vec3& dir)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("dirLight.direction", dir);
}

void setAmbient(const glm::vec3& ambient)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("dirLight.ambient", ambient);
}

void setDiffuse(const glm::vec3& diffuse)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("dirLight.diffuse", diffuse);
}

void setSpecular(const glm::vec3& specular)
{
    _shaderPtr->use();
    _shaderPtr->setVec3("dirLight.specular", specular);
}

}  // namespace sun
}  // namespace light
}  // namespace kn
