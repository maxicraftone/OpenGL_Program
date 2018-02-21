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
#include "Joystick.h"
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

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
};

float vertices2[] = {
	-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f , 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
};

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
void processJoystickInput(GLFWwindow* window);
void processJoystickMovement();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void joystick_callback(int joystick, int event);
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
Joystick joystick = Joystick(GLFW_JOYSTICK_1);

int main() {
	initGLFW();
	GLFWwindow* window = createDisplay();
	loadGLAD();

	if (failed)
		return -1;

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetJoystickCallback(joystick_callback);

	ShaderProgram shaderProgram = ShaderProgram("basic.vsh", "basic.fsh");
	shaderProgram.linkProgram();
	ShaderProgram lampProgram = ShaderProgram("lamp.vsh", "lamp.fsh");
	lampProgram.linkProgram();

	unsigned int objectVAO = createAndBindVAO();
	storeDataInAttributeList(0, 3, ownCube, sizeof(vertices), 8, 0);
	storeDataInAttributeList(1, 3, ownCube, sizeof(vertices), 8, 3 * sizeof(float));
	storeDataInAttributeList(2, 3, ownCube, sizeof(vertices), 8, 6 * sizeof(float));
	unbindVAO();

	unsigned int planeVAO = createAndBindVAO();
	storeDataInAttributeList(0, 3, vertices3, sizeof(vertices), 8, 0);
	storeDataInAttributeList(1, 3, vertices3, sizeof(vertices), 8, 3 * sizeof(float));
	storeDataInAttributeList(2, 3, vertices3, sizeof(vertices), 8, 6 * sizeof(float));
	unbindVAO();

	unsigned int lightVAO = createAndBindVAO();
	storeDataInAttributeList(0, 3, vertices, sizeof(vertices), 8, 0);
	unbindVAO();

	unsigned int wallTexture = loadDefaultTexture("wall.jpg");
	unsigned int containerTexture = loadDefaultTexture("container.jpg");
	unsigned int containerTexture2 = loadDefaultTexture("container2.jpg");
	unsigned int clayTexture = loadDefaultTexture("clay.jpg");

	shaderProgram.activate();

	shaderProgram.setInt_1("material.diffuse", 0);

	TransformationMatrix view;
	TransformationMatrix projection;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	int joystick = glfwJoystickPresent(GLFW_JOYSTICK_1);
	writeInfo("Controller ID 0 active: " + std::to_string(joystick));
	if (joystick == 0)
		controllerUsed = false;
	else
		controllerUsed = true;
	if (controllerUsed) {
		std::string name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		writeInfo("Name of controller ID 0: " + name);
	}

	Material coral = Material(glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 0.25f);

	LightSource cubeLight = LightSource(Light(Position(0.0f, 0.5f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.2f)), 36);
	cubeLight.setScale(0.25f);
	cubeLight.setIgnoreColor(true);

	Entity cube = Entity(Position(0.0f, 0.0f, 0.0f), 30, coral);
	Entity plane(Position(glm::vec3(0.0f)), 6, coral);
	// ----- GAMELOOP -----
	while (!glfwWindowShouldClose(window)) {
		// INPUT
		calculateDeltaTime();
		processInput(window);
		glfwGetWindowSize(window, &WIDTH, &HEIGHT);

		// CALC
		float sinusWave = sin(glfwGetTime());
		cubeLight.translate(0.0f, sinusWave * 0.01f, 0.0f);

		TransformationMatrix view = camera.GetViewMatrix();
		projection.perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
		
		shaderProgram.activate();
		shaderProgram.setFloat_3("viewPos", camera.Pos.getPosition());
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
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, containerTexture2);

		renderEntity(cube, cubeLight.getLight(), shaderProgram);

		disableAttribs(0, 2);
		unbindVAO();

		bindVertexArray(planeVAO);
		enableAttribs(0, 2);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, containerTexture2);

		renderEntity(plane, cubeLight.getLight(), shaderProgram);

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
	if(controllerUsed)
		processJoystickInput(window);

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

void processJoystickInput(GLFWwindow* window) {

	processJoystickMovement();

	if (joystick.buttonPressed(BUTTON_START))
		glfwSetWindowShouldClose(window, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

void joystick_callback(int joystick, int event) {
	if (event == GLFW_CONNECTED) {
		std::string name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		writeInfo("Joystick " + name + " with id " + std::to_string(joystick) + " connected");
	}
	else if (event == GLFW_DISCONNECTED) {
		writeInfo("Joystick with id " + std::to_string(joystick) + " disconnected");
	}
}

void processJoystickMovement() {
	if (joystick.axisUsed(AXIS_LS_VERTICAL))
		camera.ProcessJoystick(FORWARD, deltaTime, joystick.getAxisValue(AXIS_LS_VERTICAL));
	if (joystick.axisUsed(AXIS_LS_HORIZONTAL))
		camera.ProcessJoystick(RIGHT, deltaTime, joystick.getAxisValue(AXIS_LS_HORIZONTAL));

	if (joystick.axisUsed(AXIS_RS_VERTICAL))
		camera.ProcessMouseMovement(0.0f, joystick.getAxisValue(AXIS_RS_VERTICAL) * 20);
	if (joystick.axisUsed(AXIS_RS_HORIZONTAL))
		camera.ProcessMouseMovement(joystick.getAxisValue(AXIS_RS_HORIZONTAL) * 20, 0.0f);

	if (joystick.axisUsed(AXIS_LT))
		camera.ProcessMouseScroll(-(joystick.getAxisValue(AXIS_LT) + 1) / 4);
	if (joystick.axisUsed(AXIS_RT))
		camera.ProcessMouseScroll((joystick.getAxisValue(AXIS_RT) + 1) / 4);
}

void calculateDeltaTime() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}