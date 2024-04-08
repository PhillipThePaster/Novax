#pragma once
#include "Render.hpp"
#include "images.h"

ID3D11ShaderResourceView* Adolf_Image = NULL;
ID3D11ShaderResourceView* Putin_Image = NULL;
ID3D11ShaderResourceView* Zelensky_Image = NULL;


int AdolfH = 0, AdolfW = 0;
int PutinH = 0, PutinW = 0;
int ZeleH = 0, ZeleW = 0;

struct WeaponIconSize {
	float width;
	float height;
	float offsetX;
	float offsetY;
};
std::unordered_map<std::string, WeaponIconSize> weaponIconSizes = {
	{"t_knife", {20.0f, 20.0f, -8.0f, 0.0f}},
	{"ct_knife", {20.0f, 20.0f, -8.0f, 0.0f}},
	{"deagle", {20.0f, 20.0f, -8.0f, 0.0f}},
	{"elite", {20.0f, 20.0f, 0.0f, 0.0f}},
	{"fiveseven", {20.0f, 20.0f, 0.0f, 0.0f}},
	{"glock", {20.0f, 20.0f, 0.0f, 0.0f}},
	{"revolver", {20.0f, 20.0f, -5.0f, 0.0f}},
	{"p2000", {20.0f, 20.0f, 0.0f, 0.0f}},
	{"p250", {20.0f, 20.0f, 0.0f, 0.0f}},
	{"usp", {20.0f, 20.0f, 0.0f, 0.0f}},
	{"tec9", {20.0f, 20.0f, 0.0f, 0.0f}},
	{"cz75a", {20.0f, 20.0f, 0.0f, 0.0f}},
	{"mac10", {20.0f, 20.0f, 0.0f, 0.0f}},
	{"ump45", {20.0f, 20.0f, -10.0f, 0.0f}},
	{"bizon", {20.0f, 20.0f, -10.0f, 0.0f}},
	{"mp7", {20.0f, 20.0f, -5.0f, 0.0f}},
	{"mp9", {20.0f, 20.0f, -10.0f, 0.0f}},
	{"p90", {20.0f, 20.0f, -10.0f, 0.0f}},
	{"galilar", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"famas", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"m4a1_silencer", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"m4a1", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"aug", {20.0f, 20.0f, -10.0f, 0.0f}},
	{"sg556", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"ak47", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"g3sg1", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"scar20", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"awp", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"ssg08", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"xm1014", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"sawedoff", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"mag7", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"nova", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"negev", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"m249", {20.0f, 20.0f, -15.0f, 0.0f}},
	{"taser", {20.0f, 20.0f, 0.0f, 0.0f}},
	{"flashbang", {20.0f, 20.0f, 5.0f, 0.0f}},
	{"hegrenade", {20.0f, 20.0f, 5.0f, 0.0f}},
	{"smokegrenade", {20.0f, 20.0f, 5.0f, 0.0f}},
	{"molotov", {20.0f, 20.0f, 5.0f, 0.0f}},
	{"decoy", {20.0f, 20.0f, 5.0f, 0.0f}},
	{"incgrenade", {20.0f, 20.0f, 5.0f, 0.0f}},
	{"c4", {20.0f, 20.0f, 0.0f, 0.0f}},
};

const char* GunIcon(const std::string weapon) {
	std::map<std::string, const char*> gunIcons = {
		{"ct_knife", "]"},
		{"t_knife", "["},
		{"deagle", "A"},
		{"elite", "B"},
		{"fiveseven", "C"},
		{"glock", "D"},
		{"revolver", "J"},
		{"p2000", "E"},
		{"p250", "F"},
		{"usp", "G"},
		{"tec9", "H"},
		{"cz75a", "I"},
		{"mac10", "K"},
		{"ump45", "L"},
		{"bizon", "M"},
		{"mp7", "N"},
		{"mp9", "N"},
		{"p90", "O"},
		{"galilar", "Q"},
		{"famas", "R"},
		{"m4a1_silencer", "T"},
		{"m4a1", "S"},
		{"aug", "U"},
		{"sg556", "V"},
		{"ak47", "W"},
		{"g3sg1", "X"},
		{"scar20", "Y"},
		{"awp", "Z"},
		{"ssg08", "a"},
		{"xm1014", "b"},
		{"sawedoff", "c"},
		{"mag7", "d"},
		{"nova", "e"},
		{"negev", "f"},
		{"m249", "g"},
		{"taser", "h"},
		{"flashbang", "i"},
		{"hegrenade", "j"},
		{"smokegrenade", "k"},
		{"molotov", "l"},
		{"decoy", "m"},
		{"incgrenade", "n"},
		{"c4", "o"}
	};

	auto it = gunIcons.find(weapon);
	return (it != gunIcons.end()) ? it->second : "";
}

const char* RenderWeaponIcon(const CEntity& Entity) {
	uintptr_t ClippingWeapon, WeaponData, WeaponNameAddress;
	ProcessMgr.ReadMemory(Entity.Pawn.Address + Offset::Pawn.pClippingWeapon, ClippingWeapon);
	ProcessMgr.ReadMemory(ClippingWeapon + Offset::WeaponBaseData.WeaponDataPTR, WeaponData);
	ProcessMgr.ReadMemory(WeaponData + Offset::WeaponBaseData.szName, WeaponNameAddress);
	std::string weaponName = "Invalid Weapon Name";

	if (!WeaponNameAddress) {
		weaponName = "NULL";
	}
	else {
		weaponName = Entity.Pawn.WeaponName;
	}
	std::string weaponIcon = GunIcon(weaponName);
	return weaponIcon.c_str();
}


namespace Esp {

	ImVec4 Get2DBox(const CEntity& Entity) {
		BoneJointPos Head = Entity.GetBone().BonePosList[BONEINDEX::head];
		Vec3 diff = Head.Pos - Entity.Pawn.Pos;
		if (diff.Length() > 70.f) {
			return ImVec4{ 0.1f, 0.1f, 0.1f, 0.1f };
		}
		Vec2 Size, Pos;
		Size.y = (Entity.Pawn.ScreenPos.y - Head.ScreenPos.y) * 1.2;
		Size.x = Size.y * 0.6;
		Pos = ImVec2(Entity.Pawn.ScreenPos.x - Size.x / 2 + 2, Head.ScreenPos.y - Size.y * 0.12);

		return ImVec4{ Pos.x,Pos.y,Size.x,Size.y };
	}


	void DrawBone(const CEntity& Entity, float Thickness) {
		if (!Config::Skeleton) return;
		for (const auto& jointList : BoneJointList::List) {
			BoneJointPos prev, curr;
			for (auto index : jointList) {
				curr = Entity.GetBone().BonePosList[index];
				if (prev.Pos != Vec3() && prev.IsVisible && curr.IsVisible) {
				//	Gui.Line(prev.ScreenPos, curr.ScreenPos, ImColor(0,0,0,255), Thickness + 1);
					Gui.Line(prev.ScreenPos, curr.ScreenPos, Config::BoneColor, Thickness);
				}
				prev = curr;
			}
		}
	}
	//outlined skeleton 
	/*
	 if (prev.Pos != Vec3() && prev.IsVisible && curr.IsVisible) {
		 Gui.Line(prev.ScreenPos, curr.ScreenPos, ImColor(0, 0, 0, 255), Thickness + 2);
		 Gui.Line(prev.ScreenPos, curr.ScreenPos, Color, Thickness);
	 }
	*/

	void DrawHeadCircle(const CEntity& Entity, ImColor Color) {
		if (!Config::HeadCircle) return;

		Vec2 CenterPos = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos;
		float Radius = abs(Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.y - Entity.GetBone().BonePosList[BONEINDEX::neck_0].ScreenPos.y) + 2;

		Gui.Circle(CenterPos, Radius, ImColor(0,0,0,255), 2.f);
		Gui.Circle(CenterPos, Radius, Color, 1.f);
	}

	void EyeRay(const CEntity& Entity, const float Length, ImColor Color, float Thickness) {
		if (!Config::ShowEyeRay) return;
		Vec2 StartPoint, EndPoint;
		Vec3 Temp;
		BoneJointPos Head = Entity.GetBone().BonePosList[BONEINDEX::head];
		StartPoint = Head.ScreenPos;
		float LineLength = cos(Entity.Pawn.ViewAngle.x * M_PI / 180) * Length;
		Temp.x = Head.Pos.x + cos(Entity.Pawn.ViewAngle.y * M_PI / 180) * LineLength;
		Temp.y = Head.Pos.y + sin(Entity.Pawn.ViewAngle.y * M_PI / 180) * LineLength;
		Temp.z = Head.Pos.z - sin(Entity.Pawn.ViewAngle.x * M_PI / 180) * Length;
		if (!gGame.View.WorldToScreen(Temp, EndPoint)) return;
		Gui.Line(StartPoint, EndPoint, Color, Thickness);
	}

	void LineToEnemy(ImVec4 Rect, ImColor Color, float Thickness) {
		if (!Config::Snapline) return;
		Gui.Line({ Rect.x + Rect.z / 2,Rect.y + Rect.w }, { Gui.Window.Size.x / 2, Gui.Window.Size.y }, ImColor(0, 0, 0, 255), Thickness + 2);
		Gui.Line({ Rect.x + Rect.z / 2,Rect.y + Rect.w }, { Gui.Window.Size.x / 2, Gui.Window.Size.y }, Color, Thickness);
	}



	void Render(ImVec4 Rect, const CEntity& Entity, const CEntity& LocalEntity, int LocalPlayerControllerIndex, int Index) {      
		DWORD64 spottedMask = Entity.Pawn.bSpottedByMask;
		bool isSpotted = (Entity.Pawn.bSpottedByMask & (DWORD64(1) << LocalPlayerControllerIndex)) || (LocalEntity.Pawn.bSpottedByMask & (DWORD64(1) << Index));

		int distance = static_cast<int>(Entity.Pawn.Pos.DistanceTo(LocalEntity.Pawn.Pos) / 100);

		auto bonecol = Config::BoneColor;
		auto col = Config::BoxColor;
		auto FillCol = Config::BoxFilledColor;

		// for player list i was working on
		/*
		std::vector<std::string> redNames = { "Dimmi", "Icy", "Dimmi" };

		for (const auto& name : redNames) {
			if (Entity.Controller.PlayerName == name) {
				col = ImColor(1.0f, 0.0f, 0.0f, 1.0f);
				break;
			}
		}
		*/		
		
		if (Config::VisCheck) {
			if (isSpotted) {
				//bonecol = Config::BoneVisColor;
				col = Config::VisibleColor;
				FillCol = Config::BoxFilledVisColor;
			}
		}

		auto vList = ImGui::GetBackgroundDrawList();

		float alpha = 130;
		float Atop = 0;
		ImVec2 topLeft = { Rect.x, Rect.y };
		ImVec2 bottomRight = { Rect.x + Rect.z, Rect.y + Rect.w };
		ImU32 colorTop = IM_COL32(ImColor(FillCol).Value.x * 255, ImColor(FillCol).Value.y * 255, ImColor(FillCol).Value.z * 255, Atop);
		ImU32 colorBottom = IM_COL32(ImColor(FillCol).Value.x * 255, ImColor(FillCol).Value.y * 255, ImColor(FillCol).Value.z * 255, alpha);



		if (Config::ShowBoxESP) {
			float lineW = (Rect.z / 3);
			float lineH = (Rect.w / 3);
			auto outlineCol = ImColor(0.0f, 0.0f, 0.0f, 1.0f);

			if (Config::BoxType == 0) {
				Gui.Rectangle({ Rect.x, Rect.y }, { Rect.z, Rect.w }, { 0, 0, 0, 255 }, 3);
				Gui.Rectangle({ Rect.x, Rect.y }, { Rect.z, Rect.w }, col, 1.3);
			}

			if (Config::BoxType == 1) {
				//Outline
				vList->AddLine(ImVec2(Rect.x, Rect.y - 1.3 / 2), ImVec2(Rect.x, Rect.y + lineH), outlineCol, 3);
				vList->AddLine(ImVec2(Rect.x - 1.3 / 2, Rect.y), ImVec2(Rect.x + lineW, Rect.y), outlineCol, 3);
				vList->AddLine(ImVec2(Rect.x + Rect.z - lineW, Rect.y), ImVec2(Rect.x + Rect.z + 1.3 / 2, Rect.y), outlineCol, 3);
				vList->AddLine(ImVec2(Rect.x + Rect.z, Rect.y - 1.3 / 2), ImVec2(Rect.x + Rect.z, Rect.y + lineH), outlineCol, 3);
				vList->AddLine(ImVec2(Rect.x, Rect.y + Rect.w - lineH), ImVec2(Rect.x, Rect.y + Rect.w + 1.3 / 2), outlineCol, 3);
				vList->AddLine(ImVec2(Rect.x - 1.3 / 2, Rect.y + Rect.w), ImVec2(Rect.x + lineW, Rect.y + Rect.w), outlineCol, 3);
				vList->AddLine(ImVec2(Rect.x + Rect.z - lineW, Rect.y + Rect.w), ImVec2(Rect.x + Rect.z + 1.3 / 2, Rect.y + Rect.w), outlineCol, 3);
				vList->AddLine(ImVec2(Rect.x + Rect.z, Rect.y + Rect.w + 1.3 / 2), ImVec2(Rect.x + Rect.z, Rect.y + Rect.w - lineH), outlineCol, 3);
				//corners
				vList->AddLine(ImVec2(Rect.x, Rect.y - 1.3 / 2), ImVec2(Rect.x, Rect.y + lineH), col, 1.3);
				vList->AddLine(ImVec2(Rect.x - 1.3 / 2, Rect.y), ImVec2(Rect.x + lineW, Rect.y), col, 1.3);
				vList->AddLine(ImVec2(Rect.x + Rect.z - lineW, Rect.y), ImVec2(Rect.x + Rect.z + 1.3 / 2, Rect.y), col, 1.3);
				vList->AddLine(ImVec2(Rect.x + Rect.z, Rect.y - 1.3 / 2), ImVec2(Rect.x + Rect.z, Rect.y + lineH), col, 1.3);
				vList->AddLine(ImVec2(Rect.x, Rect.y + Rect.w - lineH), ImVec2(Rect.x, Rect.y + Rect.w + 1.3 / 2), col, 1.3);
				vList->AddLine(ImVec2(Rect.x - 1.3 / 2, Rect.y + Rect.w), ImVec2(Rect.x + lineW, Rect.y + Rect.w), col, 1.3);
				vList->AddLine(ImVec2(Rect.x + Rect.z - lineW, Rect.y + Rect.w), ImVec2(Rect.x + Rect.z + 1.3 / 2, Rect.y + Rect.w), col, 1.3);
				vList->AddLine(ImVec2(Rect.x + Rect.z, Rect.y + Rect.w + 1.3 / 2), ImVec2(Rect.x + Rect.z, Rect.y + Rect.w - lineH), col, 1.3);
			}

		}

		// Filled Box
		if (Config::FilledBox) {
			if (Config::BoxFillType == 0) {
				Gui.RectangleFilled({ Rect.x, Rect.y }, { Rect.z, Rect.w }, FillCol);
			}

			if (Config::BoxFillType == 1) {
				vList->AddRectFilledMultiColor(topLeft, bottomRight, colorTop, colorTop, colorBottom, colorBottom);
			}
		}

		// ik this is bad im just to lazy to actually implement it 
		uintptr_t Itemservices, Weaponservices, weapons;
		bool HasHelmet = false, HasDefuser = false;

		ProcessMgr.ReadMemory(Entity.Pawn.Address + Offset::Pawn.m_pItemServices, Itemservices);
		ProcessMgr.ReadMemory(Itemservices + Offset::Pawn.m_bPawnHasHelmet, HasHelmet);
		ProcessMgr.ReadMemory(Itemservices + Offset::Pawn.m_bHasDefuser, HasDefuser);

		ProcessMgr.ReadMemory(Entity.Pawn.Address + Offset::Pawn.WeaponServices, Weaponservices);
		ProcessMgr.ReadMemory(Weaponservices + Offset::Pawn.m_hMyWeapons + 0x8, weapons);


		// Flags
		std::string flags;
		std::string dis_str = std::to_string(distance) + "m";

		if (Config::selectedFlags & (1 << 0)) flags += "$" + std::to_string(Entity.Controller.Money) + "\n";
		if ((Config::selectedFlags & (1 << 1)) && (Entity.Pawn.Health < 30))flags += "Lethal\n";
		if (Config::selectedFlags & (1 << 2) && Entity.Pawn.FlashDuration > 30) flags += "Flashed\n";
		if (Config::selectedFlags & (1 << 3) && HasHelmet && Entity.Pawn.Armor > 0) flags += "Hk\n";
		if (Config::selectedFlags & (1 << 4) && HasDefuser) flags += "Defuser";
		if ((Config::selectedFlags & (1 << 5)) && Entity.Pawn.Scoped) flags += "Scoped\n";
		if ((Config::selectedFlags & (1 << 6)) && Entity.Pawn.Defusing) flags += "Defusing\n";
		if (Config::selectedFlags & (1 << 7))flags += dis_str + "\n";
		if (Config::selectedFlags & (1 << 8))flags += (Entity.Controller.Ping == 0) ? "BOT\n" : std::to_string(Entity.Controller.Ping) + "ms\n";
		if (Config::selectedFlags & (1 << 9)) flags += (isSpotted) ? "Visible\n" : "Hidden\n";

		//if (Entity.Controller.HasHelmet) flags += "HK\n"; // shit dont work
		//if (Entity.Pawn.HasHeavy) flags += "HV\n"; // shit dont work
		//flags += "(" + std::to_string(Entity.Pawn.Pos.x) + ", " + std::to_string(Entity.Pawn.Pos.y) + ", " + std::to_string(Entity.Pawn.Pos.z) + ")" + "\n"; // this is for testing purposes 

		int flagpos = 4;
		if (Config::ShowArmourBar)
			flagpos += 4;

		Gui.StrokeText(flags.c_str(), { Rect.x + Rect.z + flagpos, Rect.y }, ImColor(255, 255, 255, 255), 12, false);

		std::string weaponIcon = GunIcon(Entity.Pawn.WeaponName);
		if (Config::ShowWeaponESP) {
			if (Config::WeaponStyle == 0) {
				WeaponIconSize iconSize = weaponIconSizes[Entity.Pawn.WeaponName];
				ImVec2 textPosition = { Rect.x + (Rect.z - iconSize.width) / 2 + iconSize.offsetX, Rect.y + Rect.w + ((Config::ShowAmmoBar) ? 8 : 3) + iconSize.offsetY };
				ImVec2 textSize = ImGui::GetIO().Fonts->Fonts[1]->CalcTextSizeA(15.0f, FLT_MAX, 0, weaponIcon.c_str());
				textPosition.x = Rect.x + (Rect.z - textSize.x) / 2;

				for (int i = -1; i <= 1; i++)
					for (int j = -1; j <= 1; j++)
						ImGui::GetBackgroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[1], 14.f, ImVec2{ textPosition.x + i, textPosition.y + j }, ImColor(0, 0, 0, 255), weaponIcon.c_str());

				ImGui::GetBackgroundDrawList()->AddText(ImGui::GetIO().Fonts->Fonts[1], 14.f, textPosition, Config::Weaponcolor, weaponIcon.c_str());
			}

			if (Config::WeaponStyle == 1) {
				auto yOffset = (Config::ShowAmmoBar) ? 5 : 0;

				Gui.StrokeText(Entity.Pawn.WeaponName, { Rect.x + Rect.z / 2, Rect.y + Rect.w + yOffset }, Config::Weaponcolor, 13, true);
			}
		}

		if (Config::ShowPlayerName){
			Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2, Rect.y - (Config::ShowFlashBar == 1 ? 17 : 13) }, Config::Namecolor, 12, true); // flash bar is not in the cheat rn but will be 
		}



		// dont use this please its so stupid
		if (Adolf_Image == nullptr) {
			Gui.LoadTextureFromMemory(Images::Adolf, sizeof Images::Adolf, &Adolf_Image, &AdolfH, &AdolfH);
			Gui.LoadTextureFromMemory(Images::Putin, sizeof Images::Putin, &Putin_Image, &PutinW, &PutinH);
			Gui.LoadTextureFromMemory(Images::Zelensky, sizeof Images::Zelensky, &Zelensky_Image, &ZeleW, &ZeleH);
		}

		ImTextureID image = nullptr;
		switch (Config::ImgType) {
		case 1:
			image = Adolf_Image;
			break;
		case 2:
			image = Putin_Image;
			break;
		case 3:
			image = Zelensky_Image;
			break;
		}

		if (image != nullptr) {
			ImGui::GetBackgroundDrawList()->AddImage(image, ImVec2(Rect.x, Rect.y), { ImVec2(Rect.x, Rect.y).x + ImVec2(Rect.z, Rect.w).x, ImVec2(Rect.x, Rect.y).y + ImVec2(Rect.z, Rect.w).y });
		}


	}


	void drawing_3D(ImVec4 Rect, const CEntity& Entity, const CEntity& LocalEntity, int LocalPlayerControllerIndex, int Index) {

		Render::Square3D(Entity.Pawn.Pos, { 40, 50, Rect.y }, Config::zeusRangeColor, 0.5f); // first horizontal x || second horizontal y

	}


	// gonna make it not use this dogshit soon and just use bars that can be easily customized / used for other bars | Armour / Ammo
	class HealthBar
	{
	private:
		using TimePoint_ = std::chrono::steady_clock::time_point;
	private:
		const int ShowBackUpHealthDuration = 500;
		float MaxHealth = 0.f;
		float CurrentHealth = 0.f;
		float LastestBackupHealth = 0.f;
		ImVec2 RectPos{};
		ImVec2 RectSize{};
		bool InShowBackupHealth = false;
		TimePoint_ BackupHealthTimePoint{};
	public:
		ImDrawList* DrawList = ImGui::GetBackgroundDrawList();
		HealthBar() {}
		void DrawHealthBar_Horizontal(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, const ImColor& HealthColorTop);
		void DrawHealthBar_Vertical(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, const ImColor& HealthColorTop);
	private:
		ImColor Mix(ImColor Col_1, ImColor Col_2, float t);
		ImColor BackupHealthColor = ImColor(255, 255, 255, 220);
		ImColor HealthbarMin = ImColor(255, 0, 0, 255);
		ImColor BGC = ImColor(20, 20, 20, 220);
	};

	void HealthBar::DrawHealthBar_Horizontal(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, const ImColor& HealthColorTop) {
		this->MaxHealth = MaxHealth;
		this->RectPos = Pos;
		this->RectSize = Size;

		float AnimationSpeed = 1.2f;
		float Proportion = CurrentHealth / MaxHealth;
		float BarWidth = Size.x * Proportion;

		if (CurrentHealth > LastestBackupHealth) {
			LastestBackupHealth += AnimationSpeed;
			if (LastestBackupHealth > CurrentHealth)
				LastestBackupHealth = CurrentHealth;
		}
		else {
			LastestBackupHealth -= AnimationSpeed;
			if (LastestBackupHealth < CurrentHealth)
				LastestBackupHealth = CurrentHealth;
		}


		ImVec2 BarStart = Pos;
		ImVec2 BarEnd = { BarStart.x + BarWidth, BarStart.y + Size.y };
		ImColor Color = Mix(HealthColorTop, HealthbarMin, Proportion);
		DrawList->AddRectFilled(RectPos, { RectPos.x + RectSize.x, RectPos.y + RectSize.y }, BGC, 1);
		DrawList->AddRectFilled(BarStart, BarEnd, Color, 0);
		DrawList->AddRect(RectPos, { RectPos.x + RectSize.x, RectPos.y + RectSize.y }, BGC, 0, 3);

		ImVec2 textPos = { Pos.x + BarWidth, Pos.y + Size.y - 5 - LastestBackupHealth / MaxHealth * Size.y };
		if (CurrentHealth < MaxHealth) {
			std::string displayText = std::to_string(static_cast<int>(CurrentHealth));
			Gui.StrokeText(displayText, textPos, ImColor(255, 255, 255, 255), 10, true);
		}
	}

	void HealthBar::DrawHealthBar_Vertical(float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, const ImColor& HealthColorTop) {
		this->MaxHealth = MaxHealth;
		this->RectPos = Pos;
		this->RectSize = Size;

		float AnimationSpeed = 1.2f;
		float Proportion = CurrentHealth / MaxHealth;
		float Height = RectSize.y * Proportion;

		if (CurrentHealth > LastestBackupHealth) {
			LastestBackupHealth += AnimationSpeed;
			if (LastestBackupHealth > CurrentHealth)
				LastestBackupHealth = CurrentHealth;
		}
		else {
			LastestBackupHealth -= AnimationSpeed;
			if (LastestBackupHealth < CurrentHealth)
				LastestBackupHealth = CurrentHealth;
		}

		ImColor Color = Mix(HealthColorTop, HealthbarMin, Proportion);
		DrawList->AddRectFilled(RectPos, { RectPos.x + RectSize.x, RectPos.y + RectSize.y }, BGC, 1);
		DrawList->AddRectFilled({ RectPos.x, RectPos.y + RectSize.y - LastestBackupHealth / MaxHealth * RectSize.y }, { RectPos.x + RectSize.x, RectPos.y + RectSize.y }, Color, 1, 0);
		DrawList->AddRect(RectPos, { RectPos.x + RectSize.x, RectPos.y + RectSize.y }, BGC, 0, 3);

		ImVec2 textPos = { RectPos.x - (4), RectPos.y + RectSize.y - LastestBackupHealth / MaxHealth * RectSize.y };

		if (Config::HealthText) {
			if (CurrentHealth < MaxHealth) {
				std::string displayText = std::to_string(static_cast<int>(CurrentHealth));
				Gui.StrokeText(displayText, textPos, ImColor(255, 255, 255, 255), 10, true);
			}
		}
	}


	ImColor HealthBar::Mix(ImColor Col_1, ImColor Col_2, float t)
	{
		ImColor Col;
		Col.Value.x = t * Col_1.Value.x + (1 - t) * Col_2.Value.x;
		Col.Value.y = t * Col_1.Value.y + (1 - t) * Col_2.Value.y;
		Col.Value.z = t * Col_1.Value.z + (1 - t) * Col_2.Value.z;
		Col.Value.w = Col_1.Value.w;
		return Col;
	}

	void DrawHealthBar(DWORD Sign, float MaxHealth, float CurrentHealth, ImVec2 Pos, ImVec2 Size, bool Horizontal, const ImColor& HealthColorTop)
	{
		static std::map<DWORD, HealthBar> HealthBarMap;
		if (!HealthBarMap.count(Sign))
		{
			HealthBarMap.insert({ Sign, HealthBar() });
		}
		if (HealthBarMap.count(Sign))
		{
			if (Horizontal)
				HealthBarMap[Sign].DrawHealthBar_Horizontal(MaxHealth, CurrentHealth, Pos, Size, HealthColorTop);
			else
				HealthBarMap[Sign].DrawHealthBar_Vertical(MaxHealth, CurrentHealth, Pos, Size, HealthColorTop);
		}
	}

	// rlly bad code
	void DrawArmorBar(DWORD Sign, float MaxArmor, float CurrentArmor, ImVec2 Pos, ImVec2 Size, const ImColor& ArmourColor)
	{
		static std::map<DWORD, HealthBar> HealthBarMap;
		if (!HealthBarMap.count(Sign))
			HealthBarMap.insert({ Sign,HealthBar() });

		if (HealthBarMap.count(Sign))
			HealthBarMap[Sign].DrawHealthBar_Vertical(MaxArmor, CurrentArmor, Pos, Size, ArmourColor);
	}

	void DrawAmmoBar(DWORD Sign, float MaxAmmo, float CurrentAmmo, ImVec2 Pos, ImVec2 Size, const ImColor& AmmoColor)
	{
		static std::map<DWORD, HealthBar> HealthBarMap;
		if (!HealthBarMap.count(Sign))
			HealthBarMap.insert({ Sign,HealthBar() });

		if (HealthBarMap.count(Sign))
			HealthBarMap[Sign].DrawHealthBar_Horizontal(MaxAmmo, CurrentAmmo, Pos, Size, AmmoColor);
	}

}
