#ifndef ENTITY_H
#define ENTITY_H

#include <glm\glm.hpp>
#include "Maths.h"

class Material {
public:
	Material(glm::vec3 ambient = glm::vec3(1.0f), glm::vec3 diffuse = glm::vec3(1.0f), glm::vec3 specular = glm::vec3(0.0f), float shininess = 0.0f);

	void setAmbientUniform(ShaderProgram shaderProgram);
	void setDiffuseUniform(ShaderProgram shaderProgram);
	void setSpecularUniform(ShaderProgram shaderProgram);
	void setShininessUniform(ShaderProgram shaderProgram);

	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	float getShininess();
private:
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	float m_shininess;
};

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

class Light {
public:
	Light(Position position, glm::vec3 color = glm::vec3(1.0f), glm::vec3 ambient = glm::vec3(0.1f), glm::vec3 diffuse = glm::vec3(0.5f), glm::vec3 specular = glm::vec3(1.0f));

	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 pos);
	void setPosition(Position pos);
	void setColor(glm::vec3 color);
	void setColor(float r, float g, float b);

	void setPositionUniform(ShaderProgram shaderProgram);
	void setColorUniform(ShaderProgram shaderProgram);
	void setAmbientUniform(ShaderProgram shaderProgram);
	void setDiffuseUniform(ShaderProgram shaderProgram);
	void setSpecularUniform(ShaderProgram shaderProgram);

	Position getPosition();
	glm::vec3 getColor();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
private:
	Position lightPos;
	glm::vec3 l_ambient;
	glm::vec3 l_diffuse;
	glm::vec3 l_specular;
	glm::vec3 l_color;
};

class LightSource {
public:
	LightSource(Light source_light, unsigned int vertexCount);

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
	Light getLight();
	unsigned int getVertexCount();
	float getRotationX();
	float getRotationY();
	float getRotationZ();
	float getScale();
	bool getIgnoreColor();
private:
	Position position;
	Light light = Light(Position(0.0f, 0.0f, 0.0f));
	bool ignoreColor = false;
	unsigned int int_vertexCount;
	float rotX, rotY, rotZ;
	float scale;
};

#endif