#pragma once
#include <Windows.h>
#include "Utils/ProcessManager.hpp"

namespace Offset
{
	inline DWORD ForceJump;
	inline DWORD ForceCrouch;
	inline DWORD ForceForward;
	inline DWORD ForceLeft;
	inline DWORD ForceRight;

	inline DWORD EntityList;
	inline DWORD Matrix;
	inline DWORD ViewAngle;
	inline DWORD LocalPlayerController;
	inline DWORD LocalPlayerPawn;
	inline DWORD GlobalVars;
	inline DWORD InventoryServices;
	inline DWORD PlantedC4;
	inline DWORD InputSystem;
	inline DWORD Pointer;

	struct
	{
		DWORD Health = 0x334;
		DWORD TeamID = 0x3CB;
		DWORD IsAlive = 0x7EC;
		DWORD PlayerPawn = 0x7E4;
		DWORD iszPlayerName = 0x638;
		DWORD EnemySensor = 0x1440;
		DWORD GravityScale = 0x444;
	}Entity;


	struct {
		DWORD m_vecAbsOrigin = 0xC8;
		DWORD m_pGameSceneNode = 0x318;
	}bomb;


	struct{
		DWORD MovementServices = 0x1140;		// CPlayer_MovementServices*
		DWORD WeaponServices = 0x1100;			// CPlayer_WeaponServices*
		DWORD BulletServices = 0x1718;			// CCSPlayer_BulletServices*
		DWORD CameraServices = 0x1138;			// CPlayer_CameraServices*
		DWORD pClippingWeapon = 0x1308;			// C_CSWeaponBase*

		DWORD m_hMyWeapons = 0x40;

		DWORD StartAccount = 0x1490;
		DWORD isScoped = 0x1400;
		DWORD TotalHit = 0x40;
		DWORD Pos = 0x127C;						// C_BasePlayerPawn::m_vOldOrigin
		DWORD MaxHealth = 0x330;				// C_BaseEntity::m_iMaxHealth
		DWORD CurrentHealth = 0x334;			// C_BaseEntity::m_iHealth
		DWORD GameSceneNode = 0x318;			// C_BaseEntity::m_pGameSceneNode
		DWORD BoneArray = 0x1E0;				// CSkeletonInstance_::m_modelState + CGameSceneNode_::m_vecOrigin
		DWORD angEyeAngles = 0x1578;
		DWORD vecLastClipCameraPos = 0x12EC;
		DWORD iShotsFired = 0x147C;
		DWORD aimPunchAngle = 0x177C;			// C_CSPlayerPawn::m_aimPunchAngle
		DWORD aimPunchCache = 0x17A0;
		DWORD iIDEntIndex = 0x15A4;
		DWORD iTeamNum = 0x3CB;
		DWORD DesiredFov = 0x6CC;
		DWORD iFovStart = 0x214;
		DWORD fFlags = 0x3D4;
		DWORD bSpottedByMask = 0x1698 + 0xC;			// C_CSPlayerPawnBase::entitySpottedState + EntitySpottedState_t::bSpottedByMask
		DWORD m_flEmitSoundTime = 0x1460;
		DWORD Defusing = 0x1408; // m_bIsDefusing || bool
		DWORD m_pItemServices = 0x1108;
		DWORD m_bHasDefuser = 0x40; // bool
		DWORD m_bPawnHasHelmet = 0x41; // bool
		DWORD m_bHasHeavyArmor = 0x42; // bool

		DWORD m_pMovementServices = 0x1140;
		DWORD m_flStamina = 0x4D0; // float
		DWORD m_flVelocityModifier = 0x1484;
		DWORD m_vecAbsVelocity = 0x3D8; // Vector
		DWORD m_bKilledByHeadshot = 0x16C8; // bool
	} Pawn;

	struct{
		DWORD flFlashMaxAlpha = 0x14C8; // float
		DWORD flFlashDuration = 0x14CC; // float
		DWORD m_flFlashBangTime = 0x14B8; // float
	} Grenade;

	struct {
		DWORD m_Glow = 0xBA8;
		DWORD m_iGlowType = 0x30;
		DWORD m_glowColorOverride = 0x40; // Color
		DWORD m_bGlowing = 0x51; // bool
	} Glow;

	struct{
		DWORD RealTime = 0x00;
		DWORD FrameCount = 0x04;
		DWORD MaxClients = 0x10;
		DWORD IntervalPerTick = 0x14;
		DWORD CurrentTime = 0x5A8;
		DWORD CurrentTime2 = 0x30;
		DWORD TickCount = 0x40;
		DWORD IntervalPerTick2 = 0x44;
		DWORD CurrentNetchan = 0x0048;
		DWORD CurrentMap = 0x0180;
		DWORD CurrentMapName = 0x0188;
	} GlobalVar;

	struct
	{
		DWORD m_hPawn = 0x604;
		DWORD m_pObserverServices = 0x1118;
		DWORD m_hObserverTarget = 0x44;
		DWORD m_hController = 0x1294;
		DWORD PawnArmor = 0x7F4;
		DWORD HasHelmet = 0x41;
		DWORD HasDefuser = 0x7F8;
		DWORD m_bIsLocalPlayerController = 0x6C8; // bool
		DWORD Ping = 0x718; // m_hPlayerPing 
	} PlayerController;

	struct{
		DWORD ClippingWeapon = 0x1308;
		DWORD WeaponDataPTR = 0x368;
		DWORD szName = 0xC20;
		DWORD Clip1 = 0x15C8;					// C_BasePlayerWeapon::m_iClip1
		DWORD MaxClip = 0x1FC;					// CBasePlayerWeaponVData::m_iMaxClip1
		DWORD CycleTime = 0xC44;
		DWORD Penetration = 0xD4C;
		DWORD WeaponType = 0x248;
		DWORD Inaccuracy = 0xC8C;				// CCSWeaponBaseVData::m_flInaccuracyMove
		DWORD m_szName = 0xC18;

		DWORD WeaponSize = 0x50;
		DWORD ActiveWeapon = 0x58;
		DWORD Item = 0x50;						// C_AttributeContainer::m_Item
		DWORD ItemDefinitionIndex = 0x1BA;
		DWORD m_MeshGroupMask = 0x180;			// CModelState::m_MeshGroupMask
		DWORD m_flSpread = 0xC54; // float
	} WeaponBaseData;

	struct{
		DWORD AttributeManager = 0x1098;		// C_AttributeContainer
		DWORD FallbackPaintKit = 0x1548;
		DWORD FallbackSeed = 0x154C;
		DWORD FallbackWear = 0x1550;
		DWORD FallbackStatTrak = 0x1554;
		DWORD szCustomName = 0x2D0;

		DWORD EntityQuality = 0x1BC;			// EconItemView::m_iEntityQuality
		DWORD ItemIDHigh = 0x1D0;				// EconItemView::m_iItemIDHigh
	} EconEntity;

	struct{
		DWORD m_bBeingDefused = 0xF14;
		DWORD m_flDefuseCountDown = 0xF28;
		DWORD m_nBombSite = 0xEDC;
	    DWORD m_flC4Blow = 0xF08;
	} C4;

	struct {
		DWORD m_pDamageServices = 0x710;

		DWORD m_perRoundStats = 0x40;
		DWORD m_matchStats = 0x90;
		DWORD m_iNumRoundKills = 0x110;
		DWORD m_iNumRoundKillsHeadshots = 0x114;
		DWORD m_unTotalRoundDamageDealt = 0x118;
		DWORD m_pActionTrackingServices = 0x708;
	}Action_Tracking;

	struct
	{
		DWORD MoneyServices = 0x6F8;
		DWORD Account = 0x40;
		DWORD TotalCashSpent = 0x48;
		DWORD CashSpentThisRound = 0x4C;
	} InGameMoneyServices;

	struct // C_BaseCSGrenadeProjectile
	{
		DWORD nSmokeEffectTickBegin = 0x1160; // int32_t
		DWORD bDidSmokeEffect = 0x1164; // bool
		DWORD nRandomSeed = 1; // int32_t
		DWORD vSmokeColor = 0x116C; // Vector
		DWORD vSmokeDetonationPos = 0x1178; // Vector
		DWORD VoxelFrameData = 0x1188; // CUtlVector<uint8_t>
		DWORD bSmokeVolumeDataReceived = 0x11A0; // bool
		uintptr_t bSmokeEffectSpawned = 0x11A1; // bool
	} SmokeGrenadeProjectile;

	namespace Signatures{

		const std::string InventoryServices = "E8 ?? ?? ?? ?? 8B 45 D0 48 8B 55 D8";
		const std::string GlobalVars = "48 89 15 ?? ?? ?? ?? 48 8D 05 ?? ?? ?? ?? 48 85 D2";
		const std::string EntityList = "48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1 EB";
		const std::string LocalPlayerController = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 ?? 8B 88";
		const std::string ViewMatrix = "48 8D 0D ?? ?? ?? ?? 48 C1 E0 06";
		const std::string LocalPlayerPawn = "48 8D 05 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC 48 83 EC ?? 8B 0D";
		const std::string PlantedC4 = "48 8B 15 ?? ?? ?? ?? FF C0 48 8D 4C 24 40";
		const std::string InputSystem = "48 89 05 ?? ?? ?? ?? 48 8D 05";
	}

	bool UpdateOffsets();
}