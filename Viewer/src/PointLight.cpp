#include "PointLight.h"

PointLight::PointLight(std::string _name) : Light(_name)
{
	position = glm::vec3(0, 0, 50);
}

float PointLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal)
{
	glm::vec3 _l = glm::normalize(position-point);
	float tmp = (_l.x*normal.x + _l.y*normal.y + _l.z*normal.z);
	return L * tmp;
}
