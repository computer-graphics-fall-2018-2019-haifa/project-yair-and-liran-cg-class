#pragma once
#define _USE_MATH_DEFINES

#include "ImguiMenus.h"
#include "MeshModel.h"
#include "Utils.h"
#include <cmath>
#include <memory>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <nfd.h>
#include <random>
#include "ModelGeometricParameters.h"

bool showDemoWindow = false;
bool showAnotherWindow = false;

glm::vec4 clearColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);

const glm::vec4& GetClearColor()
{
	return clearColor;
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		bool isAddCmaera = false;
		bool isAddLight = false;
		ImGui::Begin("Computer Graphic ass. 1");
		std::vector<std::string> modelNames = scene.getModelNames();
		std::vector<std::string> cameraNames = scene.GetCameraNames();
		std::vector<std::string> lightNames = scene.getLightNames();
		int modelsNumber = modelNames.size();
		int lightsNumber = lightNames.size();
		int cameraCount = scene.GetCameraCount();
		int lightCount = scene.GetLightCount();
		if (modelsNumber > 0)
		{
			char** items = new char*[modelsNumber];
			for (int i = 0; i < modelsNumber; ++i)
			{
				items[i] = const_cast<char*>(modelNames[i].c_str());
			}
			char** cameras = new char*[cameraCount];
			for (int i = 0; i < cameraCount; ++i)
			{
				cameras[i] = const_cast<char*>(cameraNames[i].c_str());
			}

			char** lightItems = new char*[lightsNumber];
			if (lightCount > 0)
			{
				for (int i = 0; i < lightsNumber; ++i)
				{
					lightItems[i] = const_cast<char*>(lightNames[i].c_str());
				}
			}

			

			ImGui::Combo("Select Model", &scene.activeModelIndex, items, modelsNumber);
			ImGui::Combo("Select Camera", &scene.activeCameraIndex, cameras, cameraCount);
			if (lightCount > 0)
			{
				ImGui::Combo("Select Light", &scene.activeLightIndex, lightItems, lightCount);
			}

			if (ImGui::CollapsingHeader("Model"))
			{
				static int e = 2;
				ImGui::RadioButton("ModelRotation", &e, 0); ImGui::SameLine();
				ImGui::RadioButton("ModelTranslation", &e, 1); ImGui::SameLine();
				ImGui::RadioButton("ModelScaling", &e, 2);

				ImGui::Checkbox("Show Face normals", &scene.isShowFaceNormals); ImGui::SameLine();
				ImGui::Checkbox("Show Vertex normals", &scene.isShowVertexNormals);
				ImGui::Checkbox("Show Bounding Box", &scene.isShowBoundingBox);
				ImGui::SliderFloat("Normal scaling", &(scene.scaleNormalLength), 0.001, 2);


				/** Active model parameters ***/
				MeshModel* activeModel = scene.GetActiveModel();
				ImGui::Text("Model parameters");
				if (e == 0)
				{
					ImGui::SliderFloat("Model X rotation", &(activeModel->param->rot_x), -360.0f, 360.0f);
					ImGui::SliderFloat("Model Y rotation", &(activeModel->param->rot_y), -360.0f, 360.0f);
					ImGui::SliderFloat("Model Z rotation", &(activeModel->param->rot_z), -360.0f, 360.0f);
				}
				else if (e == 1) {
					ImGui::SliderFloat("Model X translation", &(activeModel->param->trans_x), -1000.0f, 1000.0f);
					ImGui::SliderFloat("Model Y translation", &(activeModel->param->trans_y), -1000.0f, 1000.0f);
					ImGui::SliderFloat("Model Z translation", &(activeModel->param->trans_z), -1000.0f, 1000.0f);
				}
				else if (e == 2)
				{
					ImGui::SliderFloat("Model X scaling", &(activeModel->param->scale_x), 0.1f, 100.0f);
					ImGui::SliderFloat("Model Y scaling", &(activeModel->param->scale_y), 0.1f, 100.0f);
					ImGui::SliderFloat("Model Z scaling", &(activeModel->param->scale_z), 0.1f, 100.0f);
				}
			}

			if (ImGui::CollapsingHeader("Camera"))
			{
				scene.isAddCamera = ImGui::Button("AddCamera", ImVec2(70, 30));
				/** Active camera parameters ***/
				Camera* activeCamera = scene.GetActiveCamera();
				ImGui::Text("Camera parameters");
				ImGui::Checkbox("Prespective Projection", &scene.isPrespective);
				static int c = 0;
				ImGui::RadioButton("CmaeraRotation", &c, 0); ImGui::SameLine();
				ImGui::RadioButton("CmaeraTranslation", &c, 1);
				if (c == 0)
				{
					ImGui::SliderFloat("Camera X rotation", &(activeCamera->param->rot_x), -360.0f, 360.0f);
					ImGui::SliderFloat("Camera Y rotation", &(activeCamera->param->rot_y), -360.0f, 360.0f);
					ImGui::SliderFloat("Camera Z rotation", &(activeCamera->param->rot_z), -360.0f, 360.0f);
				}
				else if (c == 1)
				{
					ImGui::SliderFloat("Camera X translation", &(activeCamera->param->trans_x), -1000.0f, 1000.0f);
					ImGui::SliderFloat("Camera Y translation", &(activeCamera->param->trans_y), -1000.0f, 1000.0f);
					ImGui::SliderFloat("Camera Z translation", &(activeCamera->param->trans_z), -1000.0f, 1000.0f);
				}
				ImGui::SliderFloat("Zoom", &(scene.zoom), 1, 10);
				ImGui::SliderFloat("Distance", &(activeCamera->distance), 0, 10);
			}

			if (ImGui::CollapsingHeader("Light"))
			{
				scene.isAddLight = ImGui::Button("AddLight", ImVec2(70, 30));
				scene.isAddParallelLight = false;
				scene.isAddPointLight = false;
				static int lightOption = 0;
				ImGui::RadioButton("Parallel Light", &lightOption, 0); ImGui::SameLine();
				ImGui::RadioButton("Point Light", &lightOption, 1);
				static int c = 0;
				ImGui::RadioButton("LightRotation", &c, 0); ImGui::SameLine();
				ImGui::RadioButton("LightTranslation", &c, 1);
				ImGui::SliderFloat("Ambient level", &(scene.ambientLevel), 0.0f, 1.0f);
				if(scene.isAddLight)
				{
					if(lightOption==0)
						scene.isAddParallelLight = scene.isAddLight;
					else if(lightOption==1)
						scene.isAddPointLight = scene.isAddLight;
				}
				if (lightCount > 0)
				{
					/** Active camera parameters ***/
					Light* activeLight = scene.GetActiveLight();
					ImGui::SliderFloat("L level", &(activeLight->L), 0.0f, 50.0f);
					ImGui::Text("Light parameters");

					if (c == 0)
					{
						ImGui::SliderFloat("Light X rotation", &(activeLight->param->rot_x), -360.0f, 360.0f);
						ImGui::SliderFloat("Light Y rotation", &(activeLight->param->rot_y), -360.0f, 360.0f);
						ImGui::SliderFloat("Light Z rotation", &(activeLight->param->rot_z), -360.0f, 360.0f);
						//scene.isAddParallelLight = scene.isAddLight;

					}
					else if (c == 1)
					{
						ImGui::SliderFloat("Light X translation", &(activeLight->param->trans_x), -1000.0f, 1000.0f);
						ImGui::SliderFloat("Light Y translation", &(activeLight->param->trans_y), -1000.0f, 1000.0f);
						ImGui::SliderFloat("Light Z translation", &(activeLight->param->trans_z), -1000.0f, 1000.0f);
						//scene.isAddPointLight = scene.isAddLight;
					}
				}
			}
		
			if (ImGui::CollapsingHeader("Color"))
			{
				ImGui::ColorEdit3("Edges color", (float*)&(scene.edgesColor));
				ImGui::ColorEdit3("Faces color", (float*)&(scene.facesColor));
				ImGui::ColorEdit3("Grid color", (float*)&(scene.gridColor));
				ImGui::ColorEdit3("Normals color", (float*)&(scene.normalsColor));
				ImGui::ColorEdit3("Bounding Box color", (float*)&(scene.boundingBoxColor));
				ImGui::ColorEdit3("Background color color", (float*)&(scene.beackgroundColor));
			}
			
			static int shade = 0;
			if (ImGui::CollapsingHeader("Shading"))
			{
				ImGui::RadioButton("Flat", &shade, 0);
				ImGui::RadioButton("Gouraud", &shade, 1);
				ImGui::RadioButton("Phong", &shade, 2);
			}
			switch (shade)
			{
			case 0: scene.shadingMode = Scene::Flat; break;
			case 1: scene.shadingMode = Scene::Gouraud; break;
			case 2: scene.shadingMode = Scene::Phong; break;
			}
		}
		ImGui::End();
	}

	// 3. Show another simple window.
	if (showAnotherWindow)
	{
		ImGui::Begin("Another Window", &showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
		{
			showAnotherWindow = false;
		}
		ImGui::End();
	}

	// 4. Demonstrate creating a fullscreen menu bar and populating it.
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoFocusOnAppearing;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Load Model...", "CTRL+O"))
				{
					nfdchar_t *outPath = NULL;
					nfdresult_t result = NFD_OpenDialog("obj;png,jpg", NULL, &outPath);
					if (result == NFD_OKAY) {
						scene.AddModel(Utils::LoadMeshModel(outPath));
						free(outPath);
					}
					else if (result == NFD_CANCEL) {
					}
					else {
					}

				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}
}












/*


ImGui::Text("Demo widgets", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

ImGui::Checkbox("Demo Window", &showDemoWindow);      // Edit bools storing our window open/close state
ImGui::Checkbox("Another Window", &showAnotherWindow);

ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color

if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
counter++;
ImGui::SameLine();
ImGui::Text("counter = %d", counter);

ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
*/