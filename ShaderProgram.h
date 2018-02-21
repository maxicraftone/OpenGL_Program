#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <fstream>

class ShaderProgram {
public:
	ShaderProgram(const char *vshSourceFile, const char *fshSourceFile);
	void addVertexShader(const char *vshSourceFile);
	void addFragmentShader(const char *fshSourceFile);
	void deleteVertexShader(void);
	void deleteFragmentShader(void);
	void linkProgram(void);
	void loadUniforms(void(*func)());
	void activate(void);
	bool isActive(void);
	void setFloat_4(const std::string &name, float x, float y, float z, float w);
	void setFloat_4(const std::string &name, glm::vec4 floats);
	void setFloat_3(const std::string &name, float x, float y, float z);
	void setFloat_3(const std::string &name, glm::vec3 floats);
	void setFloat_1(const std::string &name, float value);
	void setInt_1(const std::string &name, unsigned int value);
	void setMat_4(const std::string &name, glm::mat4 matrix);
	unsigned int getShaderProgram();
	void stop(void);
	void cleanUp(void);
private:
	bool active = false;
	unsigned int shaderProgram;
	unsigned int vertexShader;
	unsigned int fragmentShader;
};

#endif