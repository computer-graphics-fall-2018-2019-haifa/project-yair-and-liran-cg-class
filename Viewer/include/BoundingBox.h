#ifndef _BOUNDING_
#define _BOUNDING_
#include <glm/vec3.hpp>
#include <vector>
#include "MeshModel.h"

class BoundingBox : public MeshModel
{
public:
	float minX, maxX, minY, maxY, minZ, maxZ;
	glm::vec4 v1;
	glm::vec4 v2;
	glm::vec4 v3;
	glm::vec4 v4;
	glm::vec4 v5;
	glm::vec4 v6;
	glm::vec4 v7;
	glm::vec4 v8;
	BoundingBox(std::vector<glm::vec3> vertices);
};
#endif

