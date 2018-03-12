#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include "ShaderProgram.h"
#include "Logger.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

ShaderProgram::ShaderProgram(const char *vshSourceFile, const char *fshSourceFile){
	shaderProgram = glCreateProgram();
	addVertexShader(vshSourceFile);
	addFragmentShader(fshSourceFile);
}

void ShaderProgram::addVertexShader(const char *vshSourceFile){//const char *vshSource) {
	std::ifstream file(vshSourceFile);
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string contents((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	const char *vshSource = contents.c_str();
	
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vshSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		writeError("Vertex shader compilation failed: ");
		writeToConsole(infoLog);
	}
	else
	{
		writeInfo("Vertex shader was compiled successfully");
	}

	glAttachShader(shaderProgram, vertexShader);
}

void ShaderProgram::addFragmentShader(const char *fshSourceFile) {
	std::ifstream file(fshSourceFile);
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string contents((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	const char *fshSource = contents.c_str();
	//std::cout << fshSource << std::endl;

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fshSource, NULL);
	glCompileShader(fragmentShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		writeError("Fragment shader compilation failed: ");
		writeToConsole(infoLog);
	}
	else
	{
		writeInfo("Fragment shader was compiled successfully");
	}

	glAttachShader(shaderProgram, fragmentShader);
}

void ShaderProgram::deleteVertexShader() {
	if (!vertexShader) {
		writeError("Vertex shader cannot be deleted, because it doesn't exist");
	}
	else 
	{
		glDetachShader(shaderProgram, vertexShader);
		glDeleteShader(vertexShader);
	}
}

void ShaderProgram::deleteFragmentShader() {
	if (!fragmentShader) {
		writeError("Fragment shader cannot be deleted, because it doesn't exist");
	}
	else
	{
		glDetachShader(shaderProgram, fragmentShader);
		glDeleteShader(fragmentShader);
	}
}

void ShaderProgram::linkProgram() {
	glLinkProgram(shaderProgram);

	int  success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		writeError("Linking of shader program failed: ");
		writeToConsole(infoLog);
	}
	else
	{
		writeInfo("Shaderprogram was linked successfully");
	}

	deleteVertexShader();
	deleteFragmentShader();
}

void ShaderProgram::loadUniforms(void(*func)()) {
	func();
}

void ShaderProgram::activate() {
	glUseProgram(shaderProgram);
	active = true;
}

bool ShaderProgram::isActive() {
	return active;
}

unsigned int ShaderProgram::getShaderProgram() {
	return shaderProgram;
}

void ShaderProgram::stop() {
	glUseProgram(0);
	active = false;
}

void ShaderProgram::cleanUp() {
	stop();
	deleteVertexShader();
	deleteFragmentShader();
	glDeleteProgram(shaderProgram);
}

void ShaderProgram::setTexturebank(const std::string &uniform, unsigned int textureBank) {
	glUniform1i(glGetUniformLocation(shaderProgram, uniform.c_str()), textureBank);
}

void ShaderProgram::setFloat_4(const std::string &name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
}

void ShaderProgram::setFloat_4(const std::string &name, glm::vec4 floats) {
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), floats.x, floats.y, floats.z, floats.w);
}

void ShaderProgram::setFloat_3(const std::string &name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}

void ShaderProgram::setFloat_3(const std::string &name, glm::vec3 floats) {
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), floats.x, floats.y, floats.z);
}

void ShaderProgram::setFloat_1(const std::string &name, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void ShaderProgram::setInt_1(const std::string &name, unsigned int value) {
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void ShaderProgram::setMat_4(const std::string &name, glm::mat4 matrix) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}