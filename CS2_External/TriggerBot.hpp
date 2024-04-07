#pragma once
#include "Game.h"
#include "Entity.h"
#include "MenuConfig.hpp"
#include <chrono>
#include <random>

namespace TriggerBot {
    inline DWORD TriggerDelay = 90; // no idea why this just breaks all the time

    inline void Run(const CEntity& LocalEntity) {
        CEntity Entity;
        DWORD uHandle = 0;
        if (!ProcessMgr.ReadMemory<DWORD>(LocalEntity.Pawn.Address + Offset::Pawn.iIDEntIndex, uHandle) || uHandle == -1)
            return;

        DWORD64 ListEntry = ProcessMgr.TraceAddress(gGame.GetEntityListAddress(), { 0x8 * (uHandle >> 9) + 0x10,0x0 });
        if (!ListEntry)
            return;

        DWORD64 PawnAddress = 0;
        if (!ProcessMgr.ReadMemory<DWORD64>(ListEntry + 0x78 * (uHandle & 0x1FF), PawnAddress) || !Entity.UpdatePawn(PawnAddress))
            return;

        int weaponGroup = GetWeaponGroup(LocalEntity.Pawn.WeaponName);
        bool AllowShoot = ((!Config::TeamCheck || LocalEntity.Pawn.TeamID != Entity.Pawn.TeamID) && Entity.Pawn.Health > 0) && (weaponGroup == 8 ? (Entity.Pawn.Pos.DistanceTo(LocalEntity.Pawn.Pos) < 200) : true);


        if ((Config::ScopeOnlyT && !LocalEntity.Pawn.Scoped && (weaponGroup == 5 || 1)) || (!AllowShoot) || (!Config::IgnoreFlashT && LocalEntity.Pawn.FlashDuration > 0.f))
            return;

        static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
        auto CurTimePoint = std::chrono::steady_clock::now();
        if (CurTimePoint - LastTimePoint >= std::chrono::milliseconds(TriggerDelay)) {
            const bool isAlreadyShooting = GetAsyncKeyState(VK_LBUTTON) < 0;
            if (!isAlreadyShooting) {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            }
            LastTimePoint = CurTimePoint;
        }
    }
}


