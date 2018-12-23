#ifndef __LIGHT__
#define __LIGHT__
#include "MeshModel.h"

class Scene;

class Light : public MeshModel
{
public:
	Light(std::string _modelName) : MeshModel(_modelName), L(0.2),a(1) {}
	virtual float CalculateIllumination(glm::vec3 point, glm::vec3 normal, Scene* scene) = 0;
	float L;
	float a;
	glm::vec3 position, direction;
};

#endif
