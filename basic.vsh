#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 modelMatrix;
uniform mat4 modelMatrix_inversed;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 lightPos;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
	FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
	Normal = mat3(transpose(modelMatrix_inversed)) * aNormal;
	TexCoord = aTexCoord;
}