#include "ParallelLight.h"

ParallelLight::ParallelLight(std::string _name): Light(_name)
{
	direction = glm::normalize(glm::vec3(0, 0, 50));
}

float ParallelLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal)
{
	float dotProduct = direction.x*normal.x + direction.y*normal.y + direction.z*normal.z;
	if (dotProduct < 0)
		return 0;
	float tmp = (direction.x*normal.x + direction.y*normal.y + direction.z*normal.z);
	return 10 * L * tmp;
}
