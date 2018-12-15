#include "ParallelLight.h"

ParallelLight::ParallelLight(std::string _name, glm::vec3 _direction): Light(_name)
{
	this->Direction = _direction;
}

float ParallelLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal)
{
	//TODO
	return 0;
}
