#version 430 core

out vec4 fragColor;

in vec4 iColor;
in vec3 iWorldNormal;
in vec3 iWorldPosition;

struct Camera
{
	vec3 worldPosition;
};

struct Material
{
	float ambient;
	float diffuse;
	float specular;
	float specularSmoothness;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 color;
};

uniform Material material;
uniform DirectionalLight light;
uniform Camera camera;

void main()
{
	vec3 ambient = material.ambient * iColor.rgb;
	vec3 diffuse = max(0, -dot(iWorldNormal, light.direction)) * light.color * iColor.rgb;
	
	vec3 worldEye = normalize(iWorldPosition - camera.worldPosition);
	vec3 h = dot(iWorldNormal, light.direction) * iWorldNormal;
	vec3 pprime = 2 * h - light.direction;
	vec3 specular = light.color * pow(max(0, dot(worldEye, pprime)), material.specularSmoothness) * material.specular;

	fragColor = vec4(ambient + diffuse + specular, 1.f);
}