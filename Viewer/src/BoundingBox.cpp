//#include "BoundingBox.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox(std::vector<glm::vec3>& vertices) //: MeshModel("")
{
	float minX = 100000000, maxX = -100000000, minY = 100000000, maxY = -100000000, minZ = 100000000, maxZ = -100000000;
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
	vertexes.push_back(glm::vec4(minX, minY, minZ, 1));
	vertexes.push_back(glm::vec4(maxX, minY, minZ, 1));
	vertexes.push_back(glm::vec4(maxX, minY, maxZ, 1));
	vertexes.push_back(glm::vec4(minX, minY, maxZ, 1));
	vertexes.push_back(glm::vec4(minX, maxY, minZ, 1));
	vertexes.push_back(glm::vec4(maxX, maxY, minZ, 1));
	vertexes.push_back(glm::vec4(maxX, maxY, maxZ, 1));
	vertexes.push_back(glm::vec4(minX, maxY, maxZ, 1));
	o = glm::vec4((minX + maxX) / 2, (minY + maxY) / 2, (minZ + maxZ) / 2, 1);
	x = glm::vec4(maxX, (minY + maxY) / 2, (minZ + maxZ) / 2, 1);
	y = glm::vec4((minX + maxX) / 2, maxY, (minZ + maxZ) / 2, 1);
	z = glm::vec4((minX + maxX) / 2, (minY + maxY) / 2, maxZ, 1);
}

std::vector<glm::vec4> BoundingBox::GetFinalVertexes(glm::mat4x4& vertexTransformationMatrix)
{
	std::vector<glm::vec4> finalVertexes;
	for (int i = 0; i < vertexes.size(); ++i)
	{
		finalVertexes.push_back(vertexTransformationMatrix * vertexes[i]);
	}
	return finalVertexes;
}

std::vector<glm::vec4> BoundingBox::TransformCoordinateSystem(glm::mat4x4& vertexTransformationMatrix)
{
	std::vector<glm::vec4> coordinateSystem;
	coordinateSystem.push_back(vertexTransformationMatrix * o);
	coordinateSystem.push_back(vertexTransformationMatrix * x);
	coordinateSystem.push_back(vertexTransformationMatrix * y);
	coordinateSystem.push_back(vertexTransformationMatrix * z);
	return coordinateSystem;
}
