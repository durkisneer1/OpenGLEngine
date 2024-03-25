#pragma once

#include <glm/glm.hpp>

enum CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;


namespace kn
{
	class Camera {
	public:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp;

		float yaw;
		float pitch;

		float speed;
		float sensitivity;

		Camera(
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = YAW, float pitch = PITCH
		);
		Camera(
			float posX, float posY, float posZ,
			float upX, float upY, float upZ,
			float yaw, float pitch
		);
		~Camera() = default;

		glm::mat4 getViewMatrix() const;
		void processKeyboard(CameraMovement direction, double deltaTime);
		void processMouse();
		
	private:
		void updateVectors();

		double mousePosX, mousePosY;
		double lastMousePosX, lastMousePosY;
		bool firstMouse = true;;
	};
}