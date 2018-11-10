#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


Camera::Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up) :
	zoom(1.0)
{
	SetCameraLookAt(eye, at, up);
}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	glm::vec3 x = glm::normalize(eye - at);
	glm::vec3 y = glm::normalize(glm::cross(up, x));
	glm::vec3 z = glm::normalize(glm::cross(x, y));

	glm::vec4 x4(x[0], x[1], x[2], 0);
	glm::vec4 y4(y[0], y[1], y[2], 0);
	glm::vec4 z4(z[0], z[1], z[2], 0);
	glm::vec4 t = glm::vec4(-1*eye[0], -1 * eye[1], -1 * eye[2], 1.0);
	glm::mat4 C = glm::mat4(x4, y4, z4, t);
	viewTransformation = C;

}

void Camera::SetOrthographicProjection(const float left, const float right, const float bottom, const float top,
	const float near, const float far)
{
	glm::mat4x4 C
	{ 2.0 / (right - left)		,	0						,		0					,	-1.0*((right + left) / (right - left)),
		0						,	2.0 / (top - bottom)	,		0					,	-1.0*((top + bottom) / (top - bottom)),
		0						,	0						,		2.0 / (near - far)	,	-1.0*((far + near) / (far - near)),
		0						,	0						,	0						,	1,
	};
	projectionTransformation = C;
}


void Camera::SetPerspectiveProjection(
	const float fovy,
	const float aspectRatio,
	const float near,
	const float far)
{

}

void Camera::SetZoom(const float zoom)
{

}

glm::mat4x4 Camera::GetProjectionTransformation()
{
	return projectionTransformation;
}

glm::mat4x4 Camera::GetViewTransformation()
{
	return viewTransformation;
}
