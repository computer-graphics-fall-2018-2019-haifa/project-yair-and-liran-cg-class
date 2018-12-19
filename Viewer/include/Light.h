#ifndef __LIGHT__
#define __LIGHT__
#include "MeshModel.h"

class Light : public MeshModel
{
public:
	Light(std::string _modelName) : MeshModel(_modelName), L(1) {}
	virtual float CalculateIllumination(glm::vec3 point, glm::vec3 normal) = 0;
	float L;
	glm::vec3 position, direction;
};

#endif
