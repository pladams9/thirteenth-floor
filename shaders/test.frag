#version 140 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float specular_power;
};

uniform Material material;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main()
{
	// Light settings
	vec3 lightAmbient = vec3(0.5f, 0.5f, 0.5f);
	vec3 lightDiffuse = vec3(0.7f, 0.7f, 0.7f);
	vec3 lightSpec = vec3(1.0f, 1.0f, 1.0f);
	vec3 lightDir = normalize(-vec3(-0.2f, -1.0f, -0.3f));
	
	// Ambient calculation
	vec3 ambient = material.ambient * lightAmbient;
	
	// Diffuse calculation
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = lightDiffuse * (diff * material.diffuse);
	
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.specular_power);
    vec3 specular = lightSpec * (spec * material.specular);  
	
	// Output	
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0f);
}
