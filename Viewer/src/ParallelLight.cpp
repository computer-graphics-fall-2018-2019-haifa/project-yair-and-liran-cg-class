#include "ParallelLight.h"
#include <algorithm>
#include "Scene.h"

ParallelLight::ParallelLight(std::string _name): Light(_name)
{
	direction = glm::normalize(glm::vec3(0, 0, 50));
}

float ParallelLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal,Scene* scene)
{
	Camera* cam = scene->GetActiveCamera();

	glm::vec3 LightDirection = -direction;
	glm::vec3 R = 2.0f * (glm::dot(LightDirection, normal)) * normal - LightDirection;
	glm::vec3 V = glm::normalize(cam->eye - point);
	R = glm::normalize(R);
	float dotProd = glm::max(glm::dot(V, R), 0.0f);
	float specular = pow(dotProd, a);

	float diffuse = glm::max(glm::dot(-glm::normalize(LightDirection), normal), 0.0f);

	return diffuseLevel * diffuse + specularLevel * specular;
}
