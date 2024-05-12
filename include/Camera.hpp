#pragma once

#include <glm/glm.hpp>

namespace kn
{

class Camera {
public:
    glm::vec3 pos;
    glm::vec3 front = { 0.0f, 0.0f, -1.0f };
    glm::vec3 up = { 0.0f, 1.0f, 0.0f };
    glm::vec3 right;
    glm::vec3 worldUp = { 0.0f, 1.0f, 0.0f };

    float yaw = -90.0f;
    float pitch = 0.0f;
    float speed = 2.5f;
    float sens = 0.1f;

    Camera(glm::vec3 pos, float fov);
    ~Camera() = default;

    void update(double deltaTime, const glm::vec2& movementVec);
    void look();

private:
	void updateVectors();
};

}  // namespace kn
