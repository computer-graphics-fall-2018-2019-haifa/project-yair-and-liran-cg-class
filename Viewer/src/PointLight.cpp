#include "PointLight.h"
#include <algorithm>
#include "Scene.h"

PointLight::PointLight(std::string _name) : Light(_name)
{
	position = glm::vec3(0, 0, 50);
}

float PointLight::CalculateIllumination(glm::vec3 point, glm::vec3 normal, Scene* scene)
{

	Camera* cam = scene->GetActiveCamera();
	glm::mat4x4 trans = GetWorldTransformation();
	glm::mat4x4 cameraViewingTransform = cam->GetViewTransformation();
	glm::mat4x4 cameraViewingTransformInverse = glm::inverse(cameraViewingTransform);
	glm::mat4x4 vertexTransformationMatrix =
		cameraViewingTransformInverse *
		GetWorldTransformation();
	glm::vec3 newPos = vertexTransformationMatrix * glm::vec4(position.x,position.y,position.z,1);

	glm::vec3 pos = newPos;
	glm::vec3 Lpoint = glm::normalize(pos);
	glm::vec3 R = glm::dot(Lpoint, normal)*normal + glm::dot(Lpoint, normal)*normal - Lpoint;
	R = glm::normalize(R);
	//glm::vec3 V = glm::normalize(cam->eye - point);
	glm::vec3 V = point-cam->eye;

	float specular = pow(((R.x*V.x) + (R.y*V.y) + (R.z*V.z)), a);

	glm::vec3 _l = glm::normalize(newPos - point);
	float tmp = (_l.x*normal.x + _l.y*normal.y + _l.z*normal.z);

	//specular = std::max(0.0f, specular);

	return L * (tmp +  specular);
}
