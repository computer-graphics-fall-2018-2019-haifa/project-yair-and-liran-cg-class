#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "MeshModel.h"
#include "Camera.h"

/*
 * Scene class.
 * This class holds all the scene information (models, cameras, lights, etc..)
 */
class Scene {
private:
	std::vector<MeshModel*> models;
	std::vector<Camera*> cameras;
public:
	int activeCameraIndex;
	int activeModelIndex;
	Scene();

	void AddModel(MeshModel* model);
	const int GetModelCount() const;

	void AddCamera(Camera* camera);
	const int GetCameraCount() const;

	void SetActiveCameraIndex(int index);
	const int GetActiveCameraIndex() const;

	void SetActiveModelIndex(int index);
	const int GetActiveModelIndex() const;


	MeshModel* GetModelByIndex(int index);
	Camera* GetCameraByIndex(int cameraIndex);
	std::vector<std::string> getModelNames();
	MeshModel* GetActiveModel();
	Camera* GetActiveCamera();
	// Add more methods as needed...
};