#include "Scene.h"
#include "MeshModel.h"
#include <string>
#include "Utils.h"

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{

}

void Scene::AddModel(MeshModel* model)
{
	models.push_back(model);
}

const int Scene::GetModelCount() const
{
	return models.size();
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

const int Scene::GetActiveCameraIndex() const
{
	return activeCameraIndex;
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

glm::mat4x4 Scene::GetCameraScalingMatrix()
{
	glm::mat4x4 C
	{ camScale,  0 ,  0 ,  0,
		0 ,  camScale,  0 ,  0,
		0 ,  0 ,  camScale,  0,
		0 ,  0 ,  0 ,  1 };
	return C;
}
