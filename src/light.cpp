#include "Light.hpp"

namespace kn
{

DirectionalLight::DirectionalLight()
{
    m_shaderPtr = shader::get("default");
}

void DirectionalLight::update()
{
    m_shaderPtr->setVec3("dirLight.direction", direction);
    m_shaderPtr->setVec3("dirLight.ambient", ambient);
    m_shaderPtr->setVec3("dirLight.diffuse", diffuse);
    m_shaderPtr->setVec3("dirLight.specular", specular);
}

}  // namespace kn
