#ifndef __LIGHT__
#define __LIGHT__
#include "MeshModel.h"

class Scene;

class Light : public MeshModel
{
public:
	Light(std::string _modelName, glm::vec3 color, MeshModel* meshPtr) :   colorVector(color),
	MeshModel(meshPtr->faces, meshPtr->vertices, meshPtr->faceNormals, _modelName) {}
	Light(std::string _modelName) : MeshModel(_modelName){}
	virtual float CalculateIllumination(glm::vec3 point, glm::vec3 normal, Scene* scene) = 0;
	float specularLevel = 0.5, diffuseLevel = 0.5;
	int a=1;
	glm::vec3 position, direction;
	glm::vec3 currentPosition, currentDirection;
	glm::vec3 colorVector = glm::vec3(1, 1, 1);
};

#endif
