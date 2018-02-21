#ifndef MATHS_H
#define MATHS_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <fstream>

#include "ShaderProgram.h"

class Position;
class Axis;

class TransformationMatrix {
public:
	TransformationMatrix();
	glm::mat4 getMatrix();
	void translate(float x, float y, float z);
	void translate(Position pos);
	void scale(float scalar);
	void scale(glm::vec3 scale);
	void rotate(float degrees, Axis axis);
	void perspective(float fov, float aspectRatio, float nearPlane, float farPlane);
	void orthographic(float width, float height, float nearPlane, float farPlane);
	void lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up);
	void makeModelMatrix(ShaderProgram program);
	void makeViewMatrix(ShaderProgram program);
	void makeProjectionMatrix(ShaderProgram program);
private:
	glm::mat4 trans;
};

class Position {
public:
	Position(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	Position(glm::vec3 position);
	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 position);
	void add(float x, float y, float z);
	void add(glm::vec3 position);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void normalize();
	glm::vec3 getPosition();
	float getX();
	float getY();
	float getZ();
private:
	glm::vec3 vector;
};

enum EnumAxis {
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
	NONE
};

class Axis {
public:
	Axis(EnumAxis axis = NONE);
	Axis(EnumAxis axis, EnumAxis axis2);
	Axis(EnumAxis axis, EnumAxis axis2, EnumAxis axis3);
	void setAxis(EnumAxis axis);
	void setAxis(EnumAxis axis, EnumAxis axis2);
	void setAxis(EnumAxis axis, EnumAxis axis2, EnumAxis axis3);
	void setAxis(float x, float y, float z);
	void setAxis(glm::vec3 axis);
	void setX(bool enabled = true);
	void setY(bool enabled = true);
	void setZ(bool enabled = true);
	glm::vec3 getAxis();
private:
	glm::vec3 vector = glm::vec3(0.0f, 0.0f, 0.0f);
	EnumAxis axis;
};

#endif