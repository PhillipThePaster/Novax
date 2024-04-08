#include "..\CS2_External\Hitsounds\Sounds.h"
#include "MenuConfig.hpp"
#include "Entity.h"

unsigned char* sounds[] = { neverlose_sound, skeet_sound, Bell, Bubble, Cod };

namespace Misc {

	struct hitmarker_info {
		float animation_progress;
		bool impacted;
		int damage;
	};

	std::vector<hitmarker_info> hitmarkers;
	hitmarker_info hitmarker;


	void Hitmarker(float hitmarkerSize, float hitmarkerGap) {
		ImGuiIO& io = ImGui::GetIO();
		ImVec2 center = ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);

		for (auto it = hitmarkers.begin(); it != hitmarkers.end();) {
			auto& hitmarker = *it;

			hitmarker.animation_progress += 0.01;
			if (hitmarker.animation_progress > 1.0f)
				hitmarker.animation_progress = 1.0f;

			ImColor col = ImColor(255, 255, 255, 255);

			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x - hitmarkerSize, center.y - hitmarkerSize), ImVec2(center.x - hitmarkerGap, center.y - hitmarkerGap), col, 1.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x - hitmarkerSize, center.y + hitmarkerSize), ImVec2(center.x - hitmarkerGap, center.y + hitmarkerGap), col, 1.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x + hitmarkerSize, center.y - hitmarkerSize), ImVec2(center.x + hitmarkerGap, center.y - hitmarkerGap), col, 1.4f);
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(center.x + hitmarkerSize, center.y + hitmarkerSize), ImVec2(center.x + hitmarkerGap, center.y + hitmarkerGap), col, 1.4f);

			// yes i know it shows the damage from last shot and not current one fuck u || <- fixed this 3.24.24
			if (Config::DamageText) 
				Gui.StrokeText("- " + std::to_string(hitmarker.damage), ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * (0.5f - hitmarker.animation_progress * 0.1f)), ImVec4(255, 150, 20, 255 * 1.0f - hitmarker.animation_progress), 19.f, true);

			if (hitmarker.animation_progress >= 1.0f && !hitmarker.impacted)
				it = hitmarkers.erase(it);
			else
				++it;
			hitmarker.impacted = false;
		}
	}


	void HitSound(const CEntity& aLocalPlayer) noexcept {
		char buffer[256] = "";
		int dmg = 0;
		static int oldDamage = 0;
		uintptr_t ActionTracking;

		if (ProcessMgr.ReadMemory(aLocalPlayer.Controller.Address + Offset::Action_Tracking.m_pActionTrackingServices, ActionTracking) &&
			ProcessMgr.ReadMemory(ActionTracking + Offset::Action_Tracking.m_unTotalRoundDamageDealt, dmg)) {

			if (dmg > oldDamage) {
				if (Config::Hitsound && Config::hitsound_type >= 0 && Config::hitsound_type <= 5) {
					PlaySoundA(reinterpret_cast<char*>(sounds[Config::hitsound_type]), NULL, SND_ASYNC | SND_MEMORY); 	
				}
				hitmarker.animation_progress = 0.0f;
				hitmarker.damage = dmg - oldDamage;
				hitmarker.impacted = true;
				hitmarkers.push_back(hitmarker);
			}
			oldDamage = dmg;
		}
		if (Config::Hitmarker) Hitmarker(Config::HitmarkSize, Config::HitmarkGap);
	}

	// dont use this its so bad going to try and make it not eat fps and also will not show all smokes just 1
	/*
    static inline uintptr_t GetSmokeEntity(int i, uintptr_t EntityListEntry) {
		uintptr_t Entity = EntityListEntry + 0x78 * (i + 1);
		return Entity;
	}
	void NadeManager(CGame Game) noexcept {
		std::vector<std::string> EntityNames = {
			"smokegrenade_projectile", "weapon_smokegrenade","weapon_incgrenade", "molotov_projectile"
		};

		for (int i_smoke = 64; i_smoke < 1024; i_smoke++) {
			uintptr_t SmokeEntity = GetSmokeEntity(i_smoke, Game.GetEntityListEntry());

			uintptr_t ent_base, addr;
			ProcessMgr.ReadMemory<uintptr_t>(SmokeEntity, ent_base);
			Vec3 smokepos;
			char toread[32];
			std::string classname;
			Vec3 COLOR = { 255, 255, 255 };
			ProcessMgr.ReadMemory<uintptr_t>(ent_base + 0x10, addr);
			ProcessMgr.ReadMemory<uintptr_t>(addr + 0x20, addr);
			ProcessMgr.ReadMemory<char[32]>(addr, toread);
			ProcessMgr.ReadMemory<Vec3>(ent_base + Offset::SmokeGrenadeProjectile.vSmokeDetonationPos, smokepos);

			classname = toread;

			if (classname == "smokegrenade_projectile") {
				Vec2 StartPoint, EndPoint;

	
				gGame.View.WorldToScreen(smokepos, EndPoint);

				ImVec2 screenPos(EndPoint.x, EndPoint.y);
				ImGui::GetBackgroundDrawList()->AddText(screenPos, IM_COL32(255, 255, 255, 255), "Smoke Grenade");
			}
		}
	}
	*/
	void NightMode() noexcept{
		if (!Config::Nightmode)return;

		ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ Gui.Window.Size.x, Gui.Window.Size.y }, ImGuiCond_Always);
		ImGui::SetNextWindowBgAlpha(0.f);
		ImGui::Begin("##background", nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDecoration);

		ImVec2 windowPos = ImGui::GetWindowPos();
		ImVec2 windowSize = ImGui::GetWindowSize();


		ImGui::GetBackgroundDrawList()->AddRectFilled(windowPos, ImVec2(windowPos.x + windowSize.x, windowPos.y + windowSize.y), IM_COL32(0, 0, 0, Config::NightmodeBright));

		ImGui::End();
	}
}
