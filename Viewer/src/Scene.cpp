#include "Scene.h"
#include "MeshModel.h"
#include <string>
#include "Utils.h"
#include "ParallelLight.h"
#include "PointLight.h"

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{

}

void Scene::AddModel(MeshModel* model)
{
	models.push_back(model);
}

void Scene::AddLight(Light* light)
{
	lights.push_back(light);
}

const int Scene::GetModelCount() const
{
	return models.size();
}

const int Scene::GetLightCount() const
{
	return lights.size();
}

void Scene::AddNewCamera(glm::vec3 eye, glm::vec3 at, glm::vec3 up)
{
	std::string cameraPath = "..\\Data\\camera.obj";
	MeshModel* meshPtr = Utils::LoadMeshModel(cameraPath);
	glm::mat4x4 _rotataionYmatrix
	{ glm::cos(1.57)			,	0	,	glm::sin(1.57)	,	0,
		0							,	1	,				0					,	0,
		-1 * glm::sin(1.57)	,	0	,	glm::cos(1.57)	,	0,
		0										,	0	,				0					,	1 };

	for(int i=0 ; i<meshPtr->vertices.size() ; i++)
	{
		glm::vec4 tmp = _rotataionYmatrix * glm::vec4(meshPtr->vertices[i][0], meshPtr->vertices[i][1], meshPtr->vertices[i][2], 1);
		meshPtr->vertices[i] = glm::vec3(tmp[0], tmp[1], tmp[2]);
	}
	Camera* camera = new Camera(eye, at, up, cameras.size(), meshPtr);
	camera->param->scale_x = 20;
	camera->param->scale_y = 20;
	camera->param->scale_z = 20;
	cameras.push_back(camera);

}

void Scene::AddNewParallelLight()
{
	std::string lightPath = "..\\Data\\obj_examples\\sun.obj";
	MeshModel* meshPtr = Utils::LoadMeshModel(lightPath);
	Light* light = new ParallelLight("ParallelLight " + std::to_string(lights.size()), meshPtr);
	light->param->scale_x = 20;
	light->param->scale_y = 20;
	light->param->scale_z = 20;
	lights.push_back(light);
	if (lights.size() == 1)
		SetActiveLightIndex(0);
	
}

void Scene::AddNewPointLight()
{
	std::string lightPath = "..\\Data\\obj_examples\\bulb.obj";
	MeshModel* meshPtr = Utils::LoadMeshModel(lightPath);
	Light* light = new PointLight("PointLight" + std::to_string(lights.size()), meshPtr);
	light->param->scale_x = 10;
	light->param->scale_y = 10;
	light->param->scale_z = 10;
	lights.push_back(light);
	if (lights.size() == 1)
		SetActiveLightIndex(0);
}


const int Scene::GetCameraCount() const
{
	return cameras.size();
}

void Scene::SetActiveCameraIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < cameras.size())
	{
		activeCameraIndex = index;
	}
}

void Scene::SetActiveLightIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < lights.size())
	{
		activeLightIndex = index;
	}
}

const int Scene::GetActiveCameraIndex() const
{
	return activeCameraIndex;
}

const int Scene::GetActiveLightIndex() const
{
	return activeLightIndex;
}

void Scene::SetActiveModelIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < models.size())
	{
		activeModelIndex = index;
	}
}

const int Scene::GetActiveModelIndex() const
{
	return activeModelIndex;
}

MeshModel* Scene::GetModelByIndex(int index)
{
	return models[index];
}

Light* Scene::GetLightByIndex(int index)
{
	return lights[index];
}

Camera* Scene::GetCameraByIndex(int cameraIndex)
{
	return cameras[cameraIndex];
}

std::vector<std::string> Scene::getModelNames()
{
	std::vector<std::string> names;
	for (int i = 0; i < models.size(); ++i)
	{
		names.push_back(models[i]->GetName());
	}
	return names;
}

std::vector<std::string> Scene::getLightNames()
{
	std::vector<std::string> names;
	for (int i = 0; i < lights.size(); ++i)
	{
		names.push_back(lights[i]->GetName());
	}
	return names;
}

std::vector<std::string> Scene::GetCameraNames()
{
	std::vector<std::string> names;
	for (int i = 0; i < GetCameraCount(); ++i)
	{
		names.push_back(cameras[i]->GetName());
	}
	return names;
}

MeshModel* Scene::GetActiveModel()
{
	return models[activeModelIndex];
}

Camera* Scene::GetActiveCamera()
{
	return cameras[activeCameraIndex];
}

Light* Scene::GetActiveLight()
{
	return lights[activeLightIndex];
}

glm::mat4x4 Scene::GetCameraScalingMatrix()
{
	glm::mat4x4 C
	{ camScale,  0 ,  0 ,  0,
		0 ,  camScale,  0 ,  0,
		0 ,  0 ,  camScale,  0,
		0 ,  0 ,  0 ,  1 };
	return C;
}

void Scene::SetActiveCameraFinalTransformation()
{
	//Camera* cam = GetActiveCamera();
	//glm::mat4x4 trans = glm::inverse(cam->GetViewTransformation());
	//glm::mat4x4 rot = glm::inverse(cam->tm->rotataionXmatrix * cam->tm->rotataionYmatrix * cam->tm->rotataionZmatrix);
	//glm::mat4x4 cameraViewingTransform = cam->GetViewTransformation();
	//glm::mat4x4 cameraViewingTransformInverse = glm::inverse(cameraViewingTransform);

	//for (int i = 0; i < lights.size(); ++i)
	//{
	//	Light* currentLight = lights[i];
	//	glm::mat4x4 vertexTransformationMatrix =
	//		cameraViewingTransformInverse *
	//		currentLight->GetWorldTransformation();
	//	glm::vec3 pos = currentLight->position;
	//	glm::vec3 dir = currentLight->direction;
	//	currentLight->currentPosition = vertexTransformationMatrix * glm::vec4(pos.x, pos.y, pos.z, 1);
	//	currentLight->currentDirection = vertexTransformationMatrix * glm::vec4(dir.x, dir.y, dir.z, 1);
	//}
}
