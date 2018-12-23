#include "ParallelLight.h"
#include <algorithm>
#include "Scene.h"

ParallelLight::ParallelLight(std::string _name): Light(_name)
{
	direction = glm::normalize(glm::vec3(0, 0, 50));
}

float ParallelLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal,Scene* scene)
{
	glm::vec4 newDirection = glm::vec4(direction.x, direction.y, direction.z, 1);
	Camera* cam = scene->GetActiveCamera();
	glm::mat4x4 trans = GetWorldTransformation();
	//glm::mat4x4 camTrans = cam ->
	glm::mat4x4 cameraViewingTransform = cam->GetViewTransformation();
	glm::mat4x4 cameraViewingTransformInverse = glm::inverse(cameraViewingTransform);
	glm::mat4x4 vertexTransformationMatrix =
		cameraViewingTransformInverse *
		GetWorldTransformation();
	newDirection = vertexTransformationMatrix * newDirection;
	float dotProduct = direction.x*normal.x + direction.y*normal.y + direction.z*normal.z;
	if (dotProduct < 0)
		return 0;
	float tmp = (direction.x*normal.x + direction.y*normal.y + direction.z*normal.z);


	glm::vec3 Lpoint =  glm::normalize(direction);
	glm::vec3 R = glm::dot(Lpoint,normal)*normal + glm::dot(Lpoint,normal)*normal - Lpoint;
	R = glm::normalize(R);
	
	//glm::vec3 V = glm::normalize(cam->eye - point);
	glm::vec3 V = cam->eye - point;
	float specular = pow(((R.x*V.x) + (R.y*V.y) + (R.z*V.z)), a);

	//specular = std::max(0.0f, specular);

	return L * tmp + L*specular;
}
