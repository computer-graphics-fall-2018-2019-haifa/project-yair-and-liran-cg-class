#include "Light.h"
#ifndef __POINTLIGHT__
#define __POINTLIGHT__

class PointLight : public Light
{
public:
	PointLight::PointLight(std::string _name);

	float CalculateIllumination(glm::vec3 point, glm::vec3 normal);

};

#endif