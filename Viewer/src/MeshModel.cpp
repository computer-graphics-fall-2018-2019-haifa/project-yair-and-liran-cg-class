#include "MeshModel.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

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


