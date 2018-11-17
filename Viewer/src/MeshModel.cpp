#include "MeshModel.h"
//#include "Utils.h"
#include <vector>
#include <string>
#include <sstream>
#define M_PI           3.14159265358979323846  /* pi */

MeshModel::MeshModel(std::vector<Face>& faces, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::string& modelName) :
	modelName(modelName),
	worldTransform(glm::mat4x4(1)),
	tm(new TransformationMatrices()),
	param(new ModelGeometricParameters()), 
	boundingBox(vertices)
{
	this->faces = faces;
	this->vertices = vertices;
	this->faceNormals = normals; // GetFaceNormals(faces, vertices);
	this->modelName = modelName;
}

MeshModel::MeshModel(std::string _modelName) : 
	modelName(_modelName), 
	worldTransform(glm::mat4x4(1)),	
	tm(new TransformationMatrices()),
	param(new ModelGeometricParameters()), 
	boundingBox(std::vector<glm::vec3>())
{
}

MeshModel::~MeshModel()
{
	delete tm;
	delete param;
}

void MeshModel::SetWorldTransformation(glm::mat4x4& worldTransform)
{
	this->worldTransform = worldTransform;
}

glm::mat4x4& MeshModel::GetWorldTransformation()
{
	this->SetTransofrmationMatrices();

	worldTransform =
		tm->translationMatrix *
		tm->rotataionXmatrix *
		tm->rotataionYmatrix *
		tm->rotataionZmatrix *
		tm->scaleMatrix;

	return worldTransform;
}

void MeshModel::SetColor(glm::vec4& color)
{
	this->color = color;
}

glm::vec4& MeshModel::GetColor() 
{
	return color;
}

std::string& MeshModel::GetModelName()
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

std::vector<glm::vec3> MeshModel::GetFaceNormals(std::vector<Face>& faces, std::vector<glm::vec3>& vertices)
{
	std::vector<glm::vec3> faceNormals;
	for (int i = 0; i < faces.size(); ++i)
	{
		Face face = faces[i];
		int v0Index = face.GetVertexIndex(0);
		int v1Index = face.GetVertexIndex(1);
		int v2Index = face.GetVertexIndex(2);
		glm::vec3 v0 = vertices[v0Index];
		glm::vec3 v1 = vertices[v1Index];
		glm::vec3 v2 = vertices[v2Index];
		glm::vec3 sum3 = v0 + v1 + v2;
		glm::vec3 mean(sum3[0] / 3, sum3[1] / 3, sum3[2] / 3);
		glm::vec3 direction = glm::cross(glm::normalize(v0-v1), glm::normalize(v0-v2));
		glm::vec3 to = mean + direction;
	}
	return faceNormals;
}


