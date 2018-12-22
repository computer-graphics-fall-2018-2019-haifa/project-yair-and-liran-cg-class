#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "MeshModel.h"
#include "Camera.h"
#include "Light.h"

/*
 * Scene class.
 * This class holds all the scene information (models, cameras, lights, etc..)
 */
class Scene {
private:
	std::vector<MeshModel*> models;



public:
	enum ShadingMode { Flat, Gouraud, Phong};
	ShadingMode shadingMode = Flat;
	std::vector<Light*> lights;
	std::vector<Camera*> cameras;
	bool isPrespective = false;
	int activeCameraIndex;
	int activeLightIndex;
	int activeModelIndex;
	bool isAddCamera = false, isShowFaceNormals = false, isShowVertexNormals = false, isShowBoundingBox = false;
	bool isAddLight = false, isAddParallelLight = false, isAddPointLight = false;
	float camScale = 1, zoom = 1;
	float ambientLevel = 0.5;
	GLfloat scaleNormalLength = 0.1;
	glm::vec3 edgesColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 facesColor = glm::vec3(0.144f, 0.515f, 0.5f);
	glm::vec3 normalsColor = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 gridColor = glm::vec3(0.77f, 0.77f, 0.897f);
	glm::vec3 boundingBoxColor = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 beackgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);

	Scene();

	void AddModel(MeshModel* model);
	void AddLight(Light* light);
	const int GetModelCount() const;
	const int GetLightCount() const;

	void AddNewCamera(glm::vec3 eye = glm::vec3(0, -500, 500), glm::vec3 at = glm::vec3(0, 0, 0), glm::vec3 up = glm::vec3(0, 1, 1));
	void AddNewParallelLight();
	void AddNewPointLight();
	void AddAmbientLight();
	const int GetCameraCount() const;

	void SetActiveCameraIndex(int index);
	void SetActiveLightIndex(int index);
	const int GetActiveCameraIndex() const;
	const int GetActiveLightIndex() const;

	void SetActiveModelIndex(int index);
	const int GetActiveModelIndex() const;


	MeshModel* GetModelByIndex(int index);
	Light* GetLightByIndex(int index);
	Camera* GetCameraByIndex(int cameraIndex);
	std::vector<std::string> getModelNames();
	std::vector<std::string> getLightNames();
	std::vector<std::string> GetCameraNames();
	MeshModel* GetActiveModel();
	Light* GetActiveLight();
	Camera* GetActiveCamera();
	glm::mat4x4 GetCameraScalingMatrix();
	// Add more methods as needed...
};