#include <glad\glad.h>
#include <GLFW\glfw3.h>

void enableDepthTest() {
	glEnable(GL_DEPTH_TEST);
}

void bindVertexArray(unsigned int vao) {
	glBindVertexArray(vao);
}