#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

extern bool failed;

void initGLFW();
GLFWwindow* createDisplay();
void loadGLAD();

#endif