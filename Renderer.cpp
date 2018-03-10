#include <glad\glad.h>
#include "Renderer.h"
#include "Logger.h"

void renderLightSource(LightSource l, ShaderProgram shaderProgram) {
	l.getModelMatrix().makeModelMatrix(shaderProgram);
	shaderProgram.setMat_4("modelMatrix_inversed", glm::inverse(l.getModelMatrix().getMatrix()));

	l.setColorUniform(shaderProgram);

	glDrawArrays(GL_TRIANGLES, 0, l.getVertexCount());
}

void renderEntity(Entity e, Light *l, ShaderProgram shaderProgram) {

	glActiveTexture(GL_TEXTURE0 + e.getMaterial().getDiffuseMapTextureBank());
	glBindTexture(GL_TEXTURE_2D, e.getMaterial().getDiffuseMapID());
	glActiveTexture(GL_TEXTURE0 + e.getMaterial().getSpecularMapTextureBank());
	glBindTexture(GL_TEXTURE_2D, e.getMaterial().getSpecularMapID());

	e.getModelMatrix().makeModelMatrix(shaderProgram);
	shaderProgram.setMat_4("modelMatrix_inversed", glm::inverse(e.getModelMatrix().getMatrix()));
	e.getMaterial().setupUniforms(shaderProgram);

	l->setupUniforms(shaderProgram);

	glDrawArrays(GL_TRIANGLES, 0, e.getVertexCount());
}