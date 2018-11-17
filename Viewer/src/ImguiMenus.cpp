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
		ImGui::Begin("Computer Graphic ass. 1");                         
		std::vector<std::string> modelNames = scene.getModelNames();
		std::vector<std::string> cameraNames = scene.GetCameraNames();
		int modelsNumber = modelNames.size();
		int cameraCount = scene.GetCameraCount();
		if (modelsNumber > 0)
		{
			char** items = new char*[modelsNumber];
			for (int i = 0; i < modelsNumber; ++i)
			{
				items[i] = const_cast<char*>(modelNames[i].c_str());
			}
			char** cameras = new char*[cameraCount];
			for (int i=0 ; i< cameraCount ;++i)
			{
				cameras[i] = const_cast<char*>(cameraNames[i].c_str());
			}

			scene.isAddCamera = ImGui::Button("AddCamera", ImVec2(70, 30));

			ImGui::Checkbox("Prespective Projection", &scene.isPrespective);

			ImGui::Combo("Select Model", &scene.activeModelIndex, items, modelsNumber); 
			ImGui::Combo("Select Camera", &scene.activeCameraIndex, cameras, cameraCount);

			static int e = 2;
			ImGui::RadioButton("ModelRotation", &e, 0); ImGui::SameLine();
			ImGui::RadioButton("ModelTranslation", &e, 1); ImGui::SameLine();
			ImGui::RadioButton("ModelScaling", &e, 2);


			/** Active model parameters ***/
			MeshModel* activeModel = scene.GetActiveModel();
			ImGui::Text("Model parameters");
			if (e==0)
			{
				ImGui::SliderFloat("Model X rotation", &(activeModel->param->rot_x), -360.0f, 360.0f);
				ImGui::SliderFloat("Model Y rotation", &(activeModel->param->rot_y), -360.0f, 360.0f);
				ImGui::SliderFloat("Model Z rotation", &(activeModel->param->rot_z), -360.0f, 360.0f);
			}
			else if (e==1) {
				ImGui::SliderFloat("Model X translation", &(activeModel->param->trans_x), -1000.0f, 1000.0f);
				ImGui::SliderFloat("Model Y translation", &(activeModel->param->trans_y), -1000.0f, 1000.0f);
				ImGui::SliderFloat("Model Z translation", &(activeModel->param->trans_z), -1000.0f, 1000.0f);
			}
			else if (e==2)
			{
				ImGui::SliderFloat("Model X scaling", &(activeModel->param->scale_x), 0.1f, 100.0f);
				ImGui::SliderFloat("Model Y scaling", &(activeModel->param->scale_y), 0.1f, 100.0f);
				ImGui::SliderFloat("Model Z scaling", &(activeModel->param->scale_z), 0.1f, 100.0f);
			}
			/** Active camera parameters ***/
			Camera* activeCamera = scene.GetActiveCamera();
			ImGui::Text("Camera parameters");
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
			ImGui::SliderFloat("Cameras scale", &(scene.camScale), 1.0f, 100.0f);
			ImGui::Checkbox("Show normals", &scene.isShowNormals);
			ImGui::SliderFloat("Normal scaling", &(scene.scaleNormalLength),0.001,2);
			ImGui::ColorEdit3("Model color", (float*)&(scene.modelColor)); 
			ImGui::ColorEdit3("Grid color", (float*)&(scene.gridColor)); 
			ImGui::ColorEdit3("Normals color", (float*)&(scene.normalsColor)); 
			ImGui::ColorEdit3("Bounding Box color", (float*)&(scene.boundingBoxColor)); 
			

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