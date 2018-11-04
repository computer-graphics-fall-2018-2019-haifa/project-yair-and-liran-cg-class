#define _USE_MATH_DEFINES

#include "Renderer.h"
#include "InitShader.h"
#include "MeshModel.h"
#include <imgui/imgui.h>
#include <vector>
#include <cmath>
#include "glad/glad.h"
#include <glm/common.hpp>

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)

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

void Renderer::DrawLineBersenhamAlg(GLfloat p1, GLfloat q1, GLfloat p2, GLfloat q2, glm::vec3 color = glm::vec3(0, 0, 5))
{
	GLfloat a = fabs(q2 - q1)/(p2 - p1);

	if (fabs(a) <= 1)
	{
		if (p1 > p2)
		{
			std::swap(p1, p2);
			std::swap(q1, q2);
		}
		BersenhamAlg(p1, q1, p2, q2, true, color);
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
		BersenhamAlg(p1, q1, p2, q2, false, color);
	}
}

void Renderer::BersenhamAlg(GLfloat p1, GLfloat q1, GLfloat p2, GLfloat q2, bool tmp, glm::vec3 color = glm::vec3(0, 0, 5))
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
		if (tmp)
			putPixel(x, y, color);
		else
			putPixel(y, x, color);
		x++; e += 2 * dq;
	}
}

void Renderer::Render(Scene& scene)
{
	int scaleFactor = 100;
	glm::mat4x4 scaleMatrix
	{ 200,  0 ,  0 ,  0,
		0 ,  200,  0 ,  0,
		0 ,  0 ,  200,  0,
		0 ,  0 ,  0 ,  1 };
	glm::mat4x4 translationMatrix
	{ 1,  0 ,  0 ,  500,
		0 ,  1,  0 ,  100,
		0 ,  0 ,  1,  100,
		0 ,  0 ,  0 ,  1 };
	glm::mat4x4 worldTransformation = transpose(translationMatrix)*scaleMatrix;

	int modelsNumber = scene.GetModelCount();
	for (int modelIndex = 0; modelIndex < modelsNumber; ++modelIndex)
	{

		MeshModel modelPtr = scene.GetModelByIndex(modelIndex);
		std::vector<glm::vec3> vertices = modelPtr.GetVertices();
		std::vector<Face> faces = modelPtr.GetFaces();
		std::vector<glm::vec4> finalVertices;
		for (int vertexIndex = 0; vertexIndex < vertices.size(); ++vertexIndex)
		{
			glm::vec3 vertex = vertices[vertexIndex];
			glm::vec4 augmentedVertex(vertex[0], vertex[1], vertex[2], 1);
			glm::vec4 finalVertex = worldTransformation * augmentedVertex;
			finalVertices.push_back(finalVertex);
		}

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
				DrawLineBersenhamAlg(v1[0], v1[1], v2[0], v2[1]);
			}
		}
	}

}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
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



/*
 *	glm::vec3 color = glm::vec3(0, 0, 5);
	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2) + 50, int(viewportHeight / 2) + 50, color);
	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2) + 50, int(viewportHeight / 2) + 150, color);
	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2) + 50, int(viewportHeight / 2) - 50, color);
	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2) + 50, int(viewportHeight / 2) - 150, color);

	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2) - 50, int(viewportHeight / 2) + 50, color);
	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2) - 50, int(viewportHeight / 2) + 150, color);
	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2) - 50, int(viewportHeight / 2) - 50, color);
	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2) - 50, int(viewportHeight / 2) - 150, color);


	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2) - 50, int(viewportHeight / 2), color);
	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2) + 50, int(viewportHeight / 2), color);

	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2), int(viewportHeight / 2) - 50, color);
	DrawLineBersenhamAlg(int(viewportWidth / 2), int(viewportHeight / 2), int(viewportWidth / 2), int(viewportHeight / 2) + 50, color);

 *
 *
 */

 /*
  *std::vector<glm::vec3> vertices;
	 vertices.push_back(glm::vec3(0, 0, 0));
	 vertices.push_back(glm::vec3(0, 0, 1));
	 vertices.push_back(glm::vec3(0, 1, 0));
	 vertices.push_back(glm::vec3(4, 0, 0));
	 vertices.push_back(glm::vec3(4, 0, 5));
	 vertices.push_back(glm::vec3(4, 5, 0));
	 std::vector<glm::vec4> finalVertices;
	 for (int vertexIndex = 0; vertexIndex < vertices.size(); ++vertexIndex)
	 {
		 glm::vec3 vertex = vertices[vertexIndex];
		 glm::vec4 augmentedVertex(vertex[0], vertex[1], vertex[2], 1);
		 glm::vec4 finalVertex = worldTransformation * augmentedVertex;
		 finalVertices.push_back(finalVertex);
	 }
	 int indexArr1[] = { 0,1,2,3,4,5 };
	 int indexArr2[] = { 1,2,0,4,5,3 };
	 for (int i = 0; i < 6; ++i)
	 {
		 int v1Index = indexArr1[i];
		 int v2Index = indexArr2[i];
		 glm::vec3 v1 = finalVertices[v1Index];
		 glm::vec3 v2 = finalVertices[v2Index];
		 DrawLineBersenhamAlg(v1[0], v2[0], v1[1], v2[1]);
	 }
  *
  *
  */
  /*
  // Draw a chess board in the middle of the screen
  for (int i = 100; i < viewportWidth - 100; i++)
  {
  //putPixel(i, int(viewportHeight/2), glm::vec3(1, 1, 0));
  for (int j = 100; j < viewportHeight - 100; j++)
  {
  int mod_i = i / 50;
  int mod_j = j / 50;

  int odd = (mod_i + mod_j) % 2;
  if (odd)
  {
  putPixel(i, j, glm::vec3(0, 1, 0));
  }
  else
  {
  putPixel(i, j, glm::vec3(1, 0, 0));
  }
  }
  }
  */