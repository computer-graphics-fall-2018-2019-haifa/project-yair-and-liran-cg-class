#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "MeshModel.h"

/*
 * Camera class. This class takes care of all the camera transformations and manipulations.
 *
 * Implementation suggestion:
 * --------------------------
 * Make the Camera class be a subclass of MeshModel, so you can easily and elegantly render 
 * the cameras you have added to the scene.
 */
class Camera : public MeshModel
{
private:
	glm::mat4x4 viewTransformation;
	glm::mat4x4 projectionTransformation;
	float zoom;

public:
	glm::vec3 eye, at, up;
	Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up, int index = 0);
	~Camera();

	void SetCameraLookAt();

	void SetOrthographicProjection(
		const float left,
		const float right,
		const float bottom,
		const float top,
		const float near,
		const float far);

	void SetPerspectiveProjection(
		const float fovy,
		const float aspect,
		const float near,
		const float far);

	void SetZoom(const float zoom);

	// Add more methods/functionality as needed...

	glm::mat4x4 GetProjectionTransformation(const float left, const float right, const float bottom, const float top,
		const float near, const float far);
	glm::mat4x4 GetViewTransformation();
};
