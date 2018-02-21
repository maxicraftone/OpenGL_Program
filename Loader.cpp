#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <list>
#include <vector>
#include <stb\stb_image.h>

#include "Logger.h"

std::list<int> vaos;
std::list<int> vbos;

unsigned int createAndBindVAO() {
	unsigned int vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void storeDataInAttributeList(unsigned int attributeID, unsigned int coordinateSize, float data[], unsigned int datasize, unsigned int step, unsigned int skip) {
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, datasize, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeID, coordinateSize, GL_FLOAT, GL_FALSE, step * sizeof(float), (void*)skip);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int createIndicesBuffer(unsigned int indices[], unsigned int datasize) {
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, datasize, indices, GL_STATIC_DRAW);
	std::cout << vboID << std::endl;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return vboID;
}

void bindIndicesBuffer(unsigned int vboID) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
}

void unbindVAO() {
	glBindVertexArray(0);
}

void bindTexture(unsigned int texture, unsigned int textureBank) {
	glActiveTexture(textureBank);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void enableAttribs(unsigned int from = 0, unsigned int to = 0) {

	for (unsigned int i = from; i <= to; i++) {
		glEnableVertexAttribArray(i);
	}

}

void disableAttribs(unsigned int from = 0, unsigned int to = 0) {

	for (unsigned int i = from; i <= to; i++) {
		glDisableVertexAttribArray(i);
	}

}

unsigned int loadDefaultTexture(const char *filePath) {
	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::string s_filePath = filePath;
		writeInfo("Texture " + s_filePath + " was loaded successfully");
	}
	else {
		writeError("Failed to load ");
		writeToConsole(filePath);
	}

	stbi_image_free(data);

	return texture;
}

void cleanUp() {
	for (unsigned int vaoID : vaos) {
		glDeleteVertexArrays(1, &vaoID);
	}
	for (unsigned int vboID : vbos) {
		glDeleteBuffers(1, &vboID);
	}
}