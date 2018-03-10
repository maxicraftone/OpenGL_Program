#ifndef ENTITY_H
#define ENTITY_H

#include <glm\glm.hpp>
#include "Maths.h"
#include "Material.h"
#include "Light.h"

class Entity {
public:
	Entity(Position position, unsigned int vertexCount, Material material);

	void translate(float x, float y, float z);
	void translate(glm::vec3 pos);
	void translate(Position pos);
	void rotate(float rotationX, float rotationY, float rotationZ);
	void setRotation(float rotationX, float rotationY, float rotationZ);
	void setScale(float newScale);

	TransformationMatrix getModelMatrix();

	glm::vec3 getPosition();
	Material getMaterial();
	unsigned int getVertexCount();
	float getRotationX();
	float getRotationY();
	float getRotationZ();
	float getScale();
private:
	glm::vec3 position;
	Material material;
	unsigned int int_vertexCount;
	float rotX, rotY, rotZ;
	float scale;
};

class LightSource {
public:
	LightSource(Light *source_light, unsigned int vertexCount);

	void translate(float x, float y, float z);
	void translate(glm::vec3 pos);
	void translate(Position pos);
	void rotate(float rotationX, float rotationY, float rotationZ);
	void setRotation(float rotationX, float rotationY, float rotationZ);
	void setScale(float newScale);
	
	void setIgnoreColor(bool ignore);

	void setColor(glm::vec3 color);
	void setColor(float r, float g, float b);

	TransformationMatrix getModelMatrix();

	void setColorUniform(ShaderProgram shaderProgram);

	Position getPosition();
	Light *getLight();
	unsigned int getVertexCount();
	float getRotationX();
	float getRotationY();
	float getRotationZ();
	float getScale();
	bool getIgnoreColor();
private:
	Position position;
	Light *light;
	bool ignoreColor = false;
	unsigned int int_vertexCount;
	float rotX, rotY, rotZ;
	float scale;
};

#endif