#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW\glfw3.h>

#include "Entity.h"
#include "ShaderProgram.h"

void renderLightSource(LightSource l, ShaderProgram shaderProgram);
void renderEntity(Entity e, Light *l, ShaderProgram shaderProgram);

#endif