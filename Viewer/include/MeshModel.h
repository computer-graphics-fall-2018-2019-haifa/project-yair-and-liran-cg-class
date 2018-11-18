#ifndef __MESHMODEL__
#define __MESHMODEL__

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "Face.h"
#include "TransformationMatrices.h"
#include "ModelGeometricParameters.h"
#include "BoundingBox.h"
#include <map>

/*
 * MeshModel class.
 * This class represents a mesh model (with faces and faceNormals informations).
 * You can use Utils::LoadMeshModel to create instances of this class from .obj files.
 */
class MeshModel
{
public:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> faceNormals;
	std::map<int, glm::vec3> indexesTovertexNormals;
	glm::mat4x4 worldTransform{};
	glm::vec4 color{};
	std::string modelName;
	


	TransformationMatrices* tm;
	ModelGeometricParameters* param;
	BoundingBox boundingBox;

	void CalculateVertexNormals();
	MeshModel(std::vector<Face>& faces, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::string& modelName);
	MeshModel(std::string _modelName);
	virtual ~MeshModel();
	void SetWorldTransformation(glm::mat4x4& worldTransform);
	glm::mat4x4& GetWorldTransformation();

	glm::vec4& GetColor();
	void SetColor(glm::vec4& color);

	std::string& GetModelName();
	std::vector<glm::vec3> GetVertices();
	std::vector<Face> GetFaces();

	std::string GetName();
	void SetTransofrmationMatrices();
	std::vector<glm::vec3> GetFaceNormals(std::vector<Face>& faces, std::vector<glm::vec3>& vertices);
};

#endif