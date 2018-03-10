#ifndef LIGHT_H
#define LIGHT_H

#include "Maths.h"

class Light {
public:
	Light(Position position, glm::vec3 color = glm::vec3(1.0f), glm::vec3 ambient = glm::vec3(0.1f), glm::vec3 diffuse = glm::vec3(0.5f), glm::vec3 specular = glm::vec3(1.0f));

	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 pos);
	void setPosition(Position pos);
	void setColor(glm::vec3 color);
	void setColor(float r, float g, float b);

	virtual void setupUniforms(ShaderProgram shaderProgram);
	void setStandardUniforms(ShaderProgram shaderProgram);

	void setPositionUniform(ShaderProgram shaderProgram);
	void setColorUniform(ShaderProgram shaderProgram);
	void setAmbientUniform(ShaderProgram shaderProgram);
	void setDiffuseUniform(ShaderProgram shaderProgram);
	void setSpecularUniform(ShaderProgram shaderProgram);

	void setDirectionUniform(ShaderProgram shaderProgram, glm::vec3 lightDir);
	void setCutoffUniform(ShaderProgram shaderProgram, float cutoff);
	void setConstLinQuadUniforms(ShaderProgram shaderProgram, float linear, float quadratic);

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

class PointLight : public Light {
public:
	PointLight(Position position, glm::vec3 color = glm::vec3(1.0f), glm::vec3 ambient = glm::vec3(0.1f), glm::vec3 diffuse = glm::vec3(0.5f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 const_lin_quad = glm::vec3(1.0f, 0.09f, 0.032f));

	void setConstant(float newConstant);
	void setLinear(float newLinear);
	void setQuadratic(float newQuadratic);

	void setupUniforms(ShaderProgram shaderProgram);

	float getConstant();
	float getLinear();
	float getQuadratic();

private:
	float constant;
	float linear;
	float quadratic;
};

class DirectionalLight : public Light {
public:
	DirectionalLight(glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f), glm::vec3 ambient = glm::vec3(0.1f), glm::vec3 diffuse = glm::vec3(0.5f), glm::vec3 specular = glm::vec3(1.0f));

	void setDirection(glm::vec3 direction);

	void setupUniforms(ShaderProgram shaderProgram);

	glm::vec3 getDirection();

private:
	glm::vec3 lightDir;
};

class SpotLight : public Light {
public:
	SpotLight(Position position, glm::vec3 direction, float cutOff, glm::vec3 color = glm::vec3(1.0f), glm::vec3 ambient = glm::vec3(0.1f), glm::vec3 diffuse = glm::vec3(0.5f), glm::vec3 specular = glm::vec3(1.0f), glm::vec3 const_lin_quad = glm::vec3(1.0f, 0.0f, 0.0f));

	void setDirection(glm::vec3 direction);
	void setCutoff(float cutOff);

	void setLinear(float newLinear);
	void setQuadratic(float newQuadratic);

	void setupUniforms(ShaderProgram shaderProgram);

	glm::vec3 getDirection();
	float getCutoff();

	float getLinear();
	float getQuadratic();
private:
	glm::vec3 lightDir;
	float cutoff;

	float linear;
	float quadratic;
};

#endif