#include "Renderer.h"
#include "Logger.h"

void renderLightSource(LightSource l, ShaderProgram shaderProgram) {
	l.getModelMatrix().makeModelMatrix(shaderProgram);
	shaderProgram.setMat_4("modelMatrix_inversed", glm::inverse(l.getModelMatrix().getMatrix()));

	l.setColorUniform(shaderProgram);

	l.getLight().setPositionUniform(shaderProgram);
	l.getLight().setColorUniform(shaderProgram);
	l.getLight().setAmbientUniform(shaderProgram);
	l.getLight().setDiffuseUniform(shaderProgram);
	l.getLight().setSpecularUniform(shaderProgram);

	glDrawArrays(GL_TRIANGLES, 0, l.getVertexCount());
}

void renderEntity(Entity e, Light l, ShaderProgram shaderProgram) {
	e.getModelMatrix().makeModelMatrix(shaderProgram);
	shaderProgram.setMat_4("modelMatrix_inversed", glm::inverse(e.getModelMatrix().getMatrix()));
	//e.getMaterial().setAmbientUniform(shaderProgram);
	//e.getMaterial().setDiffuseUniform(shaderProgram);
	e.getMaterial().setSpecularUniform(shaderProgram),
	e.getMaterial().setShininessUniform(shaderProgram);
	
	l.setPositionUniform(shaderProgram);
	l.setColorUniform(shaderProgram);
	l.setAmbientUniform(shaderProgram);
	l.setDiffuseUniform(shaderProgram);
	l.setSpecularUniform(shaderProgram);

	/*shaderProgram.setFloat_3("light.position", glm::vec3(0.0f, 0.5f, 1.0f));
	shaderProgram.setFloat_3("light.color", glm::vec3(1.0f));
	shaderProgram.setFloat_3("light.ambient", glm::vec3(0.1f));
	shaderProgram.setFloat_3("light.diffuse", glm::vec3(0.5f));
	shaderProgram.setFloat_3("light.specular", glm::vec3(1.0f));*/

	glDrawArrays(GL_TRIANGLES, 0, e.getVertexCount());
}