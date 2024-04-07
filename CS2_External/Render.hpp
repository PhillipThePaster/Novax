#pragma once
#define _USE_MATH_DEFINES
#include <chrono>
#include <map>
#include "Entity.h"
#include "MenuConfig.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "OS-ImGui/imgui/imgui_internal.h"

namespace Render {

	ImColor LerpColor(const ImColor& startColor, const ImColor& endColor, float t) {
		float r = startColor.Value.x + (endColor.Value.x - startColor.Value.x) * t;
		float g = startColor.Value.y + (endColor.Value.y - startColor.Value.y) * t;
		float b = startColor.Value.z + (endColor.Value.z - startColor.Value.z) * t;
		float a = startColor.Value.w + (endColor.Value.w - startColor.Value.w) * t;
		return ImColor(r, g, b, a);
	}

	void DrawFovCircle(const CEntity& LocalEntity) {
		auto& viewAngles = LocalEntity.Pawn.ViewAngle;
		Vec2 punchAngle = LocalEntity.Pawn.AimPunchAngle;
		Vec2 CenterPoint = Gui.Window.Size / 2;

		if (LocalEntity.Pawn.ShotsFired && Config::RecoilFov) {
			CenterPoint.x -= Gui.Window.Size.x / 90 * punchAngle.y;
			CenterPoint.y += Gui.Window.Size.y / 90 * punchAngle.x;
		}

		float Radius = tan(AimControl::AimFov / 180.f * M_PI / 2.f) * Gui.Window.Size.x;
		Gui.Circle(CenterPoint, Radius, ImColor(0, 0, 0, 255), 4);
		Gui.Circle(CenterPoint, Radius, Config::AimFovRangeColor, 2);
	}


	void DrawCrossHair(ImDrawList* drawList, ImU32 color, const CEntity& LocalEntity) noexcept {
		float Thickness = CrosshairConfig::Thickness;
		int BorderWidth = 2, DotSize = 1, gap = CrosshairConfig::Gap / 2, outlineGap = gap - 1;


		auto& viewAngles = LocalEntity.Pawn.ViewAngle;
		Vec2 punchAngle = LocalEntity.Pawn.AimPunchAngle;
		Vec2 pos = Gui.Window.Size / 2;


		if (LocalEntity.Pawn.ShotsFired && CrosshairConfig::RecoilCrosshair) {
			pos.x -= Gui.Window.Size.x / 90 * punchAngle.y;
			pos.y += Gui.Window.Size.y / 90 * punchAngle.x;
		}

		ImVec2 offset1{ CrosshairConfig::DotSize,CrosshairConfig::DotSize };
		ImVec2 offset2{ CrosshairConfig::DotSize + 1,CrosshairConfig::DotSize + 1 };

		if (CrosshairConfig::drawOutLine) {
			if (CrosshairConfig::drawDot) drawList->AddRectFilled(ImVec2(pos.x - offset1.x, pos.y - offset1.y), ImVec2(pos.x + offset2.x, pos.y + offset2.y), color & IM_COL32_A_MASK);//dot
			if (CrosshairConfig::drawOutLine) {
				drawList->AddRectFilled(ImVec2(pos.x - (outlineGap + BorderWidth + CrosshairConfig::HorizontalLength), pos.y - Thickness), ImVec2(pos.x - outlineGap, pos.y + 1 + Thickness), color & IM_COL32_A_MASK);//left
				drawList->AddRectFilled(ImVec2(pos.x + (outlineGap + DotSize), pos.y - Thickness), ImVec2(pos.x + (outlineGap + DotSize + BorderWidth + CrosshairConfig::HorizontalLength), pos.y + 1 + Thickness), color & IM_COL32_A_MASK);//right
				if (!CrosshairConfig::tStyle) drawList->AddRectFilled(ImVec2(pos.x - Thickness, pos.y - (outlineGap + BorderWidth + CrosshairConfig::VerticalLength)), ImVec2(pos.x + 1 + Thickness, pos.y - outlineGap), color & IM_COL32_A_MASK);//top
				drawList->AddRectFilled(ImVec2(pos.x - Thickness, pos.y + outlineGap + DotSize), ImVec2(pos.x + 1 + Thickness, pos.y + (outlineGap + DotSize + BorderWidth + CrosshairConfig::VerticalLength)), color & IM_COL32_A_MASK);//bottom
			}
		}
		if (CrosshairConfig::drawDot) drawList->AddRectFilled(ImVec2(pos.x - offset1.x + DotSize, pos.y - offset1.y + DotSize), ImVec2(pos.x + offset1.x, pos.y + offset1.y), color);// dot
		drawList->AddRectFilled(ImVec2(pos.x - (gap + CrosshairConfig::HorizontalLength), pos.y - Thickness + 1), ImVec2(pos.x - gap, pos.y + Thickness), color);// left
		drawList->AddRectFilled(ImVec2(pos.x + gap + DotSize, pos.y - Thickness + 1), ImVec2(pos.x + (gap + DotSize + CrosshairConfig::HorizontalLength), pos.y + Thickness), color);// right
		if (!CrosshairConfig::tStyle) drawList->AddRectFilled(ImVec2(pos.x - Thickness + 1, pos.y - (gap + CrosshairConfig::VerticalLength)), ImVec2(pos.x + Thickness, pos.y - gap), color);// top
		drawList->AddRectFilled(ImVec2(pos.x - Thickness + 1, pos.y + gap + DotSize), ImVec2(pos.x + Thickness, pos.y + (gap + DotSize + CrosshairConfig::VerticalLength)), color);// bottom
	}



	// menu crosshair

	void Debug_List(const CEntity& LocalEntity) {

		const float PI = 3.14159265358979323846;
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		const char* teamNames[] = { "", "Spectate", "Terrorist", "Counter-Terrorist" };
		std::ostringstream Debug_Text;

		Debug_Text << "Name: " << LocalEntity.Controller.PlayerName << "\n";
		Debug_Text << "Ping: " << LocalEntity.Controller.Ping << "\n";
		Debug_Text << "Health: " << LocalEntity.Pawn.Health << "\n";
		Debug_Text << "Position: (" << LocalEntity.Pawn.Pos.x << ", " << LocalEntity.Pawn.Pos.y << ", " << LocalEntity.Pawn.Pos.z << ")\n";
		Debug_Text << "Ammo: " << LocalEntity.Pawn.Ammo << "  Maxammo: " << LocalEntity.Pawn.MaxAmmo << "\n";
		Debug_Text << "Scoped: " << (LocalEntity.Pawn.Scoped == 1 ? "Scoped" : "False") << "\n";
		Debug_Text << "Money: " << LocalEntity.Controller.Money << "\n";
		Debug_Text << "Team: " << teamNames[LocalEntity.Controller.TeamID] << "\n";
		Debug_Text << "State: " << (LocalEntity.Controller.AliveStatus == 1 ? "Alive" : "Dead") << "\n";
		Debug_Text << "Helmet: " << (LocalEntity.Controller.HasHelmet == 1 ? "True" : "False") << "\n";
		//Debug_Text << "Velocity: " << LocalEntity.Pawn.Velocity << "\n"; // broken
		Debug_Text << "Weapon: " << LocalEntity.Pawn.WeaponName << "\n";
		const char* weaponGroupNames[] = { "Knife", "Rifle", "Pistol", "Heavy Pistol", "Sniper", "SMG", "Shotgun", "Grenade", "Zeus","Unkown" };
		int weaponGroup = GetWeaponGroup(LocalEntity.Pawn.WeaponName);
		const char* weaponGroupName = (weaponGroup >= 0 && weaponGroup < sizeof(weaponGroupNames) / sizeof(weaponGroupNames[0])) ? weaponGroupNames[weaponGroup] : "Unknown";

		Debug_Text << "Group: " << weaponGroupName << "\n";
		Debug_Text << "Groupid: " << weaponGroup << "\n";


		const std::string fullInfo = Debug_Text.str();

		const ImVec2 cal_text = ImGui::CalcTextSize(fullInfo.c_str());

		ImGui::SetNextWindowSize(ImVec2(cal_text.x + 10, cal_text.y + 10));
		ImGui::Begin("##WM", NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground); {
			auto p = ImGui::GetWindowPos();
			const ImColor bg_clr(30, 30, 30, 255), line_clr(Config::Accent), text_clr(255, 255, 255, 255);

			drawList->AddRectFilled(p, ImVec2(p.x + cal_text.x + 10, p.y + cal_text.y + 10), bg_clr);
			drawList->AddRect(p, ImVec2(p.x + cal_text.x + 10, p.y + cal_text.y + 10), ImColor(30, 30, 30,255), 0.f, 0, 5.f);
			drawList->AddRect(p, ImVec2(p.x + cal_text.x + 10, p.y + cal_text.y + 10), ImColor(60,60,60,255),0.f,0,3.f);
			drawList->AddRectFilled(p, ImVec2(p.x + cal_text.x + 9, p.y + 1), line_clr);
			drawList->AddText(ImVec2(p.x + 5, p.y + 6), text_clr, fullInfo.c_str());
		}
		ImGui::End();
	}


	// DOGSHIT CODE unfinished
	// need to style it more and optimize it i just copied the debug list function and changed it slightly
	/*
	void Keybind_List() {

		const float PI = 3.14159265358979323846;
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		std::ostringstream Debug_Text;

		if (Config::AimBot) Debug_Text << "Aimbot" << (GetAsyncKeyState(Config::AimBotHotKey) ? "   [ Held ]" : "") << "\n";
		if (Config::TriggerBot) Debug_Text << "Triggerbot" << (GetAsyncKeyState(Config::TriggerHotKey) ? "   [ Held ]" : "") << "\n";


		const std::string fullInfo = Debug_Text.str();

		const ImVec2 cal_text = ImGui::CalcTextSize(fullInfo.c_str());

		ImGui::SetNextWindowSize(ImVec2(cal_text.x + 10, cal_text.y + 10));
		ImGui::Begin("##Keybinds", NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground); {
			auto p = ImGui::GetWindowPos();
			const ImColor bg_clr(30, 30, 30, 255), line_clr(Config::Accent), text_clr(255, 255, 255, 255);

			drawList->AddRectFilled(p, ImVec2(p.x + cal_text.x + 10, p.y + cal_text.y + 10), bg_clr);
			drawList->AddRect(p, ImVec2(p.x + cal_text.x + 10, p.y + cal_text.y + 10), ImColor(30, 30, 30, 255), 0.f, 0, 5.f);
			drawList->AddRect(p, ImVec2(p.x + cal_text.x + 10, p.y + cal_text.y + 10), ImColor(60, 60, 60, 255), 0.f, 0, 3.f);
			drawList->AddRectFilled(p, ImVec2(p.x + cal_text.x + 9, p.y + 1), line_clr);
			drawList->AddText(ImVec2(p.x + 5, p.y + 6), text_clr, fullInfo.c_str());
		}
		ImGui::End();
	}
	*/

	void SpedGraph(const std::vector<float>& values, const ImVec2& graphPos, const ImVec2& graphSize, float minValue, float maxValue, ImColor lineColor) {

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		drawList->AddRectFilled(graphPos, ImVec2(graphPos.x + graphSize.x, graphPos.y + graphSize.y), IM_COL32(20, 20, 20, 10));

		if (values.size() > 1) {
			float xIncr = graphSize.x / (values.size() - 1);
			float x = graphPos.x;
			float yScale = graphSize.y / (maxValue - minValue);

			for (size_t i = 1; i < values.size(); ++i) {
				float xPrev = x;
				float yPrev = graphPos.y + graphSize.y - (values[i - 1] - minValue) * yScale;
				x += xIncr;
				float y = graphPos.y + graphSize.y - (values[i] - minValue) * yScale;
				drawList->AddLine(ImVec2(xPrev, yPrev), ImVec2(x, y), lineColor, 1.2f);
			}
		}
	}


	void MovementIndicators(const CEntity& LocalEntity) {
		uintptr_t MovementServices;

		static int maxVelocity = 0;
		int currentVelocity = LocalEntity.Pawn.Velocity;

		float lerpValue = (currentVelocity - 50) / 245.0f;
		lerpValue = fminf(fmaxf(lerpValue, 0.0f), 1.0f);

		//float Stamina = 0;
		//int Stam = static_cast<int>(80 - Stamina);

		static std::vector<float> speedHistory;
		speedHistory.push_back(static_cast<float>(currentVelocity));
		struct info_t { std::string inf; ImVec2 pos; ImColor col; };
		std::vector<info_t> info;


		if (currentVelocity > maxVelocity)
			maxVelocity = currentVelocity;

		if (speedHistory.size() > 100)
			speedHistory.erase(speedHistory.begin());

		if (Config::VelocityGraph) {
			SpedGraph(speedHistory, ImVec2((Gui.Window.Size.x) / 2 - 150, (Gui.Window.Size.y) / 1.6 + 19), ImVec2(300, 103), 0, maxVelocity + 10, Config::GraphLineColor);

			Gui.Line(ImVec2((Gui.Window.Size.x) / 2 - 150, (Gui.Window.Size.y) / 1.4 - 7), ImVec2((Gui.Window.Size.x) / 2 + 150, (Gui.Window.Size.y) / 1.4 - 7), ImColor(255, 255, 255), 1.5f);
			Gui.Line(ImVec2((Gui.Window.Size.x) / 2 - 150, (Gui.Window.Size.y) / 1.4 - 110), ImVec2((Gui.Window.Size.x) / 2 - 150, (Gui.Window.Size.y) / 1.4 - 7), ImColor(255, 255, 255), 1.5f);
		}

		//ProcessMgr.ReadMemory(LocalEntity.Pawn.Address + Offset::Pawn.MovementServices, MovementServices);
		//ProcessMgr.ReadMemory(MovementServices + Offset::Pawn.m_flStamina, Stamina);

		info.clear();

		ImColor textColor;
		if (currentVelocity >= 390)
			textColor = ImColor(255, 0, 0);
		else if (currentVelocity >= 330)
			textColor = LerpColor(ImColor(255, 165, 0), ImColor(255, 0, 0), (currentVelocity - 295) / 35.0f);
		else if (currentVelocity >= 250)
			textColor = LerpColor(ImColor(0, 255, 0), ImColor(255, 165, 0), lerpValue);
		else
			textColor = LerpColor(ImColor(255, 255, 255), ImColor(0, 255, 0), currentVelocity / 50.0f);

		if (Config::VelocityIndicator) info.push_back({ ((Config::VelocityIndicator) ? std::to_string(currentVelocity) + " " : "") + ((Config::MaxVelocity) ? "(" + std::to_string(maxVelocity) + ")" : ""), ImVec2((Gui.Window.Size.x) / 2, (Gui.Window.Size.y) / 1.4), textColor });

		//info.push_back({ std::to_string(Stam), ImVec2((Gui.Window.Size.x) / 2, (Gui.Window.Size.y) / 1.4 + 30), ImColor(0, 255, 0) });

		for (auto& entry : info) {
			std::transform(entry.inf.begin(), entry.inf.end(), entry.inf.begin(), ::toupper);
			Gui.StrokeText(entry.inf.c_str(), entry.pos, entry.col, 22.f, true);
		}
	}
	void Keystrokes() {
		if (!Config::KeyStrokes)
			return;

		bool pressed[5];
		char keys[] = { 'W', 'S', 'A', 'D', ' ' };
		ImVec2 positions[] = {
			ImVec2((Gui.Window.Size.x) / 2.4, (Gui.Window.Size.y) / 1.5),
			ImVec2((Gui.Window.Size.x) / 2.4, (Gui.Window.Size.y) / 1.5 + 20),
			ImVec2((Gui.Window.Size.x) / 2.4 - 20, (Gui.Window.Size.y) / 1.5 + 20),
			ImVec2((Gui.Window.Size.x) / 2.4 + 20, (Gui.Window.Size.y) / 1.5 + 20),
			ImVec2((Gui.Window.Size.x) / 2.4, (Gui.Window.Size.y) / 1.5 + 40)
		};
		const char* names[] = { "W", "S", "A", "D", "Space" };

		for (int i = 0; i < 5; ++i)
			pressed[i] = GetAsyncKeyState(keys[i]) & 0x8000;

		ImColor Pressed = Config::KeystrokeColor, UnPressed = ImColor(255, 255, 255);

		if (Config::KeystrokeStyle == 1) {
			for (int i = 0; i < 5; ++i) {
				const char* displayText = (keys[i] == ' ') ? (pressed[i] ? "Space" : "-----") : (pressed[i] ? names[i] : "-");
				Gui.StrokeText(displayText, positions[i], UnPressed, 24.f, true);
			}
		}
		else if (Config::KeystrokeStyle == 0) {
			for (int i = 0; i < 5; ++i) {
				Gui.StrokeText(names[i], positions[i], pressed[i] ? Pressed : UnPressed, 24.f, true);
			}
		}
	}



	// not finished dont say its bad
	void SlowedIndicator(const CEntity& Local) {
		if (!Config::SlowedIndicator || Local.Pawn.Health <= 0)
			return;

		float vel = 0;
		ProcessMgr.ReadMemory(Local.Pawn.Address + Offset::Pawn.m_flVelocityModifier, vel);

		float lerpedValue = (vel >= 0.99f) ? 1 : std::clamp(vel, 0.f, 1.f);
		ImColor lerpedColor = LerpColor(ImColor(255, 0, 0), ImColor(0, 255, 0), lerpedValue);

		std::string velocityText = "Slowed Down: " + std::to_string(static_cast<int>(vel * 100.f));

		const ImVec2 cal_text = ImGui::CalcTextSize(velocityText.c_str());

		ImGui::SetNextWindowSize(ImVec2(cal_text.x + 50, cal_text.y - 200));
		ImGui::Begin("##SLOWE", NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground); {
			auto p = ImGui::GetWindowPos();
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(p.x + 1 ,p.y + 20), ImVec2(p.x + 151, p.y + 31), IM_COL32(20, 20, 20, 255));
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(p.x ,p.y + 21), ImVec2(p.x + lerpedValue * 150, p.y + 30), lerpedColor);
			Gui.StrokeText(velocityText, ImVec2(p.x - 3, p.y - 3), lerpedColor, 20.f, false);

		}
		ImGui::End();
	}


	void SpectatorList(const CEntity& Local, const CEntity& Entity) {
		if (!Config::SpecList)
			return;

		std::vector<std::string> spectators;

		uintptr_t l_pawn, l_observe, l_spec;
		ProcessMgr.ReadMemory(Entity.Controller.Address + Offset::PlayerController.m_pObserverServices, l_pawn);
		ProcessMgr.ReadMemory(l_pawn + Offset::PlayerController.m_hObserverTarget, l_observe);
		ProcessMgr.ReadMemory(l_observe + Offset::PlayerController.m_hController, l_spec);

		if (l_observe == Local.Pawn.Address) {
			spectators.push_back(Entity.Controller.PlayerName);
		}

		if (spectators.empty())
			return;

		for (size_t i{}; i < spectators.size(); ++i) {
			auto msg = spectators[i];
			Gui.StrokeText(msg.substr(0, 24), ImVec2(Gui.Window.Size.x / 2, Gui.Window.Size.y / 2), 18.f, true);
		}
	}



	// unfinished
	/*
	void SpectatorList(const CEntity& Local , const CEntity& Entity) {
		if (!Config::SpecList)
			return;

		std::vector<std::string> spectators;

		uintptr_t l_pawn, l_observe, l_spec;
		ProcessMgr.ReadMemory(Local.Controller.Address + Offset::PlayerController.m_pObserverServices, l_pawn);
		ProcessMgr.ReadMemory(l_pawn + Offset::PlayerController.m_hObserverTarget, l_observe);
		ProcessMgr.ReadMemory(l_observe + Offset::PlayerController.m_hController, l_spec);

		if (l_observe == Local.Pawn.Address) {
			spectators.push_back(Entity.Controller.PlayerName);
		}

		if (spectators.empty())
			return;


		for (size_t i{}; i < spectators.size(); ++i) {
			auto msg = spectators[i];
			Gui.StrokeText(msg.substr(0, 24), ImVec2(Gui.Window.Size.x / 2, Gui.Window.Size.y / 2), 18.f, true);

		}

	}
	*/

	// shit code dont use it
	/*
	void DroppedEsp(const CEntity& Entity) {

		for (int i = 65; i < 1024; i++) {
			uintptr_t entity_uint;
			ProcessMgr.ReadMemory(Entity.Pawn.Address + 0x10, entity_uint);

			uintptr_t designerNameAddy;
			ProcessMgr.ReadMemory(entity_uint + 0x20, designerNameAddy);

			char designerNameBuffer[MAX_PATH]{};
			ProcessMgr.ReadMemory(designerNameAddy, designerNameBuffer, MAX_PATH);


			std::string name = std::string(designerNameBuffer);

			if (strstr(name.c_str(), "weapon_")) name.erase(0, 7);
			else if (strstr(name.c_str(), "_projectile")) name.erase(name.length() - 11, 11);
			else if (strstr(name.c_str(), "baseanimgraph")) name = "defuse kit";
			else continue;


			name = Entity.Pawn.WeaponName;

			Gui.StrokeText(name.c_str(), ImVec2(Entity.Pawn.Pos.x, Entity.Pawn.Pos.y), ImColor(255, 255, 255, 255), 16.f, true);
		}
	}
	*/





		
	// dont mind this janky code
	void SpreadCircle(float Spread) {
		if (!Config::SpreadCircle)
			return;
		Gui.CircleGradient(ImVec2(Gui.Window.Size.x / 2, Gui.Window.Size.y / 2), Spread, ImColor(255, 255, 255, 0), Config::SpreadCircleColor);
	}

	// just temp might make a actual rendering file without osimgui 
	// useless code im just doing smth
	// voxel is just a square using poly lines and makes a voxel like apperance
	void voxel(Vec3 Pos, Vec3 dimensions, bool filled, ImColor clr, float Thickness) {
		std::vector<Vec3> vertices = {
			{dimensions.x / 2, dimensions.y / 2, dimensions.z / 2},   // Top right front
			{-dimensions.x / 2, dimensions.y / 2, dimensions.z / 2},  // Top left front
			{-dimensions.x / 2, -dimensions.y / 2, dimensions.z / 2}, // Bottom left front
			{dimensions.x / 2, -dimensions.y / 2, dimensions.z / 2},  // Bottom right front
			{dimensions.x / 2, dimensions.y / 2, -dimensions.z / 2},  // Top right back
			{-dimensions.x / 2, dimensions.y / 2, -dimensions.z / 2}, // Top left back
			{-dimensions.x / 2, -dimensions.y / 2, -dimensions.z / 2},// Bottom left back
			{dimensions.x / 2, -dimensions.y / 2, -dimensions.z / 2}  // Bottom right back
		};

		std::vector<ImVec2> points;

		for (int i = 0; i < 4; ++i) {
			Vec2 point2d;
			if (gGame.View.WorldToScreen(Pos + vertices[i], point2d))
				points.push_back(ImVec2(point2d.x, point2d.y));
		}
		points.push_back(points[0]); 

		for (int i = 0; i < 4; ++i) {
			Vec2 point2d;
			if (gGame.View.WorldToScreen(Pos + vertices[i], point2d))
				points.push_back(ImVec2(point2d.x, point2d.y));
			if (gGame.View.WorldToScreen(Pos + vertices[i + 4], point2d))
				points.push_back(ImVec2(point2d.x, point2d.y));
		}
		points.push_back(points[4]); 

		for (int i = 4; i < 8; ++i) {
			Vec2 point2d;
			if (gGame.View.WorldToScreen(Pos + vertices[i], point2d))
				points.push_back(ImVec2(point2d.x, point2d.y));
		}
		points.push_back(points[6]);

		if (filled)
			ImGui::GetBackgroundDrawList()->AddConvexPolyFilled(points.data(), points.size(), ImColor(clr.Value.x, clr.Value.y, clr.Value.z, clr.Value.w * 0.7f));
		ImGui::GetBackgroundDrawList()->AddPolyline(points.data(), points.size(), clr, true, Thickness);
	}


	// just a voxel that doesnt have connecting sides
	void Square3D(Vec3 Pos, Vec3 dimensions, ImColor clr, float Thickness) {
		std::vector<Vec3> vertices = {
			{dimensions.x / 2, dimensions.y / 2, dimensions.z / 2},   // Top right front
			{-dimensions.x / 2, dimensions.y / 2, dimensions.z / 2},  // Top left front
			{-dimensions.x / 2, -dimensions.y / 2, dimensions.z / 2}, // Bottom left front
			{dimensions.x / 2, -dimensions.y / 2, dimensions.z / 2},  // Bottom right front
			{dimensions.x / 2, dimensions.y / 2, -dimensions.z / 2},  // Top right back
			{-dimensions.x / 2, dimensions.y / 2, -dimensions.z / 2}, // Top left back
			{-dimensions.x / 2, -dimensions.y / 2, -dimensions.z / 2},// Bottom left back
			{dimensions.x / 2, -dimensions.y / 2, -dimensions.z / 2}  // Bottom right back
		};

		auto addLine = [&](const Vec3& v1, const Vec3& v2) {
			Vec2 p1, p2;
			if (gGame.View.WorldToScreen(Pos + v1, p1) && gGame.View.WorldToScreen(Pos + v2, p2))
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(p1.x, p1.y), ImVec2(p2.x, p2.y), clr, Thickness);
		};

		for (int i = 0; i < 4; ++i) {
			addLine(vertices[i], vertices[(i + 1) % 4]);
			addLine(vertices[i + 4], vertices[(i + 1) % 4 + 4]);
			addLine(vertices[i], vertices[i + 4]);
		}
	}


	// 3d circle pretty self explaintory
	void Circle3D(Vec3 Pos, float radius, bool filled, ImColor clr, float Thickness) {
		static constexpr float Step = M_PI * 2.0f / 25;
		std::vector<ImVec2> points;
		for (float lat = 0.f; lat <= M_PI * 2.0f; lat += Step)
		{
			const auto& point3d = Vec3(sin(lat), cos(lat), 0.f) * radius;
			Vec2 point2d;
			if (gGame.View.WorldToScreen(Pos + point3d, point2d))
				points.push_back(ImVec2(point2d.x, point2d.y));
		}
		if (filled)
			ImGui::GetBackgroundDrawList()->AddConvexPolyFilled(points.data(), points.size(), ImColor(clr.Value.x, clr.Value.y, clr.Value.z, clr.Value.w * 0.7f));

		ImGui::GetBackgroundDrawList()->AddPolyline(points.data(), points.size(), clr, true, Thickness);
	}


	void TaserRange(const CEntity& Local, const CEntity& Entity) {
		if (Local.Pawn.WeaponName == "zeus") {
			if (Config::zeusRange)
				Render::Circle3D(Local.Pawn.Pos, 200, false, Config::zeusRangeColor, 0.5f);
			if (Entity.Pawn.Pos.DistanceTo(Local.Pawn.Pos) < 200 && Config::zeusTarget)
				Render::Circle3D(Entity.Pawn.Pos, 20, false, Config::zeusTargetColor, 2.f);
		}
	}

}