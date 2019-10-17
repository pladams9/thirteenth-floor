#version 140 core


// STRUCTS
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float rough;
};

struct DirLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 direction;
};

struct PointLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;
};


// CONSTANTS
#define NUM_DIR_LIGHTS 2
#define NUM_POINT_LIGHTS 4


// UNIFORMS
uniform Material material;
uniform vec3 viewPos;
uniform DirLight dirLights[NUM_DIR_LIGHTS];
uniform PointLight pointLights[NUM_POINT_LIGHTS];


// IN VARS
in vec3 FragPos;
in vec3 Normal;


// OUT VARS
out vec4 FragColor;


// FUNCTION PROTOTYPES
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

// MAIN
void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	vec3 result = vec3(0, 0, 0);
    
	for(int i = 0; i < NUM_DIR_LIGHTS; i++)
		result += CalcDirLight(dirLights[i], norm, viewDir);

	for(int i = 0; i < NUM_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}


// FUNCTION DEFINITIONS
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	
	// AMBIENT
	vec3 ambient = light.ambient * material.ambient;

	// DIFFUSE
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * material.diffuse;

	// SPECULAR
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.rough);
	vec3 specular = light.specular * spec * material.specular;

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	// AMBIENT
	vec3 ambient = light.ambient * material.ambient;

	// DIFFUSE
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * material.diffuse;

	// SPECULAR
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.rough);
	vec3 specular = light.specular * spec * material.specular;

	// ATTENUATION
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
    
	return (ambient + diffuse + specular);
}
