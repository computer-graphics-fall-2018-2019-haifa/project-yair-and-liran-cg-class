#include "Light.h"
#ifndef __POINTLIGHT__
#define __POINTLIGHT__

class Scene;

class PointLight : public Light
{
public:
	PointLight::PointLight(std::string _name, MeshModel* meshPtr);
	float CalculateIllumination(glm::vec3 point, glm::vec3 normal, Scene* scene);
};

#endif