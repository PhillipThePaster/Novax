#include "Cheats.h"
#include "Theme.h"
#include "configsystem.h"
#include "Misc.hpp"
#include "Esp.hpp"
#include "Render.hpp"
#include "bomb.hpp"
#include "images.h"
#include "animation_lib.hpp"
#include "math.hpp"
#include "WorldEsp.hpp"

bool uiS = true;
char inputText[256] = "";
float windowBg = 0.0f;


ID3D11ShaderResourceView* Head = NULL;
ID3D11ShaderResourceView* Body = NULL;
ID3D11ShaderResourceView* Legs = NULL;
ID3D11ShaderResourceView* r_arm = NULL;
ID3D11ShaderResourceView* l_arm = NULL;


ID3D11ShaderResourceView* EspPreview = NULL;


float pos1 = 0, pos2 = 0,pos3 = 0,pos4 = 0; // positioning code i use

int LogoW = 0, LogoH = 0;


int HeadW = 0, HeadH = 0;
int BodyW = 0, BodyH = 0;
int LegsW = 0, LegsH = 0;
int r_armW = 0, r_armH = 0;
int l_armW = 0, l_armH = 0;

const char* items[] = { "Money", "Lethal", "Flashed", "Hk", "Defuser", "Scoped", "Defusing", "Distance", "Ping", "Visible"};
const char* Hitpos[] = { "Head", "Neck",  "Chest", "Stomach" , "Pelvis" };

const char* labels[] = { "General", "W", "G", "A", "Z", "L" };
const float widths[] = { 6.02f, 5.02f, 4.02f, 3.02f, 2.02f, 1.0f };

const char* Wsettings[] = { "Name", "Fps", "Time", "Username", "Build"};


int currentTab = 0;
static int tabb = 0;
int vistab = 0;
static int WeaponTab = 0;


void ButtonColor(int r, int g, int b) {
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Button] = ImColor(r, g, b);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(r, g, b);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(r, g, b);
}


ImColor ColorMix(ImColor Col_1, ImColor Col_2, float t) {
	ImColor Col;
	Col.Value.x = t * Col_1.Value.x + (1 - t) * Col_2.Value.x;
	Col.Value.y = t * Col_1.Value.y + (1 - t) * Col_2.Value.y;
	Col.Value.z = t * Col_1.Value.z + (1 - t) * Col_2.Value.z;
	Col.Value.w = Col_1.Value.w;
	return Col;
}

void ToolTip(const char* tooltipText) {
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("%s", tooltipText);
	}
}

static void HotKey(int* k){
	static bool waitingforkey = false;
	if (waitingforkey == false) {
		if (ImGui::Button(KeyNames[*k]))
			waitingforkey = true;
	}
	else if (waitingforkey == true) {
		ImGui::Button("...");
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
		for (auto& Key : KeyCodes)
		{
			if (GetAsyncKeyState(Key)) {
				*k = Key;
				waitingforkey = false;
			}
		}
	}
}

void visuals_preview() {

	if (EspPreview == NULL) {
		Gui.LoadTextureFromMemory(Images::EspPreview, sizeof Images::EspPreview, &EspPreview, &LogoW, &LogoH);
	}

	const auto cur_window = ImGui::GetCurrentWindow();
	const ImVec2 window_center = ImVec2(cur_window->Pos.x + cur_window->Size.x * 0.17f, cur_window->Pos.y + cur_window->Size.y * 0.01f);
	const ImVec2 w_pos = window_center;

	ImVec2 p = ImGui::GetCursorScreenPos();
	ImColor c = ImColor(32, 114, 247);

	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(p.x - 7, p.y + 15), ImVec2(p.x + ImGui::GetWindowWidth() - 9, p.y - 24), ImColor(30, 30, 30));
	ImGui::GetForegroundDrawList()->AddRectFilledMultiColor(ImVec2(p.x - 7, p.y + 15), ImVec2(p.x + ImGui::GetWindowWidth() - 9, p.y + 16), ImColor(167, 24, 71, 255), Config::Accent, Config::Accent, ImColor(167, 24, 71, 255));
	ImGui::GetForegroundDrawList()->AddText({ p.x + ImGui::GetContentRegionAvail().x * 0.385f, p.y - 12 }, IM_COL32_WHITE, "visuals preview");

	const auto vList = ImGui::GetWindowDrawList();

	ImGui::SetCursorPos(ImVec2(117.f, 86.f));
	ImGui::Image((void*)EspPreview, ImVec2(LogoW - 55, LogoH - 230));

	ImU32 boneColor = Config::BoneColor;
	//bonepoints
	ImVec2 skeletonStart = ImVec2(w_pos.x + 121, w_pos.y + 210);
	ImVec2 neck = ImVec2(skeletonStart.x, skeletonStart.y - 90);
	ImVec2 stomach = ImVec2(skeletonStart.x + 4, skeletonStart.y - 13);
	ImVec2 l_shoulder = ImVec2(skeletonStart.x + 34, skeletonStart.y - 88);
	ImVec2 l_upper_arm = ImVec2(skeletonStart.x + 19, skeletonStart.y - 66);
	ImVec2 l_lower_arm = ImVec2(skeletonStart.x - 14, skeletonStart.y - 78);
	ImVec2 r_shoulder = ImVec2(skeletonStart.x - 21, skeletonStart.y - 82);
	ImVec2 r_upper_arm = ImVec2(skeletonStart.x - 43, skeletonStart.y - 59);
	ImVec2 r_lower_arm = ImVec2(skeletonStart.x - 24, skeletonStart.y - 71);
	ImVec2 l_pelvis = ImVec2(skeletonStart.x + 17, skeletonStart.y + 7);
	ImVec2 l_upper_leg = ImVec2(skeletonStart.x + 16, skeletonStart.y + 52);
	ImVec2 l_lower_leg = ImVec2(skeletonStart.x + 32, skeletonStart.y + 126);
	ImVec2 r_pelivs = ImVec2(skeletonStart.x - 19, skeletonStart.y + 14);
	ImVec2 r_upper_leg = ImVec2(skeletonStart.x - 26, skeletonStart.y + 56);
	ImVec2 r_lower_leg = ImVec2(skeletonStart.x - 20, skeletonStart.y + 106);


	if (Config::HeadCircle) {
		Config::HeadStyle == 0 ? vList->AddCircle(ImVec2(w_pos.x + 120, w_pos.y + 100), 20.f, Config::HeadColor, 25.f, 1.4f) : vList->AddCircleFilled(ImVec2(neck.x, neck.y - 20), 20.f, Config::HeadColor, 25);
	}

	if (Config::Skeleton) {
		vList->AddLine(neck, stomach, boneColor, 1.4f); //back
		vList->AddLine(neck, l_shoulder, boneColor, 1.4f); //l_shoulder
		vList->AddLine(l_shoulder, l_upper_arm, boneColor, 1.4f); //l_upper_arm
		vList->AddLine(l_upper_arm, l_lower_arm, boneColor, 1.4f); //l_lower_arm
		vList->AddLine(neck, r_shoulder, boneColor, 1.4f); //r_shoulder
		vList->AddLine(r_shoulder, r_upper_arm, boneColor, 1.4f); //r_upper_arm
		vList->AddLine(r_upper_arm, r_lower_arm, boneColor, 1.4f); //r_lower_arm
		vList->AddLine(stomach, l_pelvis, boneColor, 1.4f); //l_pelvis
		vList->AddLine(l_pelvis, l_upper_leg, boneColor, 1.4f); //l_upper_leg
		vList->AddLine(l_upper_leg, l_lower_leg, boneColor, 1.4f); //l_upper_leg
		vList->AddLine(stomach, r_pelivs, boneColor, 1.4f); //r_pelivs
		vList->AddLine(r_pelivs, r_upper_leg, boneColor, 1.4f); //r_upper_leg
		vList->AddLine(r_upper_leg, r_lower_leg, boneColor, 1.4f); //r_lower_leg
	}


	if (Config::FilledBox) {
		if (Config::BoxFillType == 0) {
			vList->AddRectFilled(ImVec2(w_pos.x + 40, w_pos.y + 70), ImVec2(w_pos.x + 200, w_pos.y + 370), Config::BoxFilledColor);
		}
		else if (Config::BoxFillType == 1) {
			ImU32 color = IM_COL32(ImColor(Config::BoxFilledColor).Value.x * 255, ImColor(Config::BoxFilledColor).Value.y * 255, ImColor(Config::BoxFilledColor).Value.z * 255, 0), colorTop = IM_COL32(ImColor(Config::BoxFilledColor).Value.x * 255, ImColor(Config::BoxFilledColor).Value.y * 255, ImColor(Config::BoxFilledColor).Value.z * 255, 130);
			vList->AddRectFilledMultiColor(ImVec2(w_pos.x + 40, w_pos.y + 70), ImVec2(w_pos.x + 200, w_pos.y + 370), color, color, colorTop, colorTop);
		}
	}

	if (Config::ShowBoxESP && Config::BoxType == 0) cur_window->DrawList->AddRect(ImVec2(w_pos.x + 40, w_pos.y + 70), ImVec2(w_pos.x + 200, w_pos.y + 370), Config::BoxColor);
	if (Config::ShowBoxESP && Config::BoxType == 1) {
		float space = 80.f;
		// Corners
		cur_window->DrawList->AddLine(ImVec2(w_pos.x + 40, w_pos.y + 70), ImVec2(w_pos.x + 40 + space / 1.5, w_pos.y + 70), Config::BoxColor, 1.f); // Top Left | Direction: Right
		cur_window->DrawList->AddLine(ImVec2(w_pos.x + 40, w_pos.y + 70), ImVec2(w_pos.x + 40, w_pos.y + 70 + space), Config::BoxColor, 1.f); // Top Left | Direction: Down
		cur_window->DrawList->AddLine(ImVec2(w_pos.x + 200, w_pos.y + 370), ImVec2(w_pos.x + 200 - space / 1.5, w_pos.y + 370), Config::BoxColor, 1.f); // Top Right | Direction: Left
		cur_window->DrawList->AddLine(ImVec2(w_pos.x + 200, w_pos.y + 370), ImVec2(w_pos.x + 200, w_pos.y + 370 - space), Config::BoxColor, 1.f); // Top Right | Direction: Down
		cur_window->DrawList->AddLine(ImVec2(w_pos.x + 40, w_pos.y + 370), ImVec2(w_pos.x + 40 + space / 1.5, w_pos.y + 370), Config::BoxColor, 1.f); // Bottom Left | Direction: Right
		cur_window->DrawList->AddLine(ImVec2(w_pos.x + 40, w_pos.y + 370), ImVec2(w_pos.x + 40, w_pos.y + 370 - space), Config::BoxColor, 1.f); // Bottom Left | Direction: Up
		cur_window->DrawList->AddLine(ImVec2(w_pos.x + 200, w_pos.y + 70), ImVec2(w_pos.x + 200 - space / 1.5, w_pos.y + 70), Config::BoxColor, 1.f); // Bottom Right | Direction: Left
		cur_window->DrawList->AddLine(ImVec2(w_pos.x + 200, w_pos.y + 70), ImVec2(w_pos.x + 200, w_pos.y + 70 + space), Config::BoxColor, 1.f); // Bottom Right | Direction: Up
	}




	float healthPercentage = 0.0f;
	static float currentTime = 0.0f;
	static float animspeed = 8.0f;
	static float currentHeight = 0.0f;

	if (Config::ShowHealthBar) {
		ImU32 MC;
		ImVec2 start, end, startO, endO;
		ImColor Color;
		float targetHeight;
		healthPercentage = 50.0f + 50.0f * sinf(2 * M_PI * currentTime / animspeed);
		MC = IM_COL32(255 * healthPercentage / 100, 255 * (100 - healthPercentage) / 100, 0, 255);
		Color = ColorMix(MC, Config::HealthbarMax, healthPercentage / 100.0f);

		targetHeight = 300 * (healthPercentage / 100.0f);
		start = { w_pos.x + 34, w_pos.y + 70 + currentHeight };
		end = { w_pos.x + 36, w_pos.y + 370 };
		startO = { w_pos.x + 33, w_pos.y + 70 };
		endO = { w_pos.x + 37, w_pos.y + 370 };

		// healthbar drawing
		cur_window->DrawList->AddRectFilled(startO, endO, ImColor(20, 20, 20, 255));
		cur_window->DrawList->AddRectFilled(start, end, Color);
		// healthbar drawing end

		currentHeight = (1.0f - 0.05f) * currentHeight + 0.05f * targetHeight;
		currentTime += ImGui::GetIO().DeltaTime;
		if (currentTime > animspeed) {
			currentTime = 0.0f;
		}
		if (Config::HealthText) {
			ImVec2 positions = { w_pos.x + 24, w_pos.y + 63 + currentHeight }; 

			char healthText[4];
			healthPercentage = 50.0f - 51.0f * sinf(2 * M_PI * currentTime / animspeed);
			int truncatedPercentage = static_cast<int>(healthPercentage);
			if (truncatedPercentage < 100) {
				snprintf(healthText, sizeof(healthText), "%3d", truncatedPercentage);
				ImVec2 Strokepositions[] = { {positions.x - 1, positions.y + 1}, {positions.x - 1, positions.y - 1}, {positions.x + 1, positions.y + 1}, {positions.x + 1, positions.y - 1} };
				for (const auto& pos : Strokepositions) {
					cur_window->DrawList->AddText(pos, ImColor(0, 0, 0), healthText);
				}
				cur_window->DrawList->AddText(positions, ImColor(255, 255, 255), healthText);
			}
		}
	}

	const std::array<std::string, 7> renderNames = { "ak47", "Playername",  "W", };

	for (std::size_t i = 0; i < renderNames.size(); ++i) {
		ImU32 textColor = ImGui::GetColorU32(ImVec4(255 / 255.f, 255 / 255.f, 255 / 255.f, 255 / 255.f));

		if ((i == 0 && Config::ShowWeaponESP && Config::WeaponStyle == 1) ||
			(i == 1 && Config::ShowPlayerName) ||
			(i == 2 && Config::ShowWeaponESP && Config::WeaponStyle == 0)) {

			const auto text_size = ImGui::CalcTextSize(renderNames[i].c_str());

			auto pos = ImVec2(w_pos.x + 205, w_pos.y + 70);
			if (i == 0) {
				pos = ImVec2(w_pos.x + (240 / 2) - text_size.x / 2, pos.y + ((Config::HealthBarType == 2) ? 317 : 315) - text_size.y);
				textColor = Config::Weaponcolor;
			}
			else if (i == 1) {
				pos = ImVec2(w_pos.x + (240 / 2) - text_size.x / 2, pos.y - ((Config::HealthBarType == 1) ? 6 : 5) - text_size.y);
				textColor = Config::Namecolor;
			}

			else if (i == 2) {
				pos = ImVec2(w_pos.x + (190 / 2) - text_size.x / 2, pos.y + (Config::HealthBarType == 2 ? 317 : 315) - text_size.y);
				textColor = Config::Weaponcolor;
				ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);
			}

			cur_window->DrawList->AddText(pos, textColor, renderNames[i].c_str());

			if (i == 2) ImGui::PopFont();
		}
	}

	const std::array<std::string, 10> Flags = { "$1200\n", "Lethal\n", "Flashed\n", "Hk\n", "Defuser", "Scoped\n", "Defusing\n", "20m\n","999ms","Visible"};

	std::size_t FC = 0; // fc = flag count 

	for (std::size_t i = 0; i < Flags.size(); ++i) {
		ImU32 textColor = ImGui::GetColorU32(ImVec4(255 / 255.f, 255 / 255.f, 255 / 255.f, 255 / 255.f));

		if ((i == 0 && Config::selectedFlags & (1 << 0)) ||
			(i == 1 && Config::selectedFlags & (1 << 1)) ||
			(i == 2 && Config::selectedFlags & (1 << 2)) ||
			(i == 3 && Config::selectedFlags & (1 << 3)) ||
			(i == 4 && Config::selectedFlags & (1 << 4)) ||
			(i == 5 && Config::selectedFlags & (1 << 5)) ||
			(i == 6 && Config::selectedFlags & (1 << 6)) ||
			(i == 7 && Config::selectedFlags & (1 << 7)) ||
			(i == 8 && Config::selectedFlags & (1 << 8)) ||
			(i == 9 && Config::selectedFlags & (1 << 9))) {

			const auto text_size = ImGui::CalcTextSize(Flags[i].c_str());
			auto pos = ImVec2(w_pos.x + 205, w_pos.y + 70 + FC * text_size.y); // can make moveable flags now for this easily
			cur_window->DrawList->AddText(pos, textColor, Flags[i].c_str());
			++FC;
		}
	}
	FC = 0;
}




std::vector<std::pair<ImVec2, ImVec2>> hitboxes;
std::vector<bool> hitboxSelected;


void Image(ImVec2 CursorPos, void* image, ImVec2 imagesize, ImColor color) {
	ImGui::SetCursorPos(CursorPos);
	ImGui::Image((void*)image, ImVec2(imagesize.x, imagesize.y), ImVec2(0, 0), ImVec2(1, 1), color);
}

void Hitbox_Preview(ImColor Selected, ImColor Unselected) {
	const auto cur_window = ImGui::GetCurrentWindow();
	const ImVec2 w_pos = ImVec2(cur_window->Pos.x + cur_window->Size.x * 0.17f, cur_window->Pos.y + cur_window->Size.y * 0.01f);
	ImVec2 p = ImGui::GetCursorScreenPos();

	if (EspPreview == NULL) {
		Gui.LoadTextureFromMemory(Images::head_binary, sizeof Images::head_binary, &Head, &HeadW, &HeadH);
		Gui.LoadTextureFromMemory(Images::body_binary, sizeof Images::body_binary, &Body, &BodyW, &BodyH);
		Gui.LoadTextureFromMemory(Images::legs_binary, sizeof Images::legs_binary, &Legs, &LegsW, &LegsH);
		Gui.LoadTextureFromMemory(Images::right_arm_binary, sizeof Images::right_arm_binary, &r_arm, &r_armW, &r_armH);
		Gui.LoadTextureFromMemory(Images::left_arm_binary, sizeof Images::left_arm_binary, &l_arm, &l_armW, &l_armH);
	}
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(p.x - 7, p.y + 15), ImVec2(p.x + ImGui::GetWindowWidth() - 9, p.y - 24), ImColor(30, 30, 30));
	ImGui::GetForegroundDrawList()->AddRectFilledMultiColor(ImVec2(p.x - 7, p.y + 15), ImVec2(p.x + ImGui::GetWindowWidth() - 9, p.y + 16), ImColor(167, 24, 71, 255), Config::Accent, Config::Accent, ImColor(167, 24, 71, 255));
	ImGui::GetForegroundDrawList()->AddText({ p.x + ImGui::GetContentRegionAvail().x * 0.45f, p.y - 12 }, IM_COL32_WHITE, "Hitbox");

	ImVec2 Bodypos(137, 96); // (137, 96) just position of the images
	ImVec2 size(20, 20); // dont change please (20, 20)

	std::vector<std::pair<ImVec2, ImVec2>> hitboxes = {
		{ImVec2(w_pos.x + Bodypos.x - 47, w_pos.y + Bodypos.y - 43), ImVec2(w_pos.x + Bodypos.x - 38 + HeadW, w_pos.y + Bodypos.y - 40 + HeadH)}, // head
		{ImVec2(w_pos.x + Bodypos.x - 53, w_pos.y + Bodypos.y), ImVec2(w_pos.x + Bodypos.x - 58 + BodyW, w_pos.y + Bodypos.y - 2 + BodyH)}, // body
		{ImVec2(w_pos.x + Bodypos.x - 63, w_pos.y + Bodypos.y + 71), ImVec2(w_pos.x + Bodypos.x - 63 + LegsW, w_pos.y + Bodypos.y + 68 + LegsH)}, // legs
		{ImVec2(w_pos.x + Bodypos.x + 3, w_pos.y + Bodypos.y), ImVec2(w_pos.x + Bodypos.x + 5 + r_armW, w_pos.y + Bodypos.y + 8 + r_armH)}, // right arm
		{ImVec2(w_pos.x + Bodypos.x - 91, w_pos.y + Bodypos.y), ImVec2(w_pos.x + Bodypos.x - 91 + l_armW, w_pos.y + Bodypos.y + 5 + l_armH)} // left arm
	};

	for (size_t i = 0; i < hitboxes.size(); ++i) {
		ImVec2 hitboxMin = ImVec2(ImMin(hitboxes[i].first.x, hitboxes[i].second.x), ImMin(hitboxes[i].first.y, hitboxes[i].second.y));
		ImVec2 hitboxMax = ImVec2(ImMax(hitboxes[i].first.x, hitboxes[i].second.x), ImMax(hitboxes[i].first.y, hitboxes[i].second.y));

		if (ImGui::IsMouseHoveringRect(hitboxMin, hitboxMax) && ImGui::IsMouseClicked(0)) {
			switch (i) {
			case 0: Config::AimPositionIndex = BONEINDEX::head; break;
			case 1: Config::AimPositionIndex = BONEINDEX::spine_1; break;
			case 2: Config::AimPositionIndex = BONEINDEX::pelvis; break;
			case 3: Config::AimPositionIndex = BONEINDEX::arm_upper_L; break;
			case 4: Config::AimPositionIndex = BONEINDEX::arm_upper_R; break;
			}
		}
	}

	Image(ImVec2(Bodypos.x, Bodypos.y), Body, ImVec2(BodyW, BodyH), (Config::AimPositionIndex == BONEINDEX::spine_1) ? Selected : Unselected); // body || BONEINDEX::spine_2
	Image(ImVec2(Bodypos.x + 13, Bodypos.y - 37), Head, ImVec2(HeadW, HeadH), (Config::AimPositionIndex == BONEINDEX::head) ? Selected : Unselected); // head || BONEINDEX::head
	Image(ImVec2(Bodypos.x - 9, Bodypos.y + 69), Legs, ImVec2(LegsW, LegsH), (Config::AimPositionIndex == BONEINDEX::pelvis) ? Selected : Unselected); // legs || BONEINDEX::pelvis
	Image(ImVec2(Bodypos.x + 58, Bodypos.y + 9), r_arm, ImVec2(r_armW, r_armH), (Config::AimPositionIndex == BONEINDEX::arm_upper_L) ? Selected : Unselected); // right arm || BONEINDEX::arm_upper_R
	Image(ImVec2(Bodypos.x - 33, Bodypos.y + 9), l_arm, ImVec2(l_armW, l_armH), (Config::AimPositionIndex == BONEINDEX::arm_upper_R) ? Selected : Unselected); // left arm || BONEINDEX::arm_upper_L

	// for color examples later down the line for multi targeting 
	ImGui::GetForegroundDrawList()->AddRectFilledMultiColor(ImVec2(p.x - 7, p.y + 305), ImVec2(p.x + ImGui::GetWindowWidth() - 9, p.y + 306), ImColor(167, 24, 71, 255), Config::Accent, Config::Accent, ImColor(167, 24, 71, 255));
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(p.x - 7, p.y + 357), ImVec2(p.x + ImGui::GetWindowWidth() - 9, p.y + 306), ImColor(30, 30, 30));

	// image trigger locations 

	/*
	for (size_t i = 0; i < hitboxes.size(); ++i) {
		cur_window->DrawList->AddRect(hitboxes[i].first, hitboxes[i].second, IM_COL32(0, 0, 0, 160));
	}
	*/
}




void Ui() {
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_CheckMark] = ImVec4(Config::Accent.Value.x, Config::Accent.Value.y, Config::Accent.Value.z, Config::Accent.Value.w);
	colors[ImGuiCol_Header] = { Config::Accent.Value.x, Config::Accent.Value.y,Config::Accent.Value.z, 0.1f };

	ImGui::SetNextWindowSize(ImVec2(700, 530));
	ImGui::Begin("Window", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar); {

		struct ButtonInfo {
			const char* icon;
			const char* tooltip;
			int tab;
		};

		const ButtonInfo buttons[] = {
			{ ICON_FA_USER_CIRCLE, "Aimbot ( W.I.P )", 0},
			{ ICON_FA_EYE, "Esp | see other players through walls", 1},
			{ ICON_FA_SUN, "Misc", 2},
			{ ICON_FA_FOLDER_OPEN, "Config system", 3}
		};

		float buttonWidth = ImGui::GetContentRegionAvail().x / std::size(buttons) - 6.f;

		for (const auto& button : buttons) {
			if (ImGui::Button(button.icon, ImVec2(buttonWidth, 35))) {
				tabb = button.tab;
			}
			if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
				ImGui::SetTooltip(button.tooltip);
			}
			ImGui::SameLine();

			ImDrawList* drawList = ImGui::GetWindowDrawList();
			ImVec2 buttonPos = ImGui::GetItemRectMin();
			ImVec2 buttonSize = ImGui::GetItemRectSize();
			drawList->AddLine({ buttonPos.x, buttonPos.y + buttonSize.y },{ buttonPos.x + buttonSize.x, buttonPos.y + buttonSize.y },IM_COL32(255, 255, 255, 255)); 

			if (tabb == button.tab) {
				drawList->AddLine({ buttonPos.x, buttonPos.y + buttonSize.y }, { buttonPos.x + buttonSize.x, buttonPos.y + buttonSize.y }, Config::Accent);
			}
		}
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImGui::Dummy(ImVec2(3.f, ImGui::GetContentRegionAvail().x));
		switch (tabb) {
		case 0:
			ImGui::Spacing();

			if (ImGui::BeginChild(2, ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu, true)) {

				const char* tabNames[] = { "Aimbot", "Triggerbot" };
				for (int i = 0; i < 2; ++i) {
					if (ImGui::Button(tabNames[i], ImVec2(ImGui::GetContentRegionAvail().x / (i == 0 ? 2.02f : 1), 30)))
						currentTab = i;
					if (i < 1)
						ImGui::SameLine();
					if (i == currentTab) {
						ImVec2 buttonPos = ImGui::GetItemRectMin(), buttonSize = ImGui::GetItemRectSize();
						ImGui::GetWindowDrawList()->AddLine({ buttonPos.x, buttonPos.y + buttonSize.y }, { buttonPos.x + buttonSize.x, buttonPos.y + buttonSize.y }, Config::Accent);
					}
				}

				ImGui::Spacing();
				switch (currentTab) {
				case 0:
					// shit is goofy ik but it works
					for (int i = 0; i < 6; ++i) {
						if (i > 0) ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);

						if (ImGui::Button(labels[i], ImVec2(ImGui::GetContentRegionAvail().x / widths[i], 30))) WeaponTab = i;

						if (i > 0) ImGui::PopFont();

						if (i < 5) ImGui::SameLine();

						if (i == WeaponTab) {
							ImVec2 buttonPos = ImGui::GetItemRectMin(), buttonSize = ImGui::GetItemRectSize();
							ImGui::GetWindowDrawList()->AddLine({ buttonPos.x, buttonPos.y + buttonSize.y }, { buttonPos.x + buttonSize.x, buttonPos.y + buttonSize.y }, Config::Accent);
						}
					}

					ImGui::BeginChild("LeftChild", ImVec2(ImGui::GetContentRegionAvail().x / 2.02f, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu);
					ImGui::Checkbox("AimBot", &Config::AimBot);
					ImGui::SameLine();
					HotKey(&Config::AimBotHotKey);
					ImGui::Checkbox("Drawfov", &Config::ShowAimFovRange);
					ImGui::SameLine();
					ImGui::ColorEdit4("##FovCircleColor", reinterpret_cast<float*>(&Config::AimFovRangeColor), ImGuiColorEditFlags_NoInputs);
					ImGui::Checkbox("Follow Recoil", &Config::RecoilFov);
					ImGui::Checkbox("Flashed", &AimControl::IgnoreFlash);
					ImGui::Checkbox("Scoped", &AimControl::ScopeOnly);
					ImGui::Checkbox("Teamcheck", &Config::AimTeam);
					ImGui::Checkbox("Visible", &Config::VisibleCheck);


					// multipoint / weapon hitboxes coming
					// this is for xwqo cause he aint like the main style
					/*
					ImGui::SetNextItemWidth(130.f);
					if (ImGui::Combo("Hitbox", &Config::AimPosition, "Head\0Neck\0Chest\0Stomach\0Pelivs\0")) {
						Config::AimPositionIndex = (Config::AimPosition == 0) ? BONEINDEX::head :
							(Config::AimPosition == 1) ? BONEINDEX::neck_0 :
							(Config::AimPosition == 2) ? BONEINDEX::spine_1 :
							(Config::AimPosition == 3) ? BONEINDEX::spine_2 :
							(Config::AimPosition == 4) ? BONEINDEX::pelvis : BONEINDEX::head;
					}
					*/
				
					ImGui::Separator();
					// IDC ЭТО РАБОТАЕТ НЕГР
					switch (WeaponTab) {
					case 0:
						Gui.Slider("AimFov", ImGuiDataType_Float, &Config::aimfov, 0.f, 60.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Smooth", ImGuiDataType_Float, &Config::aimsmooth, 0.f, 100.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);

						ImGui::SeparatorText("Account Recoil");
						ImGui::Checkbox("RCS", &Config::Grcs);
						Gui.Slider("Yaw", ImGuiDataType_Float, &Config::GrcsV[0], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Pitch", ImGuiDataType_Float, &Config::GrcsV[1], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);

						break;
					case 1:
						Gui.Slider("AimFov", ImGuiDataType_Float, &Config::Raimfov, 0.f, 60.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Smooth", ImGuiDataType_Float, &Config::Raimsmooth, 0.f, 100.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);

						ImGui::SeparatorText("Account Recoil");
						ImGui::Checkbox("RCS", &Config::Rrcs);
						Gui.Slider("Yaw", ImGuiDataType_Float, &Config::RrcsV[0], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Pitch", ImGuiDataType_Float, &Config::RrcsV[1], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);

						break;
					case 2:
						Gui.Slider("AimFov", ImGuiDataType_Float, &Config::Paimfov, 0.f, 60.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Smooth", ImGuiDataType_Float, &Config::Paimsmooth, 0.f, 100.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);

						ImGui::SeparatorText("Account Recoil");
						ImGui::Checkbox("RCS", &Config::Prcs);
						Gui.Slider("Yaw", ImGuiDataType_Float, &Config::PrcsV[0], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Pitch", ImGuiDataType_Float, &Config::PrcsV[1], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);

						break;
					case 3:
						Gui.Slider("AimFov", ImGuiDataType_Float, &Config::Hpaimfov, 0.f, 60.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Smooth", ImGuiDataType_Float, &Config::Hpaimsmooth, 0.f, 100.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);

						ImGui::SeparatorText("Account Recoil");
						ImGui::Checkbox("RCS", &Config::HPrcs);
						Gui.Slider("Yaw", ImGuiDataType_Float, &Config::HPrcsV[0], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Pitch", ImGuiDataType_Float, &Config::HPrcsV[1], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);

						break;
					case 4: 
						Gui.Slider("AimFov", ImGuiDataType_Float, &Config::Saimfov, 0.f, 60.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Smooth", ImGuiDataType_Float, &Config::Saimsmooth, 0.f, 100.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);

						ImGui::SeparatorText("Account Recoil");
						ImGui::Checkbox("RCS", &Config::Srcs);
						Gui.Slider("Yaw", ImGuiDataType_Float, &Config::SrcsV[0], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Pitch", ImGuiDataType_Float, &Config::SrcsV[1], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);

						break;
					case 5:
						Gui.Slider("AimFov", ImGuiDataType_Float, &Config::SMGaimfov, 0.f, 60.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Smooth", ImGuiDataType_Float, &Config::SMGAimpos, 0.f, 100.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);

						ImGui::SeparatorText("Account Recoil");
						ImGui::Checkbox("RCS", &Config::SMGrcs);
						Gui.Slider("Yaw", ImGuiDataType_Float, &Config::SMGrcsV[0], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);
						Gui.Slider("Pitch", ImGuiDataType_Float, &Config::SMGrcsV[1], 0.f, 2.f, "%.2f", Config::Accent, ImGuiSliderFlags_None);

						break;
					}

					ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild("##RightChild", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu);

					ImGui::Dummy(ImVec2(ImGui::GetContentRegionAvail().x, 13.f));

					Hitbox_Preview(ImColor(0, 255, 0, 255), ImColor(255, 0, 0, 255)); // doesnt do per weapon
					ImGui::EndChild();
					break;
				case 1:
					ImGui::BeginChild("LeftChild", ImVec2(ImGui::GetContentRegionAvail().x / 2.02f, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu);
					ImGui::Checkbox("TriggerBot", &Config::TriggerBot);
					ImGui::SameLine();
					HotKey(&Config::TriggerHotKey);
					ImGui::Checkbox("Teamcheck", &Config::TriggerbotTeamcheck);
					ImGui::Checkbox("Scoped", &Config::ScopeOnlyT);
					ImGui::Checkbox("Flashed", &Config::IgnoreFlashT);


					ImGui::EndChild();	
					ImGui::SameLine();
					ImGui::BeginChild("##RightChild", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu);

					ImGui::EndChild();
					break;
				}
				ImGui::EndChild();
			}
		
			break;
		case 1:
			ImGui::Spacing();

			if (ImGui::BeginChild(2, ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu, true)) {

				const char* vistabNames[] = { "Visuals", "Misc" };
				for (int i = 0; i < 2; ++i) {
					if (ImGui::Button(vistabNames[i], ImVec2(ImGui::GetContentRegionAvail().x / (i == 0 ? 2.02f : 1), 30)))
						vistab = i;
					if (i < 1)
						ImGui::SameLine();
					if (i == vistab) {
						ImVec2 buttonPos = ImGui::GetItemRectMin(), buttonSize = ImGui::GetItemRectSize();
						ImGui::GetWindowDrawList()->AddLine({ buttonPos.x, buttonPos.y + buttonSize.y }, { buttonPos.x + buttonSize.x, buttonPos.y + buttonSize.y }, Config::Accent);
					}
				}
				ImGui::Spacing();
				ImGui::BeginChild("LeftChild", ImVec2(ImGui::GetContentRegionAvail().x / 2.02f, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu);
	
				switch (vistab) {
				case 0:
					ImGui::SeparatorText("Visuals");

					ImGui::Checkbox("Box", &Config::ShowBoxESP);
					ImGui::SameLine();
					ImGui::ColorEdit4("##boxviscolor", reinterpret_cast<float*>(&Config::VisibleColor), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					ImGui::SameLine();
					ImGui::ColorEdit4("##BoxColor", reinterpret_cast<float*>(&Config::BoxColor), ImGuiColorEditFlags_NoInputs);


					ImGui::Checkbox("Filled", &Config::FilledBox);
					ImGui::SameLine();
					ImGui::ColorEdit4("##Filledviscolor", reinterpret_cast<float*>(&Config::BoxFilledVisColor), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					ImGui::SameLine();
					ImGui::ColorEdit4("##FilledBoxColor", reinterpret_cast<float*>(&Config::BoxFilledColor), ImGuiColorEditFlags_NoInputs);

	
					ImGui::Checkbox("Health", &Config::ShowHealthBar);
					ImGui::SameLine();
					ImGui::ColorEdit4("##Healthcol", reinterpret_cast<float*>(&Config::HealthbarMax), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Ammo", &Config::ShowAmmoBar);
					ImGui::SameLine();
					ImGui::ColorEdit4("##Ammocol", reinterpret_cast<float*>(&Config::AmmoColor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Armour", &Config::ShowArmourBar);
					ImGui::SameLine();
					ImGui::ColorEdit4("##Armoucol", reinterpret_cast<float*>(&Config::ArmourColor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Headcircle", &Config::HeadCircle);
					ImGui::SameLine();
					ImGui::ColorEdit4("##HeadCol", reinterpret_cast<float*>(&Config::HeadColor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Skeleton", &Config::Skeleton);
					//	ImGui::SameLine();
					//	ImGui::ColorEdit4("##SkeletonViscolor", reinterpret_cast<float*>(&Config::BoneVisColor), ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					ImGui::SameLine();
					ImGui::ColorEdit4("##BoneColor", reinterpret_cast<float*>(&Config::BoneColor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Name", &Config::ShowPlayerName);
					ImGui::SameLine();
					ImGui::ColorEdit4("##Namecolor", reinterpret_cast<float*>(&Config::Namecolor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Weapon", &Config::ShowWeaponESP);
					ImGui::SameLine();
					ImGui::ColorEdit4("##Weaponcolor", reinterpret_cast<float*>(&Config::Weaponcolor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Snapline", &Config::Snapline);
					ImGui::SameLine();
					ImGui::ColorEdit4("##SnaplineCol", reinterpret_cast<float*>(&Config::SnaplineCol), ImGuiColorEditFlags_NoInputs);

					// all broken functions dont enable 
					//ImGui::Checkbox("OOF-arrow", &Config::OOFarrow);

					//ImGui::Checkbox("Local Sound", &Config::LocalSoundEsp);
					//ImGui::Checkbox("Enemy Sound", &Config::EnemySoundEsp);

					ImGui::Checkbox("Team Check", &Config::TeamCheck);
					if (!Config::TeamCheck)  ImGui::Checkbox("Local Check", &Config::LocalCheck);
					ImGui::Checkbox("Visible", &Config::VisCheck);

					// ima change this leave it for now
					ImGui::PushItemWidth(120.f);
					ImGui::Combo("BoxStyle", &Config::BoxType, "Normal\0Corner");
					ImGui::Combo("FilledStyle", &Config::BoxFillType, "Filled\0Gradient\0");
					ImGui::Combo("WeaponStyle", &Config::WeaponStyle, "Icon\0Text");

					//ImGui::Combo("Image", &Config::ImgType, "None\0Hitler\0Putin\0Zelensky"); // goofy feature
					ImGui::PopItemWidth();
	
					ImGui::MultiCombo("Flags", &Config::selectedFlags, items, 10);

					break;
				case 1:
					ImGui::SeparatorText("Misc");
					ImGui::Checkbox("Crosshair", &Config::ShowCrossHair);
					if (ImGui::IsItemClicked(1)) {
						ImGui::OpenPopup("##Settings");
					}
					if (ImGui::BeginPopup("##Settings")) {
						ImGui::TextUnformatted("Settings");
						ImGui::Checkbox("Center Dot", &CrosshairConfig::drawDot);
						ImGui::SliderInt("Horizontal Length", &CrosshairConfig::HorizontalLength, 0, 75, "%d");
						ImGui::SliderInt("Vertical Length", &CrosshairConfig::VerticalLength, 0, 75, "%d");
						ImGui::SliderInt("Thickness", &CrosshairConfig::Thickness, 1, 20, "%d");
						ImGui::SliderInt("Gap", &CrosshairConfig::Gap, 0, 35, "%d");
						ImGui::Checkbox("Outline", &CrosshairConfig::drawOutLine);
						ImGui::Checkbox("T Style", &CrosshairConfig::tStyle);
						ImGui::Checkbox("Sniper Only", &CrosshairConfig::SniperOnly);
						ImGui::Checkbox("Follow Recoil", &CrosshairConfig::RecoilCrosshair);
						ImGui::EndPopup();
					}
					ToolTip("RightClick for more Options");

					ImGui::SameLine();
					ImGui::ColorEdit4("##CrossHairColor", reinterpret_cast<float*>(&CrosshairConfig::CrossHairColor), ImGuiColorEditFlags_NoInputs);

					ImGui::Checkbox("Spread Circle", &Config::SpreadCircle);
					ImGui::SameLine();
					ImGui::ColorEdit4("##SpreadColor", reinterpret_cast<float*>(&Config::SpreadCircleColor), ImGuiColorEditFlags_NoInputs);


					ImGui::SeparatorText("Movement");


					ImGui::SeparatorText("Indicators");
					ImGui::Checkbox("Velocity", &Config::VelocityIndicator);
					if (Config::VelocityIndicator)
					ImGui::Checkbox("Max Velocity", &Config::MaxVelocity);
					
					ImGui::Checkbox("Velocity Graph", &Config::VelocityGraph);
					if (Config::VelocityGraph) {
						ImGui::SameLine();
						ImGui::ColorEdit4("##graphColor", reinterpret_cast<float*>(&Config::GraphLineColor), ImGuiColorEditFlags_NoInputs);
					}
					ImGui::Checkbox("Slowed", &Config::SlowedIndicator);
					ToolTip("Shows when your Movement Speed is Reduced");
					ImGui::Checkbox("Keystrokes", &Config::KeyStrokes);
					if (Config::KeystrokeColor && Config::KeystrokeStyle == 0) {
						ImGui::SameLine();
						ImGui::ColorEdit4("##KeyColor", reinterpret_cast<float*>(&Config::KeystrokeColor), ImGuiColorEditFlags_NoInputs);
					}
					ImGui::Combo("Key Style", &Config::KeystrokeStyle, "Color\0Key(-)");
					break;
				}


				ImGui::EndChild();
				ImGui::SameLine();
				ImGui::BeginChild("##RightChild", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu);
				switch (vistab) {
				case 0:
					ImGui::Text("Dummy space");
					visuals_preview();

					//smth im working on 
					/*
					ImGui::Dummy(ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y / 1.3));
					if (ImGui::Button("Visible", ImVec2(ImGui::GetContentRegionAvail().x / 2, 30)))
						printf("");
					ImGui::SameLine();
					if (ImGui::Button("Hidden", ImVec2(ImGui::GetContentRegionAvail().x, 30)))
						printf("");
					*/
					break;
				case 1:
					ImGui::SeparatorText("World");
					ImGui::Checkbox("Nightmode", &Config::Nightmode);
					ToolTip("This is not actual Nightmode");

					ImGui::SameLine();
					ImGui::SetNextItemWidth(140.f);
					Gui.Slider("##brightness", ImGuiDataType_Float, &Config::NightmodeBright, 0.f, 150.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);


					ImGui::Checkbox("ZeusRange", &Config::zeusRange);
					ImGui::SameLine();
					ImGui::ColorEdit4("##zeusRangeColor", reinterpret_cast<float*>(&Config::zeusRangeColor), ImGuiColorEditFlags_NoInputs);
					ImGui::Checkbox("ZeusTarget", &Config::zeusTarget);
					ImGui::SameLine();
					ImGui::ColorEdit4("##zeusTargetColor", reinterpret_cast<float*>(&Config::zeusTargetColor), ImGuiColorEditFlags_NoInputs);
					break;
				}
				ImGui::EndChild();

				ImGui::EndChild();
			    break;
			}
			break;
		case 2:
			ImGui::Spacing();
			ImGui::BeginChild("##LeftChild", ImVec2(ImGui::GetContentRegionAvail().x / 2.02f, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu);

			ImGui::SeparatorText("Misc");


			ImGui::Checkbox("Speclist", &Config::SpecList);
			ImGui::Checkbox("Hitsound", &Config::Hitsound);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(140.f);
			ImGui::Combo("##hitsounds", &Config::hitsound_type, "Neverlose\0Skeet\0Bell\0Bubble\0Cod\0");
			ImGui::Checkbox("Hitmarker", &Config::Hitmarker);
			if (ImGui::IsItemClicked(1)) {
				ImGui::OpenPopup("##Settings");
			}
			if (ImGui::BeginPopup("##Settings")){
				ImGui::TextUnformatted("Settings");
				Gui.Slider("Hitmarker Size", ImGuiDataType_Float, &Config::HitmarkSize, Config::HitmarkGap + 3, 30.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);
				Gui.Slider("Hitmarker Gap", ImGuiDataType_Float, &Config::HitmarkGap, 0.f, 20.f, "%.0f", Config::Accent, ImGuiSliderFlags_None);
				ImGui::EndPopup();
			}
			ToolTip("RightClick for more Options");

			ImGui::Checkbox("Damage Text", &Config::DamageText);
			ToolTip("Shows the Damage of a Hit");

			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("##RightChild", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu);
			ImGui::SeparatorText("Settings");
			ImGui::Checkbox("BypassOBS", &Config::OBSBypass);


			ImGui::EndChild();
			break;
		case 3:
			ImGui::Spacing();
			ImGui::BeginChild("##LeftChild", ImVec2(ImGui::GetContentRegionAvail().x / 2.02f, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu);
			ImGui::SeparatorText("Config");

			ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.4f), "Reworking Config System\nPreviously in disrepair");


			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::BeginChild("##RightChild", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), ImGuiWindowFlags_ChildMenu);
			ImGui::SeparatorText("Menu");
			ImGui::SetNextItemWidth(100.f);
			ImGui::Combo("##Menu Style", &Config::MenuStyle, "ModDark\0Nord");
			ImGui::SameLine();
			ImGui::ColorEdit4("Accent", reinterpret_cast<float*>(&Config::Accent), ImGuiColorEditFlags_NoInputs);
			ImGui::Checkbox("Watermark", &Config::WaterMark);

			if (ImGui::IsItemClicked(1)) {
				ImGui::OpenPopup("##Settings");
			}
			if (ImGui::BeginPopup("##Settings"))
			{
				ImGui::TextUnformatted("Settings");
				ImGui::MultiCombo("##Settings", &Config::Watermarkf, Wsettings, 5);
				ImGui::EndPopup();
			}
			ToolTip("RightClick for more Options");

			ImGui::Checkbox("Debuglist", &Config::Debuglist);
			ImGui::Checkbox("V-sync", &Config::vsync);

			if (ImGui::Button("Discord", ImVec2(ImGui::GetContentRegionAvail().x, 30)))
				(ShellExecuteA)(NULL, ("open"), ("https://discord.gg/KDd33stjue"), NULL, NULL, SW_SHOWNORMAL);

			ImGui::Separator();
			ImGui::Dummy(ImVec2(20, ImGui::GetContentRegionAvail().y / 1.17));
			ButtonColor(255, 50, 0);
			if (ImGui::Button("Exit", ImVec2(ImGui::GetContentRegionAvail().x, 30)))
				exit(-1);

			ImGui::EndChild();

			break;

		}
	}
}

void Cheats::Menu(){
	StyleChanger::UpdateStyle(Config::MenuStyle);
	Ui(); 	
}

static bool isGameWindowActive() {
	HWND hwnd_cs2 = FindWindow(NULL, TEXT("Counter-Strike 2"));

	if (hwnd_cs2 != NULL ) {
		HWND foreground_window = GetForegroundWindow();
		if (foreground_window == hwnd_cs2) {
			return true;
		}
	}
	return false;
}

struct sound_info_t {
	Vec3 player_origin;
	bool has_changed;
};

std::vector<sound_info_t> s_info;

uint64_t currentTimeMillis() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Cheats::Run() {

	if (!isGameWindowActive() && !Config::ShowMenu && !ImGui::GetIO().WantCaptureMouse && !ImGui::GetIO().WantCaptureKeyboard)
		return;

	static auto LastToggleTime = std::chrono::steady_clock::now();

	if (GetAsyncKeyState(VK_INSERT) && std::chrono::steady_clock::now() - LastToggleTime >= std::chrono::milliseconds(150)) {
		Config::ShowMenu = !Config::ShowMenu;
		LastToggleTime = std::chrono::steady_clock::now();
	}

	if (Config::ShowMenu) Menu();
	Watermark::Render();
	Misc::NightMode();

	if (!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix, 64)) return;

	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress) ||
		!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;

	CEntity LocalEntity;
	if (!LocalEntity.UpdateController(LocalControllerAddress) ||
		(!LocalEntity.UpdatePawn(LocalPawnAddress) && false))
		return;



	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  HeadPos{ 0,0,0 };
	Vec3  AimPos{ 0,0,0 };

	struct WeaponSettings {float aimFov;float smooth;float rcsScaleX;float rcsScaleY;bool rcs;};

	const char* weaponGroupNames[] = { "Knife", "Rifle", "Pistol", "Heavy Pistol", "Sniper", "SMG", "Shotgun", "Grenade", "Zeus","Unkown"};

	int weaponGroup = GetWeaponGroup(LocalEntity.Pawn.WeaponName);

	std::unordered_map<int, WeaponSettings> allSettings = {
		{0, {0, 0, 0, 0, false}},// Knife
		{1, {Config::Raimfov, Config::Raimsmooth, Config::RrcsV[0], Config::RrcsV[1], Config::Rrcs}}, // Rifle
		{3, {Config::Paimfov, Config::Paimsmooth, Config::PrcsV[0], Config::PrcsV[1], Config::Prcs}}, // Pistol
		{4, {Config::Hpaimfov, Config::Hpaimsmooth, Config::HPrcsV[0], Config::HPrcsV[1], Config::HPrcs}}, // Heavy Pistol
		{5, {Config::Saimfov, Config::Saimsmooth, Config::SrcsV[0], Config::SrcsV[1], Config::Srcs}}, // Sniper
		{6, {Config::SMGaimfov, Config::SMGaimsmooth, Config::SMGrcsV[0], Config::SMGrcsV[1], Config::SMGrcs}}, // SMG
		{7, {0,0,0,0, false}}
	};

	auto it_settings = allSettings.find(weaponGroup);
	if (it_settings != allSettings.end()) {
		AimControl::AimFov = it_settings->second.aimFov;
		AimControl::Smooth = it_settings->second.smooth;
		AimControl::RCSScale.x = it_settings->second.rcsScaleX;
		AimControl::RCSScale.y = it_settings->second.rcsScaleY;
		AimControl::Rcs = it_settings->second.rcs;
	}
	else {
		AimControl::AimFov = Config::aimfov;
		AimControl::Smooth = Config::aimsmooth;
		AimControl::RCSScale.x = Config::GrcsV[0];
		AimControl::RCSScale.y = Config::GrcsV[1];
		AimControl::Rcs = Config::Grcs;
	}


	for (int i = 0; i < 64; i++) {
		CEntity Entity;
		static int LocalPlayerControllerIndex = 1;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1ULL) * 0x78, EntityAddress) ||
			(Config::LocalCheck && EntityAddress == LocalEntity.Controller.Address) ||
			!Entity.UpdateController(EntityAddress) ||
			!Entity.UpdatePawn(Entity.Pawn.Address)){
			continue;
		}

		Render::SpectatorList(LocalEntity, Entity);
		//Render::SpectatorList(LocalEntity, Entity); // still dont work idk why

		if (!Entity.IsAlive())
			continue;
        // BRO THIS SHIT IS PISSING ME OFF I HAVE WORKED ON A BUNCH OF FUNCTIONS AND NONE OF THEM WORK
		/*
		if (Config::OOFarrow) {
			Vec2 Screen;
			gGame.View.WorldToScreen(Entity.Pawn.Pos, Screen);

			float arrowRadius = 150.0f, arrowSize = 20.f;
			Vec2 screenCenter = { Gui.Window.Size.x / 2, Gui.Window.Size.y / 2 };

			float rotation = math::degrees_to_radians(math::normalize_yaw(LocalEntity.Pawn.ViewAngle.y - math::calc_angle(LocalEntity.Pawn.Pos, Entity.Pawn.Pos).y + Oofpos));

			Vector2D center = Vector2D(Gui.Window.Size.x / 2, Gui.Window.Size.y / 2);
			Vector2D position =
			{
				center.x + arrowRadius * std::cos(rotation),
				center.y + arrowRadius * std::sin(rotation)
			};

			std::array<Vector2D, 3> points =
			{
				Vector2D(position.x - arrowSize, position.y - arrowSize),
				Vector2D(position.x + arrowSize, position.y),
				Vector2D(position.x - arrowSize, position.y + arrowSize)
			};

			math::rotate_triangle(points, rotation); 


			ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(points[0].x, points[0].y),ImVec2(points[1].x, points[1].y),ImVec2(points[2].x, points[2].y),Config::OOFarrowColor);

			ImGui::GetBackgroundDrawList()->AddTriangle(ImVec2(points[0].x, points[0].y),ImVec2(points[1].x, points[1].y),ImVec2(points[2].x, points[2].y),Config::OOFarrowColor)
			);
		}
		*/
		if (!Entity.IsInScreen())
			continue;

		DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });

		if (DistanceToSight < MaxAimDistance) {
			MaxAimDistance = DistanceToSight;
			if ((!Config::AimTeam || Entity.Controller.TeamID != LocalEntity.Controller.TeamID) &&
				(!Config::VisibleCheck || Entity.Pawn.bSpottedByMask & (DWORD64(1) << (LocalPlayerControllerIndex)) || LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << (i)))) {
				AimPos = Entity.GetBone().BonePosList[Config::AimPositionIndex].Pos;
				if (Config::AimPositionIndex == BONEINDEX::head)
					AimPos.z -= 1.f;
			} 
		}

		if (Config::TeamCheck && Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;

		// sound esp no worky
		// https://yougame.biz/threads/310172/ -- dutu shitcode
		    if (Config::LocalSoundEsp) {
		       float sound;

			   ProcessMgr.ReadMemory(LocalEntity.Pawn.Address + Offset::Pawn.m_flEmitSoundTime, sound);

			   static float soundS = sound;

			   if (soundS != sound) {
			       Render::Circle3D(LocalEntity.Pawn.Pos, 20, false, ImColor(255, 255, 255, 255), 2.f);
			       soundS = sound;
			   }
		    }
		
			// animation brokey
			if (Config::EnemySoundEsp) {
				float smth3;

				ProcessMgr.ReadMemory(Entity.Pawn.Address + Offset::Pawn.m_flEmitSoundTime, smth3);

				static float main[64]{ smth3 };

				if (main[i] != smth3) {
					s_info.push_back(sound_info_t{ Entity.Pawn.Pos, true });

					main[i] = smth3;
				}

				for (int i = 0; i < s_info.size(); i++) {
					auto animation = animation_controller.get("soundinfo" + std::to_string(i) + animation_controller.current_child);
					animation.adjust(animation.value + 3.f * animation_controller.get_min_deltatime(0.3f) * (s_info[i].has_changed ? 1.f : -1.f));

					if (animation.value >= 0.99f)
						s_info[i].has_changed = false;

					Render::Circle3D(s_info[i].player_origin, 30 * animation.value, false, ImColor(255, 255, 255, 255), 2.f);
					if (i >= 60) {
						s_info.erase(s_info.begin(), s_info.begin() + 51);
					}
				}
			}

			// actual sound esp dont use it , it will freeze esp drawing
			/*
			ImGuiIO& io = ImGui::GetIO();
			ImVec2 mousePos = io.MousePos;
			float distanceToMouse = std::sqrt(std::pow(mousePos.x - Entity.Pawn.ScreenPos.x, 2) + std::pow(mousePos.y - Entity.Pawn.ScreenPos.y, 2));

			if (distanceToMouse < 80) {
				Beep(750, 300);
			}
			*/


		//zeus range shit
	    Render::TaserRange(LocalEntity, Entity);




		int distance = static_cast<int>(Entity.Pawn.Pos.DistanceTo(LocalEntity.Pawn.Pos) / 100);
		ImVec4 Rect = Esp::Get2DBox(Entity);


		if (Config::RenderDistance == 0 || (distance <= Config::RenderDistance && Config::RenderDistance > 0)) {

			Esp::LineToEnemy(Rect, Config::SnaplineCol, 1.2);
			Esp::DrawBone(Entity, 1);
			Esp::DrawHeadCircle(Entity, Config::HeadColor);
			Esp::Render(Rect, Entity, LocalEntity, LocalPlayerControllerIndex, i);
			Esp::EyeRay(Entity, 50, Config::EyeRayColor, 1);

		}

		if (Config::ShowHealthBar) {

			// dogshit code gonna be gone soon 
			// need to make it so i can change positions based on a list module so i can have multiple bars on the same level while pushing the icons / text
			/*
			ImVec2 HealthBarPos, HealthBarSize;
			switch (Config::HealthBarType) {
			case 0: HealthBarPos = { Rect.x - 6.f, Rect.y - 1.192f }; HealthBarSize = { 4, Rect.w + 2.5f }; break; // left box
			case 1: HealthBarPos = { Rect.x, Rect.y - 4.f }; HealthBarSize = { Rect.z, 4.f }; break; // top box
			case 2: HealthBarPos = { Rect.x, Rect.y + Rect.w + 2.f }; HealthBarSize = { Rect.z, 4.f }; break; // bottom box
			case 3: HealthBarPos = { Rect.x + Rect.z + 2.f, Rect.y - 1.192f }; HealthBarSize = { 4, Rect.w + 2.5f }; // right box
			break;
			}
			*/

			Esp::DrawHealthBar(EntityAddress, 100, Entity.Pawn.Health, { Rect.x - 6.f, Rect.y - 1.192f }, { 4, Rect.w + 2.5f }, Config::HealthBarType, Config::HealthbarMax);

		}
		if (Config::ShowArmourBar) {
			Esp::DrawArmorBar(EntityAddress, 100, Entity.Pawn.Armor, { Rect.x + Rect.z + 2.f, Rect.y - 1.192f }, { 4, Rect.w + 2.5f }, Config::ArmourColor);
		}

		if (Config::ShowAmmoBar) {
			Esp::DrawAmmoBar(EntityAddress, Entity.Pawn.MaxAmmo, Entity.Pawn.Ammo, { Rect.x, Rect.y + Rect.w + 2.f }, { Rect.z, 4.f }, Config::AmmoColor);
		}

	}



	Misc::HitSound(LocalEntity);
	//Misc::NadeManager(gGame); please dont use this the functions is fucked


	if (Config::Debuglist)
		Render::Debug_List(LocalEntity);


	Render::MovementIndicators(LocalEntity);
    Render::SlowedIndicator(LocalEntity); // not finishedfo
	Render::Keystrokes();
	//Render::Keybind_List(); // dont use shitcode 
	//bmb::RenderBombIcon(); // broken || FIX THIS ICE CREAM


	if (Config::ShowCrossHair && (!CrosshairConfig::SniperOnly || (CrosshairConfig::SniperOnly && weaponGroup == 5)) && !LocalEntity.Pawn.Scoped) {
		Render::DrawCrossHair(ImGui::GetBackgroundDrawList(), ImGui::ColorConvertFloat4ToU32(CrosshairConfig::CrossHairColor), LocalEntity);
	}

	if (Config::TriggerBot && GetAsyncKeyState(Config::TriggerHotKey))
		TriggerBot::Run(LocalEntity);

	// dont mind this janky code its not actually getting spread :)
	float spread = static_cast<int>(LocalEntity.Pawn.Velocity * 50.f) / 80;
	Render::SpreadCircle(spread);


	if (Config::AimBot) {
		if (Config::ShowAimFovRange)
			Render::DrawFovCircle(LocalEntity);

		if (GetAsyncKeyState(Config::AimBotHotKey)) {
			if (AimPos != Vec3(0, 0, 0))
				AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
		}
	}
}

