#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#define M_PI           3.14159265358979323846  /* pi */

MeshModel::MeshModel(std::vector<Face>& faces, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::string& modelName) :
	modelName(modelName),
	worldTransform(glm::mat4x4(1))
{
	this->faces = faces;
	this->vertices = vertices;
	this->normals = normals;
	this->modelName = modelName;
}

MeshModel::MeshModel(MeshModel& meshModel)
{
	this->faces = meshModel.faces;
	this->vertices = meshModel.vertices;
	this->normals = meshModel.normals;
	this->modelName = meshModel.modelName;
	this->worldTransform = meshModel.worldTransform;
}

MeshModel::~MeshModel()
{

}

void MeshModel::SetWorldTransformation(const glm::mat4x4& worldTransform)
{
	this->worldTransform = worldTransform;
}

const glm::mat4x4& MeshModel::GetWorldTransformation() const
{
	return worldTransform;
}

void MeshModel::SetColor(const glm::vec4& color)
{
	this->color = color;
}

const glm::vec4& MeshModel::GetColor() const
{
	return color;
}

const std::string& MeshModel::GetModelName()
{
	return modelName;
}

std::vector<glm::vec3> MeshModel::GetVertices()
{
	return vertices;
}

std::vector<Face> MeshModel::GetFaces()
{
	return faces;
}

std::string MeshModel::GetName()
{
	return modelName;
}

void MeshModel::SetProjectionTransformation()
{
	glm::mat4x4 _scaleMatrix
	{ param.scale_x,  0 ,  0 ,  0,
		0 ,  param.scale_y,  0 ,  0,
		0 ,  0 ,  param.scale_z,  0,
		0 ,  0 ,  0 ,  1 };

	glm::mat4x4 _translationMatrix
	{ 1,  0 ,  0 ,  param.trans_x,
		0 ,  1,  0 ,  param.trans_y,
		0 ,  0 ,  1,  param.trans_z,
		0 ,  0 ,  0 ,  1 };

	double degToRad = double(M_PI) / double(180);

	glm::mat4x4 _rotataionXmatrix
	{ 1	,				0					,					0						,	0,
		0	,	glm::cos(param.rot_x* degToRad)	,	-1 * glm::sin(param.rot_x* degToRad)	,	0,
		0	,	glm::sin(param.rot_x* degToRad)	,	glm::cos(param.rot_x* degToRad)			,	0,
		0	,				0					,					0						,	1 };

	glm::mat4x4 _rotataionYmatrix
	{ glm::cos(param.rot_y* degToRad)			,	0	,	glm::sin(param.rot_y* degToRad)	,	0,
		0							,	1	,				0					,	0,
		-1 * glm::sin(param.rot_y* degToRad)	,	0	,	glm::cos(param.rot_y* degToRad)	,	0,
		0										,	0	,				0					,	1 };


	glm::mat4x4 _rotataionZmatrix
	{ glm::cos(param.rot_z* degToRad)	,	-1 * glm::sin(param.rot_z* degToRad)	,	0	,	0,
		glm::sin(param.rot_z* degToRad)	,	glm::cos(param.rot_z* degToRad)			,	0	,	0,
		0					,				0							,	1	,	0,
		0					,				0							,	0	,	1 };

	tm.scaleMatrix = _scaleMatrix;
	tm.rotataionXmatrix = _rotataionXmatrix;
	tm.rotataionYmatrix = _rotataionYmatrix;
	tm.rotataionZmatrix = _rotataionZmatrix;
	tm.translationMatrix = _translationMatrix;
}


