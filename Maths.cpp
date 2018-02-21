#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <iostream>
#include "ShaderProgram.h"
#include "Logger.h"

#include "Maths.h"

TransformationMatrix::TransformationMatrix() {
	trans = glm::mat4(1.0f);
}

glm::mat4 TransformationMatrix::getMatrix() {
	return trans;
}

void TransformationMatrix::translate(float x, float y, float z) {
	trans = glm::translate(trans, glm::vec3(x, y, z));
}

void TransformationMatrix::translate(Position pos) {
	trans = glm::translate(trans, pos.getPosition());
}

void TransformationMatrix::scale(float scalar) {
	trans = glm::scale(trans, glm::vec3(scalar, scalar, scalar));
}

void TransformationMatrix::scale(glm::vec3 scale) {
	trans = glm::scale(trans, scale);
}

void TransformationMatrix::rotate(float degrees, Axis axis) {
	trans = glm::rotate(trans, glm::radians(degrees), axis.getAxis());
}

void TransformationMatrix::perspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
	trans = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void TransformationMatrix::orthographic(float width, float height, float nearPlane, float farPlane) {
	trans = glm::ortho(0.0f, width, 0.0f, height, nearPlane, farPlane);
}

void TransformationMatrix::lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up) {
	trans = glm::lookAt(pos, target, up);
}

void TransformationMatrix::makeModelMatrix(ShaderProgram program) {
	if (program.isActive()) {
		program.setMat_4("modelMatrix", trans);
	}
	else {
		writeError("Couldn't make model matrix: PROGRAM INACTIVE");
	}
}

void TransformationMatrix::makeViewMatrix(ShaderProgram program) {
	if (program.isActive()) {
		program.setMat_4("viewMatrix", trans);
	}
	else {
		writeError("Couldn't make view matrix: PROGRAM INACTIVE");
	}
}

void TransformationMatrix::makeProjectionMatrix(ShaderProgram program) {
	if (program.isActive()) {
		program.setMat_4("projectionMatrix", trans);
	}
	else {
		writeError("Couldn't make projection matrix: PROGRAM INACTIVE");
	}
}

Position::Position(float x, float y, float z) {
	vector.x = x;
	vector.y = y;
	vector.z = z;
}

Position::Position(glm::vec3 position) {
	vector.x = position.x;
	vector.y = position.y;
	vector.z = position.z;
}

void Position::setPosition(float x, float y, float z) {
	vector.x = x;
	vector.y = y;
	vector.z = z;
}

void Position::setPosition(glm::vec3 position) {
	vector = position;
}

void Position::add(float x, float y, float z) {
	vector.x += x;
	vector.y += y;
	vector.z += z;
}

void Position::add(glm::vec3 position) {
	vector += position;
}

void Position::setX(float x) {
	vector.x = x;
}

void Position::setY(float y) {
	vector.y = y;
}

void Position::setZ(float z) {
	vector.z = z;
}

void Position::normalize() {
	glm::normalize(vector);
}

glm::vec3 Position::getPosition() {
	return vector;
}

float Position::getX() {
	return vector.x;
}

float Position::getY() {
	return vector.y;
}

float Position::getZ() {
	return vector.z;
}

Axis::Axis(EnumAxis axis) {
	if (axis == X_AXIS) {
		Axis::setX();
	}
	else if (axis == Y_AXIS) {
		Axis::setY();
	}
	else if (axis == Z_AXIS) {
		Axis::setZ();
	}
}

Axis::Axis(EnumAxis axis, EnumAxis axis2) {
	if (axis == X_AXIS) {
		Axis::setX();
	}
	else if (axis == Y_AXIS) {
		Axis::setY();
	}
	else if (axis == Z_AXIS) {
		Axis::setZ();
	}
	if (axis2 == X_AXIS) {
		Axis::setX();
	}
	else if (axis2 == Y_AXIS) {
		Axis::setY();
	}
	else if (axis2 == Z_AXIS) {
		Axis::setZ();
	}
}

Axis::Axis(EnumAxis axis, EnumAxis axis2, EnumAxis axis3) {
	if (axis == X_AXIS) {
		Axis::setX();
	}
	else if (axis == Y_AXIS) {
		Axis::setY();
	}
	else if (axis == Z_AXIS) {
		Axis::setZ();
	}
	if (axis2 == X_AXIS) {
		Axis::setX();
	}
	else if (axis2 == Y_AXIS) {
		Axis::setY();
	}
	else if (axis2 == Z_AXIS) {
		Axis::setZ();
	}
	if (axis3 == X_AXIS) {
		Axis::setX();
	}
	else if (axis3 == Y_AXIS) {
		Axis::setY();
	}
	else if (axis3 == Z_AXIS) {
		Axis::setZ();
	}
}

void Axis::setAxis(EnumAxis axis) {
	if (axis == X_AXIS) {
		Axis::setX();
	}
	else if (axis == Y_AXIS) {
		Axis::setY();
	}
	else if (axis == Z_AXIS) {
		Axis::setZ();
	}
}

void Axis::setAxis(EnumAxis axis, EnumAxis axis2) {
	if (axis == X_AXIS) {
		Axis::setX();
	}
	else if (axis == Y_AXIS) {
		Axis::setY();
	}
	else if (axis == Z_AXIS) {
		Axis::setZ();
	}
	if (axis2 == X_AXIS) {
		Axis::setX();
	}
	else if (axis2 == Y_AXIS) {
		Axis::setY();
	}
	else if (axis2 == Z_AXIS) {
		Axis::setZ();
	}
}

void Axis::setAxis(EnumAxis axis, EnumAxis axis2, EnumAxis axis3) {
	if (axis == X_AXIS) {
		Axis::setX();
	}
	else if (axis == Y_AXIS) {
		Axis::setY();
	}
	else if (axis == Z_AXIS) {
		Axis::setZ();
	}
	if (axis2 == X_AXIS) {
		Axis::setX();
	}
	else if (axis2 == Y_AXIS) {
		Axis::setY();
	}
	else if (axis2 == Z_AXIS) {
		Axis::setZ();
	}
	if (axis3 == X_AXIS) {
		Axis::setX();
	}
	else if (axis3 == Y_AXIS) {
		Axis::setY();
	}
	else if (axis3 == Z_AXIS) {
		Axis::setZ();
	}
}

void Axis::setAxis(float x, float y, float z) {
	vector.x = x;
	vector.y = y;
	vector.z = z;
}

void Axis::setAxis(glm::vec3 axis) {
	vector.x = axis.x;
	vector.y = axis.y;
	vector.z = axis.z;
}

void Axis::setX(bool enabled) {
	if (!enabled) {
		vector.x = 0.0f;
	}
	else {
		vector.x = 1.0f;
	}
}

void Axis::setY(bool enabled) {
	if (!enabled) {
		vector.y = 0.0f;
	}
	else {
		vector.y = 1.0f;
	}
}

void Axis::setZ(bool enabled) {
	if (!enabled) {
		vector.z = 0.0f;
	}
	else {
		vector.z = 1.0f;
	}
}

glm::vec3 Axis::getAxis() {
	return vector;
}