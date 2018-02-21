#include <iostream>

#include "Camera.h"

Camera::Camera(Position position, Axis up, float yaw, float pitch) : Front(0.0f, 0.0f, -1.0f), MovementSpeed(def_SPEED), MouseSensitivity(def_SENSITIVTY), Zoom(def_ZOOM) {
	Pos = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(0.0f, 0.0f, -1.0f), MovementSpeed(def_SPEED), MouseSensitivity(def_SENSITIVTY), Zoom(def_ZOOM) {
	Pos.setPosition(posX, posY, posZ);
	WorldUp.setAxis(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

TransformationMatrix Camera::GetViewMatrix() {
	TransformationMatrix viewMatrix = TransformationMatrix();
	viewMatrix.lookAt(Pos.getPosition(), Pos.getPosition() + Front.getPosition(), Up.getAxis());
	return viewMatrix;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
	float velocity = MovementSpeed * deltaTime;

	if (direction == FORWARD) {
		Pos.add(FrontAxis.getAxis() * velocity);
	}
	else if (direction == BACKWARD) {
		Pos.add(-FrontAxis.getAxis() * velocity);
	}
	else if (direction == LEFT) {
		Pos.add(-Right.getAxis() * velocity);
	}
	else if (direction == RIGHT) {
		Pos.add(Right.getAxis() * velocity);
	}
	else if (direction == UP) {
		Pos.add(WorldUp.getAxis() * velocity);
	}
	else if (direction == DOWN) {
		Pos.add(-WorldUp.getAxis() * velocity);
	}
}

void Camera::ProcessJoystick(Camera_Movement direction, float deltaTime, float stickFactor) {
	float velocity = MovementSpeed * deltaTime * stickFactor;

	if (direction == FORWARD) {
		Pos.add(Front.getPosition() * velocity);
	}
	else if (direction == RIGHT) {
		Pos.add(Right.getAxis() * velocity);
	}
	Pos.setY(0.0f);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch) {
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
	if (Zoom >= 30.0f && Zoom <= 100.0f)
		Zoom -= yoffset;
	if (Zoom <= 30.0f)
		Zoom = 30.0f;
	if (Zoom >= 100.0f)
		Zoom = 100.0f;
}

void Camera::updateCameraVectors() {
	Front.setX(cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)));
	Front.setY(sin(glm::radians(Pitch)));
	Front.setZ(sin(glm::radians(Yaw)) * cos(glm::radians(Pitch)));
	Front.normalize();

	Right.setAxis(glm::normalize(glm::cross(Front.getPosition(), WorldUp.getAxis())));
	FrontAxis.setAxis(glm::normalize(glm::cross(WorldUp.getAxis(), Right.getAxis())));
	Up.setAxis(glm::normalize(glm::cross(Right.getAxis(), Front.getPosition())));
}