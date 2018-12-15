#include "Light.h"
#ifndef __PARALLELLIGHT__
#define __PARALLELLIGHT__

class ParallelLight : public Light
{
public:
	ParallelLight::ParallelLight(std::string _name, glm::vec3 _direction);
	float CalculateIllumination(glm::vec3 point, glm::vec3 normal);
	glm::vec3 Direction;
};

#endif