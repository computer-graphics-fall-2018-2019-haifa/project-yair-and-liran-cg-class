#include "Light.h"
#ifndef __PARALLELLIGHT__
#define __PARALLELLIGHT__

class Scene;

class ParallelLight : public Light
{
public:
	ParallelLight::ParallelLight(std::string _name);
	float CalculateIllumination(glm::vec3 point, glm::vec3 normal, Scene* scene);
};

#endif