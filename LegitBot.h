/*
Syn's AyyWare Framework 2015
*/

#pragma once

#include "Hacks.h"

class CLegitBot : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:
	// Targetting
	int GetTargetCrosshair();
	bool TargetMeetsRequirements(IClientEntity* pEntity);
	float FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity* pEntity, int HitBox);
//	int HitScan(IClientEntity* pEntity);
	bool AimAtPoint(IClientEntity* pLocal, Vector point, CUserCmd *pCmd, bool &bSendPacket);

	void SyncWeaponSettings();

	// Functionality
	void DoAimbot(CUserCmd *pCmd, bool &bSendpacket);
	void DoDelay(CUserCmd *pCmd, bool &bSendPacket);
	void CLegitBot::AutoPistol(CUserCmd *pCmd, IClientEntity *pLocal);
	// Aimbot
	bool IsLocked;
	int TargetID;
	int HitBox;
	Vector AimPoint;

	float Speed;
	float FoV;
	bool RecoilControl;
	float RecoilControlVal;
	bool PSilent;
	float Inacc;
	float RcsSmooth;
	float RcsRand;
};

