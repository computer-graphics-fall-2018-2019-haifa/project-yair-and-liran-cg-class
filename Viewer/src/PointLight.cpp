#include "PointLight.h"

PointLight::PointLight(std::string _name) : Light(_name)
{
	position = glm::vec3(0, 0, 50);
}

float PointLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal, glm::mat4x4 vertexTransformationMatrix)
{
	glm::vec4 pos = glm::vec4(position.x, position.y, position.z, 1);
	pos = vertexTransformationMatrix * pos;
	glm::vec3 newPos = glm::vec3(pos.x, pos.y, pos.z);
	glm::vec3 _l = glm::normalize(point- newPos);
	return L * (_l.x*normal.x + _l.y*normal.y + _l.z*normal.z);
}
