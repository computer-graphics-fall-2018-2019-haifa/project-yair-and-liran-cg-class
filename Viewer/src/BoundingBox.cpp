#include "BoundingBox.h"

BoundingBox::BoundingBox(std::vector<glm::vec3> vertices): MeshModel("")
{
	minX = 100000000 , maxX = -100000000 , minY = 100000000 , maxY = -100000000 , minZ = 100000000 , maxZ = -100000000;
	for (int i = 0; i < vertices.size(); ++i)
	{
		if (vertices[i][0] < minX)
			minX = vertices[i][0];
		if (vertices[i][0] > maxX)
			maxX = vertices[i][0];
		if (vertices[i][1] < minY)
			minY = vertices[i][1];
		if (vertices[i][1] > maxY)
			maxY = vertices[i][1];
		if (vertices[i][2] < minZ)
			minZ = vertices[i][2];
		if (vertices[i][2] > maxZ)
			maxZ = vertices[i][2];
	}

	glm::vec4 v1 = ;
	glm::vec4 v2();
	glm::vec4 v3();
	glm::vec4 v4();
	glm::vec4 v5();
	glm::vec4 v6();
	glm::vec4 v7();
	glm::vec4 v8();
}
