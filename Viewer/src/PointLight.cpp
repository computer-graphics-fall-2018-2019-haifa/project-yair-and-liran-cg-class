#include "PointLight.h"
#include <algorithm>
#include "Scene.h"

PointLight::PointLight(std::string _name, MeshModel* meshPtr) : Light(_name, meshPtr)
{
	position = glm::vec3(0, 0, 50);
}

float PointLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal, Scene* scene)
{
	normal = glm::normalize(normal);
	Camera* cam = scene->GetActiveCamera();
	/*glm::mat4x4 cameraTransformationMatrix = cam->GetViewTransformation();
	glm::mat4x4 cameraTransformationMatrixInverse = glm::inverse(cameraTransformationMatrix);
	glm::mat4x4 lightTransformationMatrix = 
		cameraTransformationMatrixInverse *
		GetWorldTransformation();

	glm::vec3 newLightPosition = lightTransformationMatrix * glm::vec4(position.x, position.y, position.z, 1);
	*/
	glm::vec3 LightDirection = glm::normalize(currentPosition - point);
	glm::vec3 R = (2 * (LightDirection[0] * normal[0] + LightDirection[1] * normal[1] + LightDirection[2] * normal[2]))*normal - LightDirection;
	R = glm::normalize(R);
	glm::vec3 V = glm::normalize(cam->eye - point);
	float specular = pow(((R.x*V.x) + (R.y*V.y) + (R.z*V.z)), a);

	glm::vec3 _l = glm::normalize(currentPosition - point);
	float tmp = (_l.x*normal.x + _l.y*normal.y + _l.z*normal.z);

	//specular = std::max(0.0f, specular);

	return L * (tmp + specular);
}
