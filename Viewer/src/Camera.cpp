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

void Camera::SetCameraLookAt(const glm::vec3& from, const glm::vec3& to, const glm::vec3& tmp)
{
	glm::vec3 forward = glm::normalize(from - to);
	glm::vec3 right = glm::cross(normalize(tmp), forward);
	glm::vec3 up = glm::cross(forward, right);

	glm::mat4x4 camToWorld;

	camToWorld[0][0] = right.x;
	camToWorld[0][1] = right.y;
	camToWorld[0][2] = right.z;
	camToWorld[1][0] = up.x;
	camToWorld[1][1] = up.y;
	camToWorld[1][2] = up.z;
	camToWorld[2][0] = forward.x;
	camToWorld[2][1] = forward.y;
	camToWorld[2][2] = forward.z;

	camToWorld[3][0] = from.x;
	camToWorld[3][1] = from.y;
	camToWorld[3][2] = from.z;

	viewTransformation = camToWorld;
	/*
	glm::vec3 newAt = glm::normalize(at - eye);
	glm::vec3 xaxis = glm::normalize(glm::cross(newAt, up));
	glm::vec3 newUp = glm::cross(xaxis, newAt);
	glm::vec3 minusNewAt = glm::vec3(newAt[0] * -1, newAt[1] * -1, newAt[2] * -1);
	glm::mat4x4 C
	{	xaxis[0]			,	xaxis[1]			,	xaxis[2]			,	0,
		newUp[0]			,	newUp[1]			,	newUp[2]			,	0,
		minusNewAt[0]		,	minusNewAt[1]		,	minusNewAt[2]		,	0,
		eye[0]				,	eye[1]				,	eye[2]				,	1,
	};
	viewTransformation = C;
	*/
	/*
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
	*/
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
