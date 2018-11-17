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
	bool isPrespective = false;
	int activeCameraIndex;
	int activeModelIndex;
	bool isAddCamera = false, isShowNormals = false;
	GLfloat scaleNormalLength = 0.1;
	glm::vec4 modelColor = glm::vec4(100.8f, 0.8f, 0.8f, 1.00f);
	glm::vec4 normalsColor = glm::vec4(1.8f, 100.8f, 1.8f, 1.00f);
	glm::vec4 gridColor = glm::vec4(2.8f, 2.8f, 120.8f, 1.00f);
	glm::vec4 boundingBoxColor = glm::vec4(3.8f, 120.8f, 120.8f, 1.00f);
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
	std::vector<std::string> GetCameraNames();
	MeshModel* GetActiveModel();
	Camera* GetActiveCamera();
	// Add more methods as needed...
};