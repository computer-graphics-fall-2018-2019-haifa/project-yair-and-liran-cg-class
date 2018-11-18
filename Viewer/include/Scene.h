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



public:
	std::vector<Camera*> cameras;
	bool isPrespective = false;
	int activeCameraIndex;
	int activeModelIndex;
	bool isAddCamera = false, isShowFaceNormals = false, isShowVertexNormals = false;
	float camScale = 1, zoom = 1;
	GLfloat scaleNormalLength = 0.1;
	glm::vec4 modelColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.00f);
	glm::vec4 normalsColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.00f);
	glm::vec4 gridColor = glm::vec4(0.125f, 0.125f, 0.25f, 1.00f);
	glm::vec4 boundingBoxColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.00f);
	glm::vec4 beackgroundColor = glm::vec4(0.137f, 0.535f, 0.7f, 1.00f);

	Scene();

	void AddModel(MeshModel* model);
	const int GetModelCount() const;

	void AddNewCamera(glm::vec3 eye = glm::vec3(0, -500, 500), glm::vec3 at = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0, 1, 1));
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
	glm::mat4x4 GetCameraScalingMatrix();
	// Add more methods as needed...
};