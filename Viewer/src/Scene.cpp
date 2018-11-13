#include "Scene.h"
#include "MeshModel.h"
#include <string>

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

void Scene::AddCamera(Camera* camera)
{
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
	for (int i=0; i< GetCameraCount() ; ++i)
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
