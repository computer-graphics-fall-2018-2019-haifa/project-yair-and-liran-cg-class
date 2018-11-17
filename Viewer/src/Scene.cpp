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
	std::string cameraPath = "C:\\computer_graphics\\project-yair-and-liran-cg-class\\Data\\obj_examples\\camera.obj";
	MeshModel* meshPtr = Utils::LoadMeshModel(cameraPath);
	Camera* camera = new Camera(eye, at, up, cameras.size(), meshPtr);
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
