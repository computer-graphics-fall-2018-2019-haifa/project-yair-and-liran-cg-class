#include "PointLight.h"
#include <algorithm>
#include "Scene.h"

PointLight::PointLight(std::string _name, MeshModel* meshPtr) : Light(_name, meshPtr)
{
	position = glm::vec3(0, 0, 50);
}

float PointLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal, Scene* scene)
{
	Camera* cam = scene->GetActiveCamera();
	
	//glm::vec3 l = currentPosition;
	glm::vec3 LightDirection = -glm::normalize(point - currentPosition);
	glm::vec3 R = 2.0f * (glm::dot(normal, LightDirection)) - LightDirection;
	glm::vec3 V = - glm::normalize(point - cam->eye);
	

	float specular = pow(glm::dot(V,R), a);

	glm::vec3 _l = glm::normalize(point - currentPosition);
	float tmp = glm::max((_l.x*normal.x + _l.y*normal.y + _l.z*normal.z),0.0f);

	//specular = std::max(0.0f, specular);
	return L * (tmp + specular);
}
