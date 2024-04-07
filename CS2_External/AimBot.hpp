#pragma once
#define _USE_MATH_DEFINES
#include "Game.h"
#include "Entity.h"
#include "MenuConfig.hpp"
#include "View.hpp"
#include <iostream>

#include <algorithm>


inline int GetWeaponGroup(const std::string& weaponName)
{
    std::unordered_map<std::string, int> weaponGroups = {
        {"ct_knife", 0},{"t_knife", 0},
        {"ak47", 1}, {"aug", 1}, {"famas", 1},{"galilar", 1}, {"m4a1_silencer", 1}, {"m4a1", 1}, {"sg556", 1},
        {"mag7", 2}, {"sawedoff", 2}, {"nova", 2}, {"xm1014", 2},
        {"cz75a", 3}, {"elite", 3}, {"fiveseven", 3},{"glock", 3}, {"p2000", 3}, {"p250", 3}, {"revolver", 3},{"tec9", 3}, {"usp", 3},
        {"deagle", 4}, {"revolver", 4},
        {"awp", 5}, {"g3Sg1", 5}, {"scar20", 5}, {"ssg08", 5},
        {"mac10", 6}, {"mp7", 6}, {"mp9", 6}, {"mp5sd", 6},{"ump45", 6}, {"bizon", 6}, {"p90", 6},
        {"smokegrenade", 7}, {"flashbang", 7}, {"molotov", 7},{"incgrenade", 7},{"hegrenade", 7},
        {"taser", 8}, {"zeus", 8}
    };


    if (weaponGroups.count(weaponName)) {
        return weaponGroups[weaponName];
    }
    else {
        return 0;
    }
}

namespace AimControl {
    const float RAD_TO_DEG = 57.295779513f;
    const float PI = 3.14159265359f;

    inline int HotKey = VK_LMENU;
    inline float AimFov = 2.0f;
    inline bool Rcs = false;
    inline bool ScopeOnly = false;
    inline bool IgnoreFlash = false;
    inline Vec2 RCSScale = { 1.0f, 1.0f };
    inline float Smooth = 75.0f;

    inline void AimBot(const CEntity& localEntity, Vec3 localPos, Vec3 aimPos) {
        int weaponGroup = GetWeaponGroup(localEntity.Pawn.WeaponName);
        if (Config::ShowMenu || weaponGroup == 7)
            return;

        if (AimControl::ScopeOnly && !localEntity.Pawn.Scoped && (weaponGroup == 5 || 1))
            return;

        if (!IgnoreFlash && localEntity.Pawn.FlashDuration > 0.f)
            return;


        int centerX = Gui.Window.Size.x / 2, centerY = Gui.Window.Size.y / 2;
        Vec2 angles{ 0, 0 };


        Vec3 offset = aimPos - localPos;
        float distance = offset.Length();

        if (Rcs && localEntity.Pawn.ShotsFired) {
            auto& viewAngles = localEntity.Pawn.ViewAngle;
            auto& aimPunch = localEntity.Pawn.AimPunchAngle;

            Vec2 newAngles = {
                viewAngles.x + (viewAngles.x - aimPunch.x) * 2.0f,
                viewAngles.y + (viewAngles.y - aimPunch.y) * 2.0f
            };

            newAngles.x = std::clamp(newAngles.x, -89.0f, 89.0f);
            newAngles.y = std::fmod(newAngles.y + 180.0f, 360.0f) - 180.0f;
            newAngles.x += centerX;
            newAngles.y += centerY;
            angles = newAngles;
        }

        if (Rcs && localEntity.Pawn.AimPunchCache.Count > 0) {
            Vec2 punchAngle;
            auto& cache = localEntity.Pawn.AimPunchCache;
            if (cache.Count <= 0xFFFF && ProcessMgr.ReadMemory<Vec2>(cache.Data + (cache.Count - 1) * sizeof(Vec3), punchAngle)) {
                angles = punchAngle;
            }
        }

        float radX = angles.x * RCSScale.x / 360.0f * PI, radY = -angles.y * RCSScale.y / 360.0f * PI;
        float siX = sinf(radX), coX = cosf(radX), siY = sinf(radY), coY = cosf(radY);

        float z = offset.z * coX + distance * siX, d = (distance * coX - offset.z * siX) / distance;
        float x = (offset.x * coY - offset.y * siY) * d, y = (offset.x * siY + offset.y * coY) * d;

        offset = Vec3{ x, y, z };
        aimPos = localPos + offset;

        float yaw = atan2f(offset.y, offset.x) * RAD_TO_DEG - localEntity.Pawn.ViewAngle.y;
        float pitch = -atan(offset.z / distance) * RAD_TO_DEG - localEntity.Pawn.ViewAngle.x;

        float norm = sqrt(pow(yaw, 2) + pow(pitch, 2));

        Vec2 screenPos;
        gGame.View.WorldToScreen(Vec3(aimPos), screenPos);

        if (norm < AimFov * 1.4) {
            int x = screenPos.x - Gui.Window.Size.x / 2;
            int y = screenPos.y - Gui.Window.Size.y / 2;

            if (x != 0 || y != 0) {
                int stx = static_cast<int>(x * (1.0f - Smooth / 100));
                int sty = static_cast<int>(y * (1.0f - Smooth / 100));
                mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(stx), static_cast<DWORD>(sty), NULL, NULL);
            }
        }

    }
}


