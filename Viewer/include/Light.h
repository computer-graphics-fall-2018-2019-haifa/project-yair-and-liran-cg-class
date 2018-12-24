#ifndef __LIGHT__
#define __LIGHT__
#include "MeshModel.h"

class Scene;

class Light : public MeshModel
{
public:
	Light(std::string _modelName, MeshModel* meshPtr) :  L(0.2), a(1),
	MeshModel(meshPtr->faces, meshPtr->vertices, meshPtr->faceNormals, _modelName) {}
	Light(std::string _modelName) : L(0.2), a(1), MeshModel(_modelName){}
	virtual float CalculateIllumination(glm::vec3 point, glm::vec3 normal, Scene* scene) = 0;
	float L;
	int a;
	glm::vec3 position, direction;
	glm::vec3 currentPosition, currentDirection;
};

#endif
