#pragma once
#include <memory>
#include <vector>
#include <string>
#include <glm/glm.hpp>

class Face
{
private:


public:
	std::vector<int> vertexIndices;
	std::vector<int> normalIndices;
	std::vector<int> textureIndices;
	Face(std::istream& issLine);
	virtual ~Face();
	const int Face::GetVertexIndex(int index);
	const int Face::GetNormalIndex(int index);
	const int Face::GetTextureIndex(int index);
};