#include "PointLight.h"

PointLight::PointLight(std::string _name) : Light(_name)
{
}

float PointLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal)
{
	//TODO
	return 0;
}
