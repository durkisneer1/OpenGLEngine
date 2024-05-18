#include "Camera.hpp"
#include "Input.hpp"
#include "Shader.hpp"
#include "Window.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>
#include <iostream>


namespace kn
{

static std::shared_ptr<shader::Shader> _shaderPtr = nullptr;

Camera::Camera(glm::vec3 pos, float fov) : pos(pos), fov(fov)
{
    _shaderPtr = kn::shader::get("default");
}

void Camera::update(double deltaTime, const glm::vec2& movementVec)
{
    float vel = speed * (float)deltaTime;
    pos += front * vel * movementVec.y;
    pos += right * vel * movementVec.x;

    look();
    updateVectors();

    _shaderPtr->setMat4("view", glm::lookAt(pos, pos + front, up));
    _shaderPtr->setMat4(
        "projection",
        glm::perspective(glm::radians(fov), (float)window::getWidth() / (float)window::getHeight(), 0.1f, 100.0f)
    );
    _shaderPtr->setVec3("viewPos", pos);
}

void Camera::look()
{
    glm::vec2 mouseRel = input::getMouseRel();

    yaw += mouseRel.x * sens;
    pitch -= mouseRel.y * sens;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

void Camera::updateVectors()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

}  // namespace kn
