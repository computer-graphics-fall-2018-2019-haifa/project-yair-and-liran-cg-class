#include "Light.h"

Light::Light(std::string _modelName) : MeshModel(_modelName)
{
}

float Light::CalculateIllumination(glm::vec3 point, glm::vec3 normal)
{
	//TODO
	return 0;
}
