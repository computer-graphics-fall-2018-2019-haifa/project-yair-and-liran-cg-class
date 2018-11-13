#pragma once
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "Face.h"
#include "TransformationMatrices.h"
#include "ModelGeometricParameters.h"
#include "BoundingBox.h"

/*
 * MeshModel class.
 * This class represents a mesh model (with faces and normals informations).
 * You can use Utils::LoadMeshModel to create instances of this class from .obj files.
 */
class MeshModel
{
private:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4x4 worldTransform{};
	glm::vec4 color{};
	std::string modelName;
	

public:
	TransformationMatrices* tm;
	ModelGeometricParameters* param;
	BoundingBox boundingBox;

	MeshModel(std::vector<Face>& faces, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::string& modelName);
	MeshModel(std::string _modelName);
	virtual ~MeshModel();
	void CalcBoundry();
	void SetWorldTransformation(const glm::mat4x4& worldTransform);
	glm::mat4x4& GetWorldTransformation();

	const glm::vec4& GetColor() const;
	void SetColor(const glm::vec4& color);

	const std::string& GetModelName();
	std::vector<glm::vec3> GetVertices();
	std::vector<Face> GetFaces();

	std::string GetName();
	void SetTransofrmationMatrices();

};
