#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <stb\stb_image.h>
#include <time.h>

#include "Initialiser.h"
#include "ShaderProgram.h"
#include "Loader.h"
#include "Maths.h"
#include "GL_wrapper.h"
#include "Camera.h"
#include "Logger.h"
#include "Entity.h"
#include "Renderer.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace glm;

int WIDTH = 1280;
int HEIGHT = 720;

bool wireframe = false;
bool controllerUsed;

float vertices3[] = {
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
};

float ownCube[] = {
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void calculateDeltaTime();

float lastX = (float)WIDTH / 2, lastY = (float)HEIGHT / 2;

bool firstMouse = true;

float dir_yaw = -90.0f;
float dir_pitch = 0.0f;

glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera = Camera(vec3(0.0f, 0.0f, 3.0f));

int main() {
	initGLFW();
	GLFWwindow* window = createDisplay();
	loadGLAD();

	if (failed)
		return -1;

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	ShaderProgram shaderProgram = ShaderProgram("basic.vsh", "basic.fsh");
	shaderProgram.linkProgram();
	ShaderProgram lampProgram = ShaderProgram("lamp.vsh", "lamp.fsh");
	lampProgram.linkProgram();

	unsigned int objectVAO = createAndBindVAO();
	storeDataInAttributeList(0, 3, ownCube, sizeof(ownCube), 8, 0);
	storeDataInAttributeList(1, 3, ownCube, sizeof(ownCube), 8, 3 * sizeof(float));
	storeDataInAttributeList(2, 2, ownCube, sizeof(ownCube), 8, 6 * sizeof(float));
	unbindVAO();

	unsigned int lightVAO = createAndBindVAO();
	storeDataInAttributeList(0, 3, ownCube, sizeof(ownCube), 8, 0);
	unbindVAO();

	unsigned int containerTexture2 = loadDefaultTexture("container2.jpg");
	unsigned int containerTexture2_spec = loadDefaultTexture("container2_specular.jpg");

	TransformationMatrix view;
	TransformationMatrix projection;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Material crateMat(shaderProgram, containerTexture2, containerTexture2_spec, 64.0f);

	PointLight pointLight = PointLight(Position(0.0f, 1.5f, 1.0f), glm::vec3(1.0f), glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f), glm::vec3(1.0f, 0.09f, 0.032f));
	DirectionalLight sun = DirectionalLight(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(1.0f, 0.9f, 0.7f), glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f));
	SpotLight spotLight = SpotLight(Position(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f), 30.0f, glm::vec3(1.0f), glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f), glm::vec3(1.0f, 0.09f, 0.032f));

	LightSource cubeLight = LightSource(&spotLight, 36);
	cubeLight.setScale(0.25f);
	cubeLight.setIgnoreColor(true);

	Entity cubes[] = {
		Entity(Position(0.0f, 0.0f, 0.0f), 36, crateMat),
		Entity(Position(2.0f, -2.0f, -3.0f), 36, crateMat),
		Entity(Position(-2.0f, 1.0f, -7.0f), 36, crateMat),
		Entity(Position(3.0f, 2.0f, -1.0f), 36, crateMat),
		Entity(Position(1.0f, 6.0f, -6.0f), 36, crateMat),
		Entity(Position(3.0f, -1.0f, 3.0f), 36, crateMat),
		Entity(Position(-4.0f, 0.0f, 1.0f), 36, crateMat),
		Entity(Position(-2.0f, 1.5f, -3.0f), 36, crateMat),
		Entity(Position(-3.0f, -4.0f, 2.0f), 36, crateMat),
		Entity(Position(-5.0f, -1.0f, -3.0f), 36, crateMat)
	};
	// ----- GAMELOOP -----
	while (!glfwWindowShouldClose(window)) {
		// INPUT
		calculateDeltaTime();
		processInput(window);
		glfwGetWindowSize(window, &WIDTH, &HEIGHT);

		// CALC
		float sinusWave = sin(glfwGetTime()) * 10;
		float posSin = pow(sinusWave, 2);
		//cubeLight.translate(0.0f, 0.0f, sinusWave * 0.01f);

		TransformationMatrix view = camera.GetViewMatrix();
		projection.perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		
		shaderProgram.activate();
		shaderProgram.setFloat_3("viewPos", camera.Pos.getPosition());
		shaderProgram.setFloat_3("light.direction", camera.Front.getPosition());
		shaderProgram.stop();

		//RENDERING
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		shaderProgram.activate();

		view.makeViewMatrix(shaderProgram);
		projection.makeProjectionMatrix(shaderProgram);

		enableDepthTest();

		shaderProgram.stop();

		// RENDER LIGHTS
		lampProgram.activate();
		view.makeViewMatrix(lampProgram);
		projection.makeProjectionMatrix(lampProgram);

		bindVertexArray(lightVAO);
		enableAttribs(0);

		renderLightSource(cubeLight, lampProgram);

		disableAttribs(0);
		unbindVAO();

		lampProgram.stop();

		// RENDER OBJECTS
		shaderProgram.activate();
		bindVertexArray(objectVAO);
		enableAttribs(0, 2);

		for (unsigned int i = 0; i < 10; i++)
		{
			cubes[i].setRotation(20.0f * i, 12.0f * i, 10.0f * i);
			renderEntity(cubes[i], cubeLight.getLight(), shaderProgram);
		}

		disableAttribs(0, 2);
		unbindVAO();


		shaderProgram.stop();

		// EVENTS AND SWAP BUFFERS
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}
	// --------------------
	shaderProgram.cleanUp();
	lampProgram.cleanUp();
	cleanUp();

	writeInfo("Game terminated");

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void processInput(GLFWwindow *window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
		if (!wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			wireframe = true;
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			wireframe = false;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.ProcessKeyboard(UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera.ProcessKeyboard(DOWN, deltaTime);
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

void calculateDeltaTime() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}