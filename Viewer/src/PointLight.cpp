#include "PointLight.h"
#include <algorithm>
#include "Scene.h"

PointLight::PointLight(std::string _name, MeshModel* meshPtr) : Light(_name, glm::vec3(1, 1, 1), meshPtr)
{
	position = glm::vec3(0, 0, 50);
}

float PointLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal, Scene* scene)
{
	Camera* cam = scene->GetActiveCamera();

	glm::vec3 LightDirection = -(currentPosition - point);
	glm::vec3 R = 2.0f * (glm::dot(LightDirection, normal)) * normal - LightDirection;
	glm::vec3 V = glm::normalize(cam->eye - point);
	R = glm::normalize(R);
	float dotProd = glm::max(glm::dot(V, R), 0.0f);
	float specular = pow(dotProd, a);

	float diffuse = glm::max(glm::dot(-glm::normalize(LightDirection), normal), 0.0f);

	return diffuseLevel * diffuse + specularLevel * specular;
}
