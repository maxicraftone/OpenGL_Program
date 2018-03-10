#version 410 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

struct Material {
	sampler2D diffuse;
    sampler2D specular;
    float shininess; // 64.0
}; 

uniform Material material;

struct Light {
    vec3 position; // 0.0, 0.0, 2.0
	vec3 direction; // 0.0, 0.0, -1.0
	vec3 color; // 1.0, 1.0, 1.0
	
	float cutoff; // 30.0

    vec3 ambient; // 0.2, 0.2, 0.2
    vec3 diffuse; // 0.5, 0.5, 0.5
    vec3 specular; // 1.0

	float constant; // 1.0
    float linear; // 0.09
    float quadratic; // 0.032
};

uniform Light light;

uniform vec3 viewPos;

void main()
{
	vec3 material_diffuse = vec3(texture(material.specular, TexCoord));
	vec3 lightDirection;

	if (light.direction != vec3(0.0) && light.cutoff == 0.0) {
		lightDirection = normalize(-light.direction);
	} else {
		lightDirection = normalize(light.position - FragPos);
	}

	vec3 normal = normalize(Normal);
	float difference = max(dot(normal, lightDirection), 0.0);

	vec3 viewDirection = normalize(viewPos - FragPos);
	vec3 lightReflection = reflect(-lightDirection, normal);
	float spec = pow(max(dot(viewDirection, lightReflection), 0.0), material.shininess);

	vec3 ambient  = light.color * light.ambient * material_diffuse;
	vec3 diffuse  = light.color * light.diffuse * difference * material_diffuse;  
	vec3 specular = light.color * light.specular * spec * vec3(texture(material.specular, TexCoord));

	float distance = 0.0;

	if (light.direction == vec3(0.0) || light.cutoff != 0.0) {
		distance = length(light.position - FragPos);
	}  

	float att = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient *= att;
	diffuse *= att;
	specular *= att;

	vec3 result;

	if (light.cutoff > 0.0f) {
		float theta = dot(lightDirection, normalize(-light.direction));

		if (theta > light.cutoff) {
			result = ambient + diffuse + specular;
		} else {
			result = ambient;
		}
	} else {
		result = ambient + diffuse + specular;
	}

    FragColor = vec4(result, 1.0);
}