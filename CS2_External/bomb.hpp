#pragma once
#include <chrono>
#include <iostream>
#include <utility>
#include <sstream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <iomanip>

#include <cmath>

#include "../CS2_External/Entity.h"
#include "../CS2_External/MenuConfig.hpp"


// ICE CREAM U NEED TO FIX THE GARBAGE
namespace bmb
{
	bool isPlanted = false;

	void RenderBombIcon() {
		uintptr_t cPlantedC4;
		uintptr_t c4Node;
		Vec3 c4Origin;

		ProcessMgr.ReadMemory(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4);
		if (!ProcessMgr.ReadMemory<uintptr_t>(gGame.GetClientDLLAddress() + Offset::PlantedC4, cPlantedC4))
			return;

		if (!ProcessMgr.ReadMemory<uintptr_t>(cPlantedC4, cPlantedC4))
			return;

		ProcessMgr.ReadMemory<uintptr_t>(cPlantedC4 + Offset::bomb.m_pGameSceneNode, c4Node);

		ProcessMgr.ReadMemory<Vec3>(c4Node + Offset::bomb.m_vecAbsOrigin, c4Origin);

		Vec2 screenPos;

		if (gGame.View.WorldToScreen(c4Origin, screenPos) && cPlantedC4) {
			ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
			Gui.StrokeText("o", ImVec2(screenPos.x - 10, screenPos.y - 12), ImColor(255, 255, 255, 255), 28);
			ImGui::PopFont();
		}
	}

	// disabled till i add C4Fullblow - Phillip
	/*
	void RenderWindow(){

	}
	*/
}