#include "Light.h"
#ifndef __PARALLELLIGHT__
#define __PARALLELLIGHT__

class ParallelLight : public Light
{
public:
	ParallelLight::ParallelLight(std::string _name);
	float CalculateIllumination(glm::vec3 point, glm::vec3 normal, glm::mat4x4 vertexTransformationMatrix);
};

#endif