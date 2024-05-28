#pragma once

#include <memory>
#include <glm/glm.hpp>

namespace kn {
namespace shader { struct Shader; }
namespace light {

class PointLight;
class SpotLight;

void setShader(std::shared_ptr<shader::Shader> shader);
std::shared_ptr<PointLight> createPointLight();
std::shared_ptr<SpotLight> createSpotLight();

class PointLight
{
public:
    PointLight();
    ~PointLight() = default;

    void setPos(const glm::vec3& pos);
    void setAmbient(const glm::vec3& ambient);
    void setDiffuse(const glm::vec3& diffuse);
    void setSpecular(const glm::vec3& specular);
    void setLinearAttenuation(float linearAttenuation);
    void setQuadraticAttenuation(float quadraticAttenuation);

private:
    int m_index;
};

class SpotLight
{
public:
    SpotLight();
    ~SpotLight() = default;

    void setPos(const glm::vec3& pos);
    void setDir(const glm::vec3& dir);
    void setAmbient(const glm::vec3& ambient);
    void setDiffuse(const glm::vec3& diffuse);
    void setSpecular(const glm::vec3& specular);
    void setLinearAttenuation(float linearAttenuation);
    void setQuadraticAttenuation(float quadraticAttenuation);
    void setCutOff(float cutOff);
    void setOuterCutOff(float outerCutOff);

private:
    int m_index;
};

namespace sun {

void setDirection(const glm::vec3& dir);
void setAmbient(const glm::vec3& ambient);
void setDiffuse(const glm::vec3& diffuse);
void setSpecular(const glm::vec3& specular);

}  // namespace sun
}  // namespace light
}  // namespace kn
