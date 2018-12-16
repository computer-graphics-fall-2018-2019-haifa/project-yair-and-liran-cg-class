#include "ParallelLight.h"
#include <glm/ext/quaternion_geometric.inl>

ParallelLight::ParallelLight(std::string _name): Light(_name)
{
	direction = glm::normalize(glm::vec3(0, 0, -50));
}

float ParallelLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal, glm::mat4x4 vertexTransformationMatrix)
{
	glm::vec4 newDirecation = glm::vec4(direction.x,direction.y,direction.z,1);
	newDirecation = vertexTransformationMatrix * newDirecation;
	glm::vec3 direct = glm::normalize(glm::vec3(newDirecation.x, newDirecation.y, newDirecation.z));
	float dotProduct = newDirecation.x*normal.x + newDirecation.y*normal.y + newDirecation.z*normal.z;
	if (dotProduct < 0)
		return 0;
	return L * (newDirecation.x*normal.x + newDirecation.y*normal.y + newDirecation.z*normal.z);
}
