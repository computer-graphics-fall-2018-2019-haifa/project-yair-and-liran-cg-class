#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


Camera::Camera(const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up) :
	zoom(1.0)
{
	SetCameraLookAt(eye, at, up);
}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	glm::vec3 z = normalize(eye - at);
	glm::vec3 x = normalize(cross(normalize(up), z));
	glm::vec3 y = normalize(cross(x, z));
	glm::mat4x4 C
	{ x[0]	,	y[0]	,	z[0]	,	eye[0],
		x[1]	,	y[1]	,	z[1]	,	eye[1],
		x[2]	,	y[2]	,	z[2]	,	eye[2],
		0		,	0		,	0		,	1,
	};
	viewTransformation = C;
}

void Camera::SetOrthographicProjection(const float left, const float right, const float bottom, const float top,
	const float near, const float far)
{
	glm::mat4x4 C
	{	2.0 / (right - left)	,	0						,		0				,	-1.0*((right + left) / (right - left)),
		0						,	2.0 / (top - bottom)	,		0				,	-1.0*((top + bottom) / (top - bottom)),
		0						,	0						,	2.0 / (near - far)	,	-1.0*((near + far)/ (near - far)),
		0						,	0						,	0					,	1,
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
