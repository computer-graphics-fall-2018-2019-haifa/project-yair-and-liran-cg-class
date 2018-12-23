#pragma once
#include "Scene.h"
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>


/*
 * Renderer class.
 */
class Renderer
{
private:
	float *colorBuffer;
	float *zBuffer;
	int viewportWidth;
	int viewportHeight;
	int viewportX;
	int viewportY;
	Scene* scene;

	void putPixel(int x, int y, const glm::vec3& color, float z = 1, bool isBackground = false);
	void createBuffers(int viewportWidth, int viewportHeight);

	GLuint glScreenTex;
	GLuint glScreenVtc;

	void createOpenGLBuffer();
	void initOpenGLRendering();

public:
	Renderer(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	~Renderer();

	//TransformationMatrices getTransofrmationsFromParam(ModelGeometricParameters& param);
	std::vector<Face> getClipedFaces(std::vector<Face> faces, std::vector<glm::vec4> vertices, float left, float right, float bottom, float top, float near_, float far_);
	void renderBoundingBox(BoundingBox& bounding_box, glm::mat4x4& vertexTransformationMatrix, glm::vec3& color);
	void RenderGrid(glm::mat4x4 rotateMatrix, glm::vec3& color);
	void Render(Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	void SetViewport(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	void DrawLineBersenhamAlg(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, glm::vec3& color);

	void BersenhamAlg(GLfloat p1, GLfloat q1, GLfloat p2, GLfloat q2, bool isXYchanged, glm::vec3& color);
	void DrawEdge(glm::vec4& v1, glm::vec4& v2, glm::vec3& color);
	glm::vec2 GetBarycentricCoors2D(std::vector<glm::vec4> vertices, glm::vec3 p);
	void FillTriangle(std::vector<glm::vec4>& vertices, std::vector<glm::vec3>& normals, bool isLight = false);
	void renderFaces(std::vector<Face>& faces, std::vector<glm::vec4>& finalVertices, bool isActiveModel = false, bool isLight = false);
	std::vector<glm::vec4> getFinalVertexesFromWortldTrans(glm::mat4x4& worldTransformation, std::vector<glm::vec3>& vertices);
	glm::vec3 GetColorForPointAndNormal(glm::vec3& point, glm::vec3& normal);
	// Add more methods/functionality as needed...
};
