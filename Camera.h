#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Maths.h"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

const float def_YAW = -90.0f;
const float def_PITCH = 0.0f;
const float def_SPEED = 5.0f;
const float def_SENSITIVTY = 0.1f;
const float def_ZOOM = 70.0f;

class Camera
{
public:
	Position Pos;
	Position Front;
	Axis FrontAxis;
	Axis Up;
	Axis Right;
	Axis WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(Position position = Position(), Axis up = Axis(Y_AXIS), float yaw = def_YAW, float pitch = def_PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	TransformationMatrix GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);

private:
	void updateCameraVectors();
};
#endif