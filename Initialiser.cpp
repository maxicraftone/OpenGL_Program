#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Main.h"
#include "Logger.h"

static void glfwError(int id, const char* description);

bool failed = false;

void initGLFW() {
	glfwSetErrorCallback(&glfwError);
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif
}

GLFWwindow* createDisplay() {
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GAME", /*glfwGetPrimaryMonitor()*/NULL, NULL);

	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwSetWindowPos(window, vidmode->width / 2 - WIDTH / 2, vidmode->height / 2 - HEIGHT / 2);

	if (window == NULL)
	{
		writeError("Failed to create GLFW window.");
		glfwTerminate();
		failed = true;
	}
	else {
		writeInfo("GLFW window created.");
	}

	glfwMakeContextCurrent(window);
	return window;
}

void loadGLAD() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		writeError("Failed to initialize GLAD.");
		failed = true;
	}
	else {
		writeInfo("GLAD initialized.");
	}
}

static void glfwError(int id, const char* description)
{
	writeError(description);
}