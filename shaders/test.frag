#version 140 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main()
{
	// Object material
	vec3 objectColor = vec3(0.9f, 0.2f, 0.3f);
	
	// Light settings
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 lightDir = normalize(-vec3(-0.2f, -1.0f, -0.3f));
	float ambientStrength = 0.2f;
	
	// Ambient calculation
	vec3 ambient = ambientStrength * lightColor;
	
	// Diffuse calculation
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;
	
	// Output	
	vec3 result = (ambient + diffuse) * objectColor;
	FragColor = vec4(result, 1.0f);
}
