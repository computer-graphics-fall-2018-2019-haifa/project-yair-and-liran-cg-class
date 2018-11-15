#ifndef _BOUNDING_
#define _BOUNDING_
#include <glm/glm.hpp>
#include <vector>
//#include "MeshModel.h"

class BoundingBox //: public MeshModel
{
public:
	std::vector<glm::vec4> vertexes;
	glm::vec4 o, x, y, z;
	BoundingBox(std::vector<glm::vec3>& vertices);
	std::vector<glm::vec4> GetFinalVertexes(glm::mat4x4& vertexTransformationMatrix);
	std::vector<glm::vec4> TransformCoordinateSystem(glm::mat4x4& vertexTransformationMatrix);
};
#endif

