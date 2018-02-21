#include "Entity.h"
#include "Logger.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) {
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
	m_shininess = shininess;
}

void Material::setAmbientUniform(ShaderProgram shaderProgram) {
	shaderProgram.setFloat_3("material.ambient", m_ambient);
}

void Material::setDiffuseUniform(ShaderProgram shaderProgram) {
	shaderProgram.setFloat_3("material.diffuse", m_diffuse);
}

void Material::setSpecularUniform(ShaderProgram shaderProgram) {
	shaderProgram.setFloat_3("material.specular", m_specular);
}

void Material::setShininessUniform(ShaderProgram shaderProgram) {
	shaderProgram.setFloat_1("material.shininess", m_shininess);
}

glm::vec3 Material::getAmbient() {
	return m_ambient;
}
glm::vec3 Material::getDiffuse() {
	return m_diffuse;
}
glm::vec3 Material::getSpecular() {
	return m_specular;
}
float Material::getShininess() {
	return m_shininess;
}

Entity::Entity(Position pos, unsigned int vertexCount, Material mat) {
	position = pos.getPosition();
	int_vertexCount = vertexCount;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	scale = 1.0f;
	material = mat;
}

void Entity::translate(float x, float y, float z) {
	position.x += x;
	position.y += y;
	position.z += z;
}

void Entity::translate(glm::vec3 pos) {
	position += pos;
}

void Entity::translate(Position pos) {
	position += pos.getPosition();
}

void Entity::rotate(float rotationX, float rotationY, float rotationZ) {
	rotX += rotationX;
	rotY += rotationY;
	rotZ += rotationZ;
}

void Entity::setRotation(float rotationX, float rotationY, float rotationZ) {
	rotX = rotationX;
	rotY = rotationY;
	rotZ = rotationZ;
}

void Entity::setScale(float newScale) {
	scale = newScale;
}

TransformationMatrix Entity::getModelMatrix() {
	TransformationMatrix modelMatrix;
	modelMatrix.translate(Position(position));
	modelMatrix.rotate(rotX, Axis(X_AXIS));
	modelMatrix.rotate(rotY, Axis(X_AXIS));
	modelMatrix.rotate(rotZ, Axis(X_AXIS));
	modelMatrix.scale(scale);
	return modelMatrix;
}

glm::vec3 Entity::getPosition() {
	return position;
}

Material Entity::getMaterial() {
	return material;
}

unsigned int Entity::getVertexCount() {
	return int_vertexCount;
}

float Entity::getRotationX() {
	return rotX;
}

float Entity::getRotationY() {
	return rotY;
}

float Entity::getRotationZ() {
	return rotZ;
}

float Entity::getScale() {
	return scale;
}

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

LightSource::LightSource(Light source_light, unsigned int vertexCount) {
	position = source_light.getPosition();
	int_vertexCount = vertexCount;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	scale = 1.0f;
	light = source_light;
}

void LightSource::translate(float x, float y, float z) {
	position.add(x, y, z);
	light.setPosition(light.getPosition().getPosition() + glm::vec3(x, y, z));
}

void LightSource::translate(glm::vec3 pos) {
	position.add(pos.x, pos.y, pos.z);
	light.setPosition(light.getPosition().getPosition() + pos);
}

void LightSource::translate(Position pos) {
	position.add(pos.getPosition());
	light.setPosition(light.getPosition().getPosition() + pos.getPosition());
}

void LightSource::rotate(float rotationX, float rotationY, float rotationZ) {
	rotX += rotationX;
	rotY += rotationY;
	rotZ += rotationZ;
}

void LightSource::setRotation(float rotationX, float rotationY, float rotationZ) {
	rotX = rotationX;
	rotY = rotationY;
	rotZ = rotationZ;
}

void LightSource::setScale(float newScale) {
	scale = newScale;
}

void LightSource::setIgnoreColor(bool ignore) {
	ignoreColor = ignore;
}

void LightSource::setColor(glm::vec3 color) {
	light.setColor(color);
}

void LightSource::setColor(float r, float g, float b) {
	light.setColor(r, g, b);
}

TransformationMatrix LightSource::getModelMatrix() {
	TransformationMatrix modelMatrix;
	modelMatrix.translate(Position(position));
	modelMatrix.rotate(rotX, Axis(X_AXIS));
	modelMatrix.rotate(rotY, Axis(X_AXIS));
	modelMatrix.rotate(rotZ, Axis(X_AXIS));
	modelMatrix.scale(scale);
	return modelMatrix;
}

void LightSource::setColorUniform(ShaderProgram shaderProgram) {
	if (!ignoreColor) {
		shaderProgram.setFloat_3("color", light.getColor());
	}
	else {
		shaderProgram.setFloat_3("color", glm::vec3(1.0f));
	}
}

Position LightSource::getPosition() {
	return position;
}

Light LightSource::getLight() {
	return light;
}

unsigned int LightSource::getVertexCount() {
	return int_vertexCount;
}

float LightSource::getRotationX() {
	return rotX;
}

float LightSource::getRotationY() {
	return rotY;
}

float LightSource::getRotationZ() {
	return rotZ;
}

float LightSource::getScale() {
	return scale;
}

bool LightSource::getIgnoreColor() {
	return ignoreColor;
}