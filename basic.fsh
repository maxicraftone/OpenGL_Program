#version 410 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

struct Material {
	sampler2D diffuse;
    vec3 specular;
    float shininess;
}; 

uniform Material material;

struct Light {
    vec3 position;
	vec3 color;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform vec3 viewPos;

void main()
{
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(light.position - FragPos);
	float difference = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = difference * vec3(texture(material.diffuse, TexCoord)) * light.diffuse * light.color;

	vec3 viewDirection = normalize(viewPos - FragPos);
	vec3 lightReflection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, lightReflection), 0.0), material.shininess * 128);
	vec3 specular = material.specular * spec * light.specular * light.color;  

    vec3 ambient = vec3(texture(material.diffuse, TexCoord)) * light.ambient * light.color;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}