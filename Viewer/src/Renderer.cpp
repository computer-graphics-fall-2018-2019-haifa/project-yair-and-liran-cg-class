#define _USE_MATH_DEFINES

#include "Renderer.h"
#include "InitShader.h"
#include "MeshModel.h"
#include <imgui/imgui.h>
#include <vector>
#include <cmath>
#include "glad/glad.h"
#include <vector>
#include <glm/common.hpp>
#include <vector>

#define M_PI           3.14159265358979323846  /* pi */
#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define GRID_LENGTH 1000
#define GRID_DELTA 50

Renderer::Renderer(int viewportWidth, int viewportHeight, int viewportX, int viewportY) :
	colorBuffer(nullptr),
	zBuffer(nullptr)
{
	initOpenGLRendering();
	SetViewport(viewportWidth, viewportHeight, viewportX, viewportY);
}

Renderer::~Renderer()
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}
}

void Renderer::putPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewportWidth) return;
	if (j < 0) return; if (j >= viewportHeight) return;
	colorBuffer[INDEX(viewportWidth, i, j, 0)] = color.x;
	colorBuffer[INDEX(viewportWidth, i, j, 1)] = color.y;
	colorBuffer[INDEX(viewportWidth, i, j, 2)] = color.z;
}

void Renderer::createBuffers(int viewportWidth, int viewportHeight)
{
	if (colorBuffer)
	{
		delete[] colorBuffer;
	}

	colorBuffer = new float[3 * viewportWidth * viewportHeight];
	for (int x = 0; x < viewportWidth; x++)
	{
		for (int y = 0; y < viewportHeight; y++)
		{
			putPixel(x, y, glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewportWidth; i++)
	{
		for (int j = 0; j < viewportHeight; j++)
		{
			putPixel(i, j, color);
		}
	}
}

void Renderer::SetViewport(int viewportWidth, int viewportHeight, int viewportX, int viewportY)
{
	this->viewportX = viewportX;
	this->viewportY = viewportY;
	this->viewportWidth = viewportWidth;
	this->viewportHeight = viewportHeight;
	createBuffers(viewportWidth, viewportHeight);
	createOpenGLBuffer();
}

void Renderer::DrawLineBersenhamAlg(GLfloat p1, GLfloat q1, GLfloat p2, GLfloat q2, glm::vec3& color = glm::vec3(1, 1, 1))
{
	GLfloat a = fabs(q2 - q1) / (p2 - p1);

	if (fabs(a) <= 1)
	{
		if (p1 > p2)
		{
			std::swap(p1, p2);
			std::swap(q1, q2);
		}
		BersenhamAlg(p1, q1, p2, q2, false, color);
	}
	else
	{
		std::swap(p1, q1);
		std::swap(p2, q2);
		if (p1 > p2)
		{
			std::swap(p1, p2);
			std::swap(q1, q2);
		}
		BersenhamAlg(p1, q1, p2, q2, true, color);
	}
}

void Renderer::BersenhamAlg(GLfloat p1, GLfloat q1, GLfloat p2, GLfloat q2, bool isXYchanged, glm::vec3& color = glm::vec3(1, 1, 1))
{
	GLfloat x = p1, y = q1;
	GLfloat dp = p2 - p1;
	GLfloat dq = fabs(q2 - q1);
	GLfloat a = dq / dp;
	GLfloat c = q1 + a * p1;
	GLfloat e = -1 * dp;

	int yState = q1 < q2 ? 1 : -1;

	while (x <= p2)
	{
		if (e > 0)
		{
			y += yState; e -= 2 * dp;
		}
		if (isXYchanged)
			putPixel(y, x, color);
		else
			putPixel(x, y, color);
		x++; e += 2 * dq;
	}
}

void Renderer::Draw2Vertexes(glm::vec4& v1, glm::vec4& v2, glm::vec3& color = glm::vec3(0, 0, 0))
{
	DrawLineBersenhamAlg((v1[0]+1) * (viewportWidth / 2) * scene->zoom,
		(v1[1]+1) * (viewportHeight / 2) * scene->zoom,
		(v2[0]+1) * (viewportWidth / 2) * scene->zoom,
		(v2[1]+1) * (viewportHeight / 2) * scene->zoom,
		color);
}

void Renderer::renderFaces(std::vector<Face>& faces, std::vector<glm::vec4>& finalVertices, bool isActiveModel, GLfloat scaleNormalLength, bool isShowNormals, glm::vec3& modelColor, glm::vec3& normalsColor)
{
	for (int faceIndex = 0; faceIndex < faces.size(); ++faceIndex)
	{
		Face face = faces[faceIndex];
		int indexArr1[] = { 0,1,2 };
		int indexArr2[] = { 1,2,0 };
		for (int i = 0; i < 3; ++i)
		{
			int v1Index = indexArr1[i];
			int v2Index = indexArr2[i];
			int vertexIndex1 = face.GetVertexIndex(v1Index);
			int vertexIndex2 = face.GetVertexIndex(v2Index);
			glm::vec4 v1 = finalVertices[vertexIndex1 - 1];
			glm::vec4 v2 = finalVertices[vertexIndex2 - 1];
			Draw2Vertexes(v1, v2, modelColor);
		}
		if (isShowNormals && isActiveModel)
		{
			int v0Index = face.GetVertexIndex(0);
			int v1Index = face.GetVertexIndex(1);
			int v2Index = face.GetVertexIndex(2);
			glm::vec3 v0 = finalVertices[v0Index - 1];
			glm::vec3 v1 = finalVertices[v1Index - 1];
			glm::vec3 v2 = finalVertices[v2Index - 1];
			glm::vec3 mean = (v0 + v1 + v2) / GLfloat(3);
			glm::vec3 direction = glm::normalize(glm::cross((v0 - v2), (v0 - v1)));
			glm::vec3 to = mean + (direction * scaleNormalLength);
			Draw2Vertexes(glm::vec4(mean[0], mean[1], mean[2], 1), glm::vec4(to[0], to[1], to[2], 1), normalsColor);
		}
	}
}

std::vector<glm::vec4> Renderer::getFinalVertexesFromWortldTrans(glm::mat4x4& worldTransformation, std::vector<glm::vec3>& vertices)
{
	std::vector<glm::vec4> finalVertices;
	for (int vertexIndex = 0; vertexIndex < vertices.size(); ++vertexIndex)
	{
		glm::vec3 vertex = vertices[vertexIndex];
		glm::vec4 augmentedVertex(vertex[0], vertex[1], vertex[2], 1);
		glm::vec4 finalVertex = worldTransformation * augmentedVertex;
		finalVertices.push_back(finalVertex);
	}
	return finalVertices;
}

void Renderer::initOpenGLRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &glScreenTex);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &glScreenVtc);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(glScreenVtc);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[] = {
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[] = {
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1 };

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc) + sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord);
	glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)sizeof(vtc));

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"), 0);
}

void Renderer::createOpenGLBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewportWidth, viewportHeight, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewportWidth, viewportHeight);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, glScreenTex);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewportWidth, viewportHeight, GL_RGB, GL_FLOAT, colorBuffer);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(glScreenVtc);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


std::vector<Face> Renderer::getClipedFaces(std::vector<Face> faces, std::vector<glm::vec4> vertices, float left, float right, float bottom, float top, float near_, float far_)
{
	std::vector<Face> facesFiltered;
	for (int faceIndex = 0; faceIndex < faces.size(); ++faceIndex)
	{
		Face face = faces[faceIndex];
		int indexArr1[] = { 0,1,2 };
		int indexArr2[] = { 1,2,0 };
		for (int i = 0; i < 3; ++i)
		{
			int v1Index = indexArr1[i];
			int v2Index = indexArr2[i];
			int vertexIndex1 = face.GetVertexIndex(v1Index);
			int vertexIndex2 = face.GetVertexIndex(v2Index);
			glm::vec4 v1 = vertices[vertexIndex1 - 1];
			glm::vec4 v2 = vertices[vertexIndex2 - 1];
			if (v1[0] < left || v2[0] < left ||
				v1[0] > right || v2[0] > right ||
				v1[1] > top || v2[1] > top ||
				v1[1] < bottom || v2[1] < bottom ||
				v1[2] < near_ || v2[2] < near_ ||
				v1[2] > far_ || v2[2] > far_)
				continue;
			facesFiltered.push_back(face);
		}
	}
	return facesFiltered;
}

void Renderer::renderBoundingBox(BoundingBox& boundingBox, glm::mat4x4& vertexTransformationMatrix, glm::vec3& color = glm::vec3(0, 0, 0))
{
	std::vector<glm::vec4> finalVertexes = boundingBox.GetFinalVertexes(vertexTransformationMatrix);

	//bottom edges
	Draw2Vertexes(finalVertexes[0], finalVertexes[1], color);
	Draw2Vertexes(finalVertexes[1], finalVertexes[2], color);
	Draw2Vertexes(finalVertexes[2], finalVertexes[3], color);
	Draw2Vertexes(finalVertexes[3], finalVertexes[0], color);

	//support edges
	Draw2Vertexes(finalVertexes[0], finalVertexes[4], color);
	Draw2Vertexes(finalVertexes[1], finalVertexes[5], color);
	Draw2Vertexes(finalVertexes[2], finalVertexes[6], color);
	Draw2Vertexes(finalVertexes[3], finalVertexes[7], color);

	//top edges
	Draw2Vertexes(finalVertexes[4], finalVertexes[5], color);
	Draw2Vertexes(finalVertexes[5], finalVertexes[6], color);
	Draw2Vertexes(finalVertexes[6], finalVertexes[7], color);
	Draw2Vertexes(finalVertexes[7], finalVertexes[4], color);

	std::vector<glm::vec4> CoordinateSystemVertexes = boundingBox.TransformCoordinateSystem(vertexTransformationMatrix);
	//draw coordinate system -[0]= o, [1] = x, [2] = y, [3] = z
	Draw2Vertexes(CoordinateSystemVertexes[0], CoordinateSystemVertexes[1], glm::vec3(0, 0, 5));
	Draw2Vertexes(CoordinateSystemVertexes[0], CoordinateSystemVertexes[2], glm::vec3(0, 5, 0));
	Draw2Vertexes(CoordinateSystemVertexes[0], CoordinateSystemVertexes[3], glm::vec3(5, 0, 0));
}

void Renderer::RenderGrid(glm::mat4x4 rotateMatrix, glm::vec3& color)
{
	for (int i = -GRID_LENGTH; i <= GRID_LENGTH; i += GRID_DELTA)
	{
		glm::vec4 x_near(-1 * GRID_LENGTH, 0, i, 1);
		glm::vec4 x_far(GRID_LENGTH, 0, i, 1);
		glm::vec4 z_near(i, 0, -1 * GRID_LENGTH, 1);
		glm::vec4 z_far(i, 0, GRID_LENGTH, 1);

		Draw2Vertexes(rotateMatrix*x_near, rotateMatrix*x_far, color);
		Draw2Vertexes(rotateMatrix*z_near, rotateMatrix*z_far, color);
	}
}

void Renderer::Render(Scene& scene)
{
	this->scene = &scene;
	Camera* cam = scene.GetActiveCamera();
	glm::mat4x4 cameraViewingTransform = cam->GetViewTransformation();
	glm::mat4x4 cameraNormalizationMatrix = cam->GetProjectionTransformation(viewportWidth / 2, viewportHeight / 2, scene.isPrespective);
	int modelsNumber = scene.GetModelCount();
	int activeModelIndex = scene.GetActiveModelIndex();

	glm::mat4x4 cameraViewingTransformInverse = glm::inverse(cameraViewingTransform);
	glm::mat4x4 gridTransformationMatrix =
		cameraNormalizationMatrix *
		cameraViewingTransformInverse;
	RenderGrid(gridTransformationMatrix, glm::vec3(scene.gridColor));

	// render models objects
	for (int modelIndex = 0; modelIndex < modelsNumber; ++modelIndex)
	{
		MeshModel* currentModel = scene.GetModelByIndex(modelIndex);
		glm::mat4x4 vertexTransformationMatrix =
			cameraNormalizationMatrix *
			cameraViewingTransformInverse *
			currentModel->GetWorldTransformation();

		std::vector<glm::vec3> vertices = currentModel->GetVertices();
		std::vector<glm::vec4> finalModelVertexes = getFinalVertexesFromWortldTrans(vertexTransformationMatrix, vertices);
		std::vector<Face> faces = currentModel->GetFaces();
		bool isActiveModel = modelIndex == activeModelIndex;
		renderFaces(faces,
			finalModelVertexes,
			isActiveModel,
			scene.scaleNormalLength,
			scene.isShowNormals,
			glm::vec3(scene.modelColor),
			glm::vec3(scene.normalsColor));
		if (isActiveModel)
			renderBoundingBox(currentModel->boundingBox, vertexTransformationMatrix, glm::vec3(scene.boundingBoxColor));
	}

	//render cameras objects
	for (int cameraIndex = 0; cameraIndex < scene.cameras.size(); ++cameraIndex)
	{
		if (cameraIndex == scene.activeCameraIndex)
			continue;
		MeshModel* currentCamera = scene.cameras[cameraIndex];
		glm::mat4x4 vertexTransformationMatrix =
			cameraNormalizationMatrix *
			//scene.GetCameraScalingMatrix() *
			cameraViewingTransformInverse *
			currentCamera->GetWorldTransformation();

		std::vector<glm::vec3> vertices = currentCamera->GetVertices();
		std::vector<glm::vec4> finalModelVertexes = getFinalVertexesFromWortldTrans(vertexTransformationMatrix, vertices);
		std::vector<Face> faces = currentCamera->GetFaces();
		renderFaces(faces, finalModelVertexes);
	}

}


