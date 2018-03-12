#include "Loader.h"
#include "Material.h"
#include "Logger.h"

Material::Material() {}

Material::Material(ShaderProgram shaderProgram, unsigned int diffuseMap, unsigned int specularMap, float shininess, unsigned int diffTexBank, unsigned int specTexBank) {
	diffuseMapID = diffuseMap;
	specularMapID = specularMap;
	m_shininess = shininess;

	diffuseTexBank = diffTexBank;
	specularTexBank = specTexBank;

	setDiffuseTexturebank(shaderProgram);
	setSpecularTexturebank(shaderProgram);
}

Material::Material(ShaderProgram shaderProgram, const char *diffuseMap, const char *specularMap, float shininess, unsigned int diffTexBank, unsigned int specTexBank) {
	diffuseMapID = loadDefaultTexture(diffuseMap);
	specularMapID = loadDefaultTexture(specularMap);
	m_shininess = shininess;

	diffuseTexBank = diffTexBank;
	specularTexBank = specTexBank;

	setDiffuseTexturebank(shaderProgram);
	setSpecularTexturebank(shaderProgram);
}

void Material::setupUniforms(ShaderProgram shaderProgram) {
	setShininessUniform(shaderProgram);
}

void Material::setDiffuseTexturebank(ShaderProgram shaderProgram) {
	shaderProgram.activate();
	shaderProgram.setTexturebank("material.diffuse", diffuseTexBank);
	shaderProgram.stop();
}

void Material::setSpecularTexturebank(ShaderProgram shaderProgram) {
	shaderProgram.activate();
	shaderProgram.setTexturebank("material.specular", specularTexBank);
	shaderProgram.stop();
}

void Material::setShininessUniform(ShaderProgram shaderProgram) {
	shaderProgram.setFloat_1("material.shininess", m_shininess);
}

unsigned int Material::getDiffuseMapID() {
	return diffuseMapID;
}
unsigned int Material::getSpecularMapID() {
	return specularMapID;
}
unsigned int Material::getDiffuseMapTextureBank() {
	return diffuseTexBank;
}
unsigned int Material::getSpecularMapTextureBank() {
	return specularTexBank;
}
float Material::getShininess() {
	return m_shininess;
}
