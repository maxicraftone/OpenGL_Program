#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm\glm.hpp>
#include "Maths.h"

class Material {
public:
	Material();
	Material(ShaderProgram shaderProgram, unsigned int diffuseMap, unsigned int specularMap, float shininess = 0.0f, unsigned int diffTexBank = 0, unsigned int specTexBank = 1);
	Material(ShaderProgram shaderProgram, const char *diffuseMap, const char *specularMap, float shininess = 0.0f, unsigned int diffTexBank = 0, unsigned int specTexBank = 1);
	~Material();

	void setupUniforms(ShaderProgram shaderProgram);

	void setDiffuseTexturebank(ShaderProgram shaderProgram);
	void setSpecularTexturebank(ShaderProgram shaderProgram);

	void setShininessUniform(ShaderProgram shaderProgram);

	unsigned int getDiffuseMapID();
	unsigned int getSpecularMapID();
	unsigned int getDiffuseMapTextureBank();
	unsigned int getSpecularMapTextureBank();
	float getShininess();
private:
	unsigned int diffuseMapID;
	unsigned int specularMapID;
	unsigned int diffuseTexBank;
	unsigned int specularTexBank;
	float m_shininess;
};

#endif
