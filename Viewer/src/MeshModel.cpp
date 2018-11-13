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
	worldTransform(glm::mat4x4(1)),
	tm(new TransformationMatrices()),
	param(new ModelGeometricParameters())
{
	this->faces = faces;
	this->vertices = vertices;
	this->normals = normals;
	this->modelName = modelName;
}

MeshModel::MeshModel(std::string _modelName) : modelName(_modelName), worldTransform(glm::mat4x4(1)), tm(new TransformationMatrices()),
param(new ModelGeometricParameters()) {}

MeshModel::~MeshModel()
{
	delete tm;
	delete param;
}

void MeshModel::CalcBoundry()
{
	float minX=0,maxX=10000,minY=0,maxY= 10000,minZ=0,MaxZ= 10000;

	for(int i=0 ; i< vertices.size() ; ++i)
	{
		//if (vertices[i][0] < minX)
		//	minX = vertices[i][0];
		//if (vertices[i][0] > maxX)
		//	maxX = vertices[i][0];
		//if (vertices[i][1] < minY)
		//	minY = vertices[i][1];
		//if (vertices[i][1] > maxY)
		//	maxY = vertices[i][1];
		//if (vertices[i][2] < minZ)
		//	minZ = vertices[i][2];
		//if (vertices[i][2] > maxZ)
		//	maxZ = vertices[i][2];

	}



}

void MeshModel::SetWorldTransformation(const glm::mat4x4& worldTransform)
{
	this->worldTransform = worldTransform;
}

glm::mat4x4& MeshModel::GetWorldTransformation()
{
	this->SetTransofrmationMatrices();

	worldTransform =
		tm->scaleMatrix *
		tm->translationMatrix *
		tm->rotataionXmatrix *
		tm->rotataionYmatrix *
		tm->rotataionZmatrix;

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

void MeshModel::SetTransofrmationMatrices()
{
	glm::mat4x4 _scaleMatrix
	{ param->scale_x,  0 ,  0 ,  0,
		0 ,  param->scale_y,  0 ,  0,
		0 ,  0 ,  param->scale_z,  0,
		0 ,  0 ,  0 ,  1 };

	glm::mat4x4 _translationMatrix
	{ 1,  0 ,  0 ,  param->trans_x,
		0 ,  1,  0 ,  param->trans_y,
		0 ,  0 ,  1,  param->trans_z,
		0 ,  0 ,  0 ,  1 };

	double degToRad = double(M_PI) / double(180);

	glm::mat4x4 _rotataionXmatrix
	{ 1	,				0					,					0						,	0,
		0	,	glm::cos(param->rot_x* degToRad)	,	-1 * glm::sin(param->rot_x* degToRad)	,	0,
		0	,	glm::sin(param->rot_x* degToRad)	,	glm::cos(param->rot_x* degToRad)			,	0,
		0	,				0					,					0						,	1 };

	glm::mat4x4 _rotataionYmatrix
	{ glm::cos(param->rot_y* degToRad)			,	0	,	glm::sin(param->rot_y* degToRad)	,	0,
		0							,	1	,				0					,	0,
		-1 * glm::sin(param->rot_y* degToRad)	,	0	,	glm::cos(param->rot_y* degToRad)	,	0,
		0										,	0	,				0					,	1 };


	glm::mat4x4 _rotataionZmatrix
	{ glm::cos(param->rot_z* degToRad)	,	-1 * glm::sin(param->rot_z* degToRad)	,	0	,	0,
		glm::sin(param->rot_z* degToRad)	,	glm::cos(param->rot_z* degToRad)			,	0	,	0,
		0					,				0							,	1	,	0,
		0					,				0							,	0	,	1 };

	tm->scaleMatrix = _scaleMatrix;
	tm->rotataionXmatrix = _rotataionXmatrix;
	tm->rotataionYmatrix = _rotataionYmatrix;
	tm->rotataionZmatrix = _rotataionZmatrix;
	tm->translationMatrix = glm::transpose(_translationMatrix);
}


