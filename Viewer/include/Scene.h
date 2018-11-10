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
	std::vector<std::shared_ptr<MeshModel>> models;
	std::vector<Camera> cameras;

	int activeCameraIndex;
	

public:
	int activeModelIndex;
	Scene();

	void AddModel(const std::shared_ptr<MeshModel>& model);
	const int GetModelCount() const;

	void AddCamera(const Camera& camera);
	const int GetCameraCount() const;

	void SetActiveCameraIndex(int index);
	const int GetActiveCameraIndex() const;

	void SetActiveModelIndex(int index);
	const int GetActiveModelIndex() const;


	std::shared_ptr<MeshModel> GetModelByIndex(int index);
	Camera GetCameraByIndex(int cameraIndex);
	std::vector<std::string> getModelNames();
	std::shared_ptr<MeshModel> GetActiveModel();
	// Add more methods as needed...
};