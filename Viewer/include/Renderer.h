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

	void putPixel(int x, int y, const glm::vec3& color);
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
	void Render(Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	void SetViewport(int viewportWidth, int viewportHeight, int viewportX = 0, int viewportY = 0);
	void DrawLineBersenhamAlg(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, glm::vec3& color);

	void BersenhamAlg(GLfloat p1, GLfloat q1, GLfloat p2, GLfloat q2, bool isXYchanged, glm::vec3& color);
	void Draw2Vertexes(glm::vec4& v1, glm::vec4& v2, glm::vec3& color);
	void renderFaces(std::vector<Face>& faces, std::vector<glm::vec4>& finalVertices);
	std::vector<glm::vec4> getFinalVertexesFromWortldTrans(glm::mat4x4& worldTransformation, std::vector<glm::vec3>& vertices);

	// Add more methods/functionality as needed...
};
