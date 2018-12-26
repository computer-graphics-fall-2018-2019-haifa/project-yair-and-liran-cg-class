#define _USE_MATH_DEFINES

#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


Camera::Camera(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up, int index, MeshModel* meshPtr) :
	MeshModel(meshPtr->faces, meshPtr->vertices, meshPtr->faceNormals, "Camera " + std::to_string(index))
{
	this->eye = eye;
	this->at = at;
	this->up = up;
	SetCameraLookAt();
}

Camera::~Camera()
{
}

void Camera::SetCameraLookAt()
{
	this->SetTransofrmationMatrices();
	glm::vec3 _eye = tm->translationMatrix * glm::vec4(eye[0], eye[1], eye[2], 1);
	glm::vec3 _up = tm->rotataionXmatrix *
		tm->rotataionYmatrix *
		tm->rotataionZmatrix*
		glm::vec4(up[0], up[1], up[2], 1);
	glm::vec3 _at = tm->translationMatrix *
		tm->rotataionXmatrix *
		tm->rotataionYmatrix *
		tm->rotataionZmatrix*
		glm::vec4(at[0], at[1], at[2], 1);
	glm::vec3 z = glm::normalize(_eye - _at);
	glm::vec3 x = glm::normalize(glm::cross(_up, z));
	glm::vec3 y = glm::normalize(glm::cross(x, z));

	glm::vec4 z4(z[0], z[1], z[2], 0);
	glm::vec4 x4(x[0], x[1], x[2], 0);
	glm::vec4 y4(y[0], y[1], y[2], 0);
	glm::vec4 t(0, 0, 0, 1);
	glm::mat4 C = glm::mat4(x4, y4, z4, t);
	glm::mat4x4 _translationMatrix
	{ 1	,	0	,	0	,	_eye[0],
		0	,	1	,	0	,	_eye[1],
		0	,	0	,	1	,	_eye[2],
		0	,	0	,	0	,	1 };


	viewTransformation = C * glm::transpose(_translationMatrix);
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

void Camera::SetPerspectiveProjection(const float left, const float right, const float bottom, const float top,
	const float near, const float far)
{
	glm::mat4x4 C
	{ (2.0 * near) / (right - left)		,	0								,		(right + left) / (right - left)		,	0,
		0								,	(2.0 * near) / (top - bottom)	,		 (top + bottom) / (top - bottom)	,	0,
		0								,	0								,		-1 * (far + near) / (far - near)	,	-1 * ((2 * far * near) / (far - near)),
		0								,	0								,	-1										,	0,
	};
	projectionTransformation = C;
}

void Camera::SetZoom(const float zoom)
{

}

glm::mat4x4 Camera::GetProjectionTransformation(int viewPortWidthMiddle, int viewPortHeightMiddle, bool isPrespective)
{
	float	left = eye[0] - viewPortWidthMiddle,
		right = eye[0] + viewPortWidthMiddle,
		bottom = eye[1] - viewPortHeightMiddle,
		top = eye[1] + viewPortHeightMiddle;
	near_ = 11 - distance;
	far_ = 200;
	if (isPrespective)
		SetPerspectiveProjection(left, right, bottom, top, near_, far_);
	else
		SetOrthographicProjection(left, right, bottom, top, near_, far_);
	return projectionTransformation;
}

glm::mat4x4 Camera::GetViewTransformation()
{
	SetCameraLookAt();
	return viewTransformation;
}
