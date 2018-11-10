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

void DrawImguiMenus(ImGuiIO& io, Scene& scene, ModelGeometricParameters& param)
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		ImGui::Begin("Computer Graphic ass. 1");                         
		std::vector<std::string> modelNames = scene.getModelNames();
		int modelsNumber = modelNames.size();
		char** items = new char*[modelsNumber];
		for (int i = 0; i < modelsNumber; ++i)
		{
			items[i] = const_cast<char*>(modelNames[i].c_str());
		}		
		
		ImGui::Combo("combo", &scene.activeModelIndex, items, modelsNumber);            // Display some text (you can use a format strings too)

		ImGui::SliderFloat("X rotation", &param.rot_x, -360.0f, 360.0f);
		ImGui::SliderFloat("Y rotation", &param.rot_y, -360.0f, 360.0f);
		ImGui::SliderFloat("Z rotation", &param.rot_z, -360.0f, 360.0f);
		
		ImGui::SliderFloat("X translation", &param.trans_x, -10.0f, 10.0f);
		ImGui::SliderFloat("Y translation", &param.trans_y, -10.0f, 10.0f);
		ImGui::SliderFloat("Z translation", &param.trans_z, -10.0f, 10.0f);

		ImGui::SliderFloat("X scaling", &param.scale_x, 1.0f, 100.0f);
		ImGui::SliderFloat("Y scaling", &param.scale_y, 1.0f, 100.0f);
		ImGui::SliderFloat("Z scaling", &param.scale_z, 1.0f, 100.0f);

		



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
						scene.AddModel(std::make_shared<MeshModel>(Utils::LoadMeshModel(outPath)));
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