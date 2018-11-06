#pragma once
#include <imgui/imgui.h>
#include "Scene.h"
#include "../../build/ModelGeometricParameters.h"

void DrawImguiMenus(ImGuiIO& io, Scene& scene, ModelGeometricParameters& param);
const glm::vec4& GetClearColor();
