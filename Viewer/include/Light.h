#ifndef __LIGHT__
#define __LIGHT__
#include "MeshModel.h"

class Light : public MeshModel
{
public:

	Light(std::string _modelName);
	virtual float CalculateIllumination(glm::vec3 point, glm::vec3 normal);

};

#endif
