#include "Light.h"

Light::Light(Position position, glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	lightPos = position;
	l_color = color;
	l_ambient = ambient;
	l_diffuse = diffuse;
	l_specular = specular;
}

void Light::setPosition(float x, float y, float z) {
	lightPos.setPosition(x, y, z);
}

void Light::setPosition(glm::vec3 pos) {
	lightPos.setPosition(pos.x, pos.y, pos.z);
}

void Light::setPosition(Position pos) {
	lightPos.setPosition(pos.getPosition());
}

void Light::setColor(glm::vec3 color) {
	l_color = color;
}

void Light::setColor(float r, float g, float b) {
	l_color.r = r;
	l_color.g = g;
	l_color.b = b;
}

void Light::setStandardUniforms(ShaderProgram shaderProgram) {
	setPositionUniform(shaderProgram);
	setColorUniform(shaderProgram);
	setAmbientUniform(shaderProgram);
	setDiffuseUniform(shaderProgram);
	setSpecularUniform(shaderProgram);
}

void Light::setupUniforms(ShaderProgram shaderProgram) {
	setDirectionUniform(shaderProgram, glm::vec3(0.0f));
	setCutoffUniform(shaderProgram, 0.0f);
	setConstLinQuadUniforms(shaderProgram, 0.0f, 0.0f);
	setStandardUniforms(shaderProgram);
}

void Light::setPositionUniform(ShaderProgram shaderProgram) {
	shaderProgram.setFloat_3("light.position", lightPos.getPosition());
}

void Light::setColorUniform(ShaderProgram shaderProgram) {
	shaderProgram.setFloat_3("light.color", l_color);
}

void Light::setAmbientUniform(ShaderProgram shaderProgram) {
	shaderProgram.setFloat_3("light.ambient", l_ambient);
}

void Light::setDiffuseUniform(ShaderProgram shaderProgram) {
	shaderProgram.setFloat_3("light.diffuse", l_diffuse);
}

void Light::setSpecularUniform(ShaderProgram shaderProgram) {
	shaderProgram.setFloat_3("light.specular", l_specular);
}



void Light::setDirectionUniform(ShaderProgram shaderProgram, glm::vec3 lightDir) {
	shaderProgram.setFloat_3("light.direction", lightDir);
}

void Light::setCutoffUniform(ShaderProgram shaderProgram, float cutoff) {
	shaderProgram.setFloat_1("light.cutoff", cutoff);
}

void Light::setConstLinQuadUniforms(ShaderProgram shaderProgram, float linear, float quadratic) {
	shaderProgram.setFloat_1("light.constant", 1.0f);
	shaderProgram.setFloat_1("light.linear", linear);
	shaderProgram.setFloat_1("light.quadratic", quadratic);
}

Position Light::getPosition() {
	return lightPos;
}

glm::vec3 Light::getColor() {
	return l_color;
}

glm::vec3 Light::getAmbient() {
	return l_ambient;
}

glm::vec3 Light::getDiffuse() {
	return l_diffuse;
}

glm::vec3 Light::getSpecular() {
	return l_specular;
}



PointLight::PointLight(Position position, glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 const_lin_quad) : Light(position, color, ambient, diffuse, specular){
	constant = const_lin_quad.x;
	linear = const_lin_quad.y;
	quadratic = const_lin_quad.z;
}

void PointLight::setConstant(float newConstant) {
	constant = newConstant;
}

void PointLight::setLinear(float newLinear) {
	linear = newLinear;
}

void PointLight::setQuadratic(float newQuadratic) {
	quadratic = newQuadratic;
}

void PointLight::setupUniforms(ShaderProgram shaderProgram) {
	setDirectionUniform(shaderProgram, glm::vec3(0.0f));
	setCutoffUniform(shaderProgram, 0.0f);
	setConstLinQuadUniforms(shaderProgram, linear, quadratic);
	setStandardUniforms(shaderProgram);
}

float PointLight::getConstant() {
	return constant;
}

float PointLight::getLinear() {
	return linear;
}

float PointLight::getQuadratic() {
	return quadratic;
}



DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Light(Position(glm::vec3(0.0f)), color, ambient, diffuse, specular) {
	lightDir = direction;
}

void DirectionalLight::setDirection(glm::vec3 direction) {
	lightDir = direction;
}

void DirectionalLight::setupUniforms(ShaderProgram shaderProgram) {
	setDirectionUniform(shaderProgram, lightDir);
	setCutoffUniform(shaderProgram, 0.0f);
	setConstLinQuadUniforms(shaderProgram, 0.0f, 0.0f);
	setStandardUniforms(shaderProgram);
}

glm::vec3 DirectionalLight::getDirection() {
	return lightDir;
}



SpotLight::SpotLight(Position postition, glm::vec3 direction, float cutOff, glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 const_lin_quad) : Light(postition, color, ambient, diffuse, specular) {
	lightDir = direction;
	cutoff = cutOff;

	linear = const_lin_quad.y;
	quadratic = const_lin_quad.z;
}

void SpotLight::setDirection(glm::vec3 direction) {
	lightDir = direction;
}

void SpotLight::setCutoff(float cutOff) {
	cutoff = cutOff;
}

void SpotLight::setLinear(float newLinear) {
	linear = newLinear;
}

void SpotLight::setQuadratic(float newQuadratic) {
	quadratic = newQuadratic;
}

void SpotLight::setupUniforms(ShaderProgram shaderProgram) {
	setDirectionUniform(shaderProgram, lightDir);
	setCutoffUniform(shaderProgram, glm::cos(glm::radians(cutoff)));
	setConstLinQuadUniforms(shaderProgram, linear, quadratic);
	setStandardUniforms(shaderProgram);
}

glm::vec3 SpotLight::getDirection() {
	return lightDir;
}

float SpotLight::getCutoff() {
	return cutoff;
}

float SpotLight::getLinear() {
	return linear;
}

float SpotLight::getQuadratic() {
	return quadratic;
}