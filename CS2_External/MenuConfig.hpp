#pragma once
#include "Game.h"
#include "Bone.h"


namespace Config {
	inline std::string path = "";
	//aimbot
	inline bool AimBot = false;
	inline bool ShowAimFovRange = true;
	inline int AimBotHotKey = 0;
	inline int  AimPosition = 0;// 0: head 1: neck 3: spine
	inline DWORD  AimPositionIndex = BONEINDEX::head;
	inline bool AimBlind = false;
	inline bool RecoilFov = false; // dont change

	inline bool AimTeam = false;

	inline bool RCS = false; // dont change

	// broken weapon configs 
	inline int smooth = 75;
	inline float Aimfov = 2;
	//general
	inline BONEINDEX Aimpos = head; // NONE OF THIS FUCKING SHIT WORKS IM GOING TO FUCKING KMS I IMPLEMENTED A FULL FUCKING CUSTOM AIM POS SYSTEM AND IT DIDNT WORK
	inline float aimfov = 2;
	inline float aimsmooth = 84;
	inline bool Grcs = true; 
	inline float GrcsV[2] = { 2.f, 2.f };
	//rifle
	inline BONEINDEX RifleAimpos = neck_0;
	inline float Raimfov = 2;
	inline float Raimsmooth = 76;
	inline bool Rrcs = true;
	inline float RrcsV[2] = { 2.f, 2.f };
	//pistol
	inline BONEINDEX PistolAimpos = head;
	inline float Paimfov = 1;
	inline float Paimsmooth = 46;
	inline bool Prcs = true;
	inline float PrcsV[2] = { 1.4f, 1.2f };
	//heavy pistol
	inline BONEINDEX HPistolAimpos = head;
	inline float Hpaimfov = 1;
	inline float Hpaimsmooth = 40;
	inline bool HPrcs = true;
	inline float HPrcsV[2] = { 1.f, 1.f };
	//sniper
	inline BONEINDEX  SAimpos = head;
	inline float Saimfov = 0;
	inline float Saimsmooth = 4;
	inline bool Srcs = true;
	inline float SrcsV[2] = { 0.f, 0.f };
	//smg
	inline BONEINDEX SMGAimpos = head;
	inline float SMGaimfov = 3;
	inline float SMGaimsmooth = 77;
	inline bool SMGrcs = true;
	inline float SMGrcsV[2] = { 1.3f, 1.3f };



	inline bool VisCheck = false;
	inline bool VisibleCheck = false;
	//col
	inline ImColor AimFovRangeColor = ImColor(230, 230, 230, 255);

	//triggerbot
	inline bool TriggerBot = true;
	inline int TriggerHotKey = 0;
	inline bool IgnoreFlashT = false;
	inline bool ScopeOnlyT = false;
	inline bool TriggerbotTeamcheck = true;


	//esp
	inline bool ShowBoxESP = false;
	inline bool ShowCornerBoxEsp = true;
	inline bool FilledBox = false;

	inline bool ShowHealthBar = true;
	inline bool ShowArmourBar = false;
	inline bool ShowAmmoBar = false;
	inline bool ShowFlashBar = false;

	inline bool Skeleton = true;
	inline bool ShowPlayerName = true;
	inline bool ShowWeaponESP = true;
	inline bool HealthText = true;
	inline bool ShowDistance = false;
	inline bool HeadCircle = false;
	inline bool ShowEyeRay = false;
	inline bool Snapline = false;
	inline bool OOFarrow = false;

	inline bool EnemySoundEsp = false;
	inline bool LocalSoundEsp = false;

	inline int  BoxType = 0;
	inline int  BoxFillType = 1;
	inline int  HealthBarType = 0;
	inline int  HeadStyle = 0;
	inline int  WeaponStyle = 0;
	inline int  RenderDistance = 0;
	inline int  ImgType = 0;

	inline unsigned int selectedFlags = 0;

	inline bool VisibleEsp = false;
	inline bool TeamCheck = true;
	inline bool OBSBypass = false;
	inline bool EspVisCheck = false;
	inline bool SpectateEsp = true;

	inline ImColor BoxColor = ImColor(255, 255, 255, 255);
	inline ImColor VisibleColor = ImColor(255, 255, 0, 255);
	inline ImColor BoxFilledColor = ImColor(105, 137, 239, 106);
	inline ImColor BoxFilledVisColor = ImColor(255, 255, 0, 255); // vischeck color
	inline ImColor BoneColor = ImColor(255, 255, 255, 255);
	inline ImColor BoneVisColor = ImColor(255, 255, 0, 255); // vischeck color
	inline ImColor SnaplineCol = ImColor(255, 255, 255, 255);
	inline ImColor HeadColor = ImColor(255, 255, 255, 255);
	inline ImColor EyeRayColor = ImColor(255, 0, 0, 255);
	inline ImColor Namecolor = ImColor(255, 255, 255, 255);
	inline ImColor Distancecolor = ImColor(255, 255, 255, 255);
	inline ImColor Weaponcolor = ImColor(255, 255, 255, 255);
	inline ImColor OOFarrowColor = ImColor(255, 255, 255, 255);

	//bars
	inline ImColor HealthbarMax = ImColor(14, 170, 255, 255);
	inline ImColor ArmourColor = ImColor(0, 128, 255, 255);
	inline ImColor AmmoColor = ImColor(255, 255, 0, 255);

	//misc
	inline bool bombtimer = true;
	inline ImColor bombtimercol = ImColor(255, 255, 255, 220);
	inline bool ShowCrossHair = false;
	inline bool Nightmode = false;
	inline bool Hitsound = true;
	inline bool Hitmarker = true;
	inline float HitmarkSize = 10.f;
	inline float HitmarkGap = 4.f;
	inline bool DamageText = true;

	inline bool Noflash = false;

	
	inline bool zeusRange = false;
	inline bool zeusTarget = false;
	inline ImColor zeusRangeColor = ImColor(255, 255, 255, 190);
	inline ImColor zeusTargetColor = ImColor(255, 255, 255, 190);

	inline float NightmodeBright = 120;
	inline float flashdur = 255.f;
	inline int hitsound_type = 0;

	inline unsigned int MovementInd = 27;
	inline ImColor GraphLineColor = ImColor(255, 255, 255, 255);

	//bombtimer
	inline bool bmbTimer = true;
	inline bool PlantedBombIco = true;

	inline bool SpecList = true;

	inline bool VelocityIndicator = true;
	inline bool MaxVelocity = true;
	inline bool VelocityGraph = true;
	inline bool KeyStrokes = true;
	inline int KeystrokeStyle = 1;

	inline bool SlowedIndicator = false;
	inline bool SpreadCircle = false;

	inline ImColor SpreadCircleColor = ImColor(9, 118, 178, 150);
	inline ImColor KeystrokeColor = ImColor(0, 255, 40, 255);


	inline bool LocalCheck = true;

	//menu
	inline bool untrusted = false;
	inline bool ShowMenu = true;
	inline bool ESPPreview = true;
	inline bool Keybindlist = false;
	inline int MenuStyle = 0;
	inline int ConfigName = 0;
	inline bool bombTimer = true;
	inline std::string SoundPath = "";

	inline bool adconf = false;//admin function really unprotected

	inline ImColor Accent = IM_COL32(17, 136, 240, 255);
	inline int styleee = 1;
	inline int selectedStyleIndex = 1;

	//watermark
	inline bool WaterMark = true;
	inline bool watermarkcheat = true;
	inline bool watermarkuser = true;
	inline bool watermarkfps = true;
	inline bool watermarktime = true;
	inline bool watermarkbuild = true;

	inline bool vsync = true;
	inline bool Debuglist = false;


}

namespace CrosshairConfig
{
	inline float CrossHairSize = 75;

	inline ImColor CrossHairColor = ImColor(0, 255, 0, 255);
	inline bool drawDot = true;

	inline bool tStyle = false;
	inline int HorizontalLength = 6;
	inline int VerticalLength = 6;
	inline bool drawOutLine = true;
	inline int Gap = 8;
	inline int Thickness = 1;
	inline float DotSize = 1.f;

	inline bool SniperOnly = false;
	inline bool RecoilCrosshair = false;
}


