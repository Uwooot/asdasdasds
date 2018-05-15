// Uwooot was here innit

#include "Visuals.h"
#include "Interfaces.h"
#include "RenderManager.h"

void CVisuals::Init() {}

void CVisuals::Move(CUserCmd *pCmd, bool &bSendPacket) {}

void CVisuals::Draw()
{
	IClientEntity* pLocal = hackManager.pLocal();

	if (Menu::Window.VisualsTab.OtherRecoilCrosshair.GetIndex() == 0)
	{
		//off
		Interfaces::Engine->ClientCmd_Unrestricted("crosshair 1");
	}

	if (Menu::Window.VisualsTab.OtherRecoilCrosshair.GetIndex() == 1)
	{	
		Interfaces::Engine->ClientCmd_Unrestricted("crosshair 0");
		DrawCrosshair();
	}

	if (Menu::Window.VisualsTab.OtherRecoilCrosshair.GetIndex() == 2)
	{
		Interfaces::Engine->ClientCmd_Unrestricted("crosshair 1");
		DrawRecoilCrosshair();
	}

	if (Menu::Window.VisualsTab.OtherRecoilCrosshair.GetIndex() == 3)
	{
		Interfaces::Engine->ClientCmd_Unrestricted("crosshair 1");
		DrawFOVCrosshair();
	}

	if (Menu::Window.VisualsTab.OtherRecoilCrosshair.GetIndex() == 4)
	{
		Interfaces::Engine->ClientCmd_Unrestricted("crosshair 0");
		DrawAnimatedCrosshair();
	}
}

void CVisuals::DrawCrosshair() {

	RECT View = Render::GetViewport();
	int MidX = View.right / 2;
	int MidY = View.bottom / 2;
	int SCS = Menu::Window.VisualsTab.StaticCrossSize.GetValue();

	Render::Line(MidX - (SCS + 1), MidY - (SCS + 1), MidX + (SCS + 1), MidY - (SCS + 1), Color(0, 0, 0, 255)); //top
	Render::Line(MidX + (SCS + 1), MidY + (SCS + 1), MidX - (SCS + 1), MidY + (SCS + 1), Color(0, 0, 0, 255)); //bottom
	Render::Line(MidX + (SCS + 1), MidY + (SCS + 1), MidX + (SCS + 1), MidY - (SCS + 1), Color(0, 0, 0, 255)); //right
	Render::Line(MidX - (SCS + 1), MidY - (SCS + 1), MidX - (SCS + 1), MidY + (SCS + 1), Color(0, 0, 0, 255)); //left

	Render::Line(MidX - SCS, MidY - SCS, MidX + SCS, MidY - SCS, Color(0, 255, 0, 255)); //top
	Render::Line(MidX + SCS, MidY + SCS, MidX - SCS, MidY + SCS, Color(0, 255, 0, 255)); //bottom
	Render::Line(MidX + SCS, MidY + SCS, MidX + SCS, MidY - SCS, Color(0, 255, 0, 255)); //right
	Render::Line(MidX - SCS, MidY - SCS, MidX - SCS, MidY + SCS, Color(0, 255, 0, 255)); //left

	Render::Line(MidX - (SCS - 1), MidY - (SCS - 1), MidX + (SCS - 1), MidY - (SCS - 1), Color(0, 0, 0, 255)); //top
	Render::Line(MidX + (SCS - 1), MidY + (SCS - 1), MidX - (SCS - 1), MidY + (SCS - 1), Color(0, 0, 0, 255)); //bottom
	Render::Line(MidX + (SCS - 1), MidY + (SCS - 1), MidX + (SCS - 1), MidY - (SCS - 1), Color(0, 0, 0, 255)); //right
	Render::Line(MidX - (SCS - 1), MidY - (SCS - 1), MidX - (SCS - 1), MidY + (SCS - 1), Color(0, 0, 0, 255)); //left

}

void CVisuals::DrawRecoilCrosshair() {

	IClientEntity *pLocal = hackManager.pLocal();

	Vector ViewAngles;
	Interfaces::Engine->GetViewAngles(ViewAngles);
	ViewAngles += pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

	Vector fowardVec;
	AngleVectors(ViewAngles, &fowardVec);
	fowardVec *= 10000;

	Vector start = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector end = start + fowardVec, endScreen;

	if (Render::WorldToScreen(end, endScreen) && pLocal->IsAlive())
	{
		int SCS = Menu::Window.VisualsTab.StaticCrossSize.GetValue();


		Render::Line(endScreen.x - (SCS + 1), (endScreen.y + 1) - (SCS + 1), endScreen.x + (SCS + 1), (endScreen.y + 1) - (SCS + 1), Color(0, 0, 0, 255)); //top
		Render::Line(endScreen.x + (SCS + 1), (endScreen.y + 1) + (SCS + 1), endScreen.x - (SCS + 1), (endScreen.y + 1) + (SCS + 1), Color(0, 0, 0, 255)); //bottom
		Render::Line(endScreen.x + (SCS + 1), (endScreen.y + 1) + (SCS + 1), endScreen.x + (SCS + 1), (endScreen.y + 1) - (SCS + 1), Color(0, 0, 0, 255)); //right
		Render::Line(endScreen.x - (SCS + 1), (endScreen.y + 1) - (SCS + 1), endScreen.x - (SCS + 1), (endScreen.y + 1) + (SCS + 1), Color(0, 0, 0, 255)); //left

		Render::Line(endScreen.x - SCS, (endScreen.y + 1) - SCS, endScreen.x + SCS, (endScreen.y + 1) - SCS, Color(0, 255, 0, 255)); //top
		Render::Line(endScreen.x + SCS, (endScreen.y + 1) + SCS, endScreen.x - SCS, (endScreen.y + 1) + SCS, Color(0, 255, 0, 255)); //bottom
		Render::Line(endScreen.x + SCS, (endScreen.y + 1) + SCS, endScreen.x + SCS, (endScreen.y + 1) - SCS, Color(0, 255, 0, 255)); //right
		Render::Line(endScreen.x - SCS, (endScreen.y + 1) - SCS, endScreen.x - SCS, (endScreen.y + 1) + SCS, Color(0, 255, 0, 255)); //left

		Render::Line(endScreen.x - (SCS - 1), (endScreen.y + 1) - (SCS - 1), endScreen.x + (SCS - 1), (endScreen.y + 1) - (SCS - 1), Color(0, 0, 0, 255)); //top
		Render::Line(endScreen.x + (SCS - 1), (endScreen.y + 1) + (SCS - 1), endScreen.x - (SCS - 1), (endScreen.y + 1) + (SCS - 1), Color(0, 0, 0, 255)); //bottom
		Render::Line(endScreen.x + (SCS - 1), (endScreen.y + 1) + (SCS - 1), endScreen.x + (SCS - 1), (endScreen.y + 1) - (SCS - 1), Color(0, 0, 0, 255)); //right
		Render::Line(endScreen.x - (SCS - 1), (endScreen.y + 1) - (SCS - 1), endScreen.x - (SCS - 1), (endScreen.y + 1) + (SCS - 1), Color(0, 0, 0, 255)); //left

	}
}

void CVisuals::DrawFOVCrosshair()
{

	float FoV;
	std::vector<int> HitBoxesToScan;
	IClientEntity* pLocal = hackManager.pLocal();
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	if (Menu::Window.LegitBotTab.Active.GetState())
	{
		if (!pWeapon)
			return;

		if (GameUtils::IsPistol(pWeapon))
		{
			FoV = (Menu::Window.PistolsTab.WeaponPistFoV.GetValue() * 2);

		}
		else if (GameUtils::IsSniper(pWeapon))
		{
			FoV = (Menu::Window.SnipersTab.WeaponSnipFoV.GetValue() * 2);

		}
		else
		{
			FoV = (Menu::Window.AutomaticsTab.WeaponMainFoV.GetValue() * 2);
		}
	}



	if (pLocal->IsScoped())
	{

	}

	else
	{

		Vector ViewAngles;
		Interfaces::Engine->GetViewAngles(ViewAngles);
		ViewAngles += pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

		Vector fowardVec;
		AngleVectors(ViewAngles, &fowardVec);
		fowardVec *= 1000;

		Vector start = pLocal->GetOrigin() + pLocal->GetViewOffset();
		Vector end = start + fowardVec, endScreen;

		if (Render::WorldToScreen(end, endScreen))
		{
			float zoomlvl = Menu::Window.VisualsTab.OtherFOV.GetValue() / 90;



			Render::DrawCircle(endScreen.x, endScreen.y, ((FoV  * 6.25) / zoomlvl) - 1, ((FoV  * 6.25) / zoomlvl) - 1, Color(0, 0, 0, 255));
			Render::DrawCircle(endScreen.x, endScreen.y, ((FoV  * 6.25) / zoomlvl), ((FoV  * 6.25) / zoomlvl), Color(0, 255, 0, 255));
			Render::DrawCircle(endScreen.x, endScreen.y, ((FoV  * 6.25) / zoomlvl) + 1, ((FoV  * 6.25) / zoomlvl) + 1, Color(0, 0, 0, 255));
		}
	}
}

void CVisuals::DrawAnimatedCrosshair() 
{


	{	
		RECT View = Render::GetViewport();
		int MidX = View.right / 2;
		int MidY = View.bottom / 2;
		static int counter = 0;
		static int motion = 0;
		int animspeed = (Menu::Window.VisualsTab.AnimCrossSpeed.GetValue());
		int ServerTime = (float)Interfaces::Globals->interval_per_tick * hackManager.pLocal()->GetTickBase() * animspeed;

		if (counter % 48 == 0)
			motion++;
		int value = ServerTime % 24;
		switch (value) {
		
		case 0:
		{
			Render::Line(MidX - 18, MidY - 18, MidX + 18, MidY - 18, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 18, MidY + 18, MidX - 18, MidY + 18, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 18, MidY + 18, MidX + 18, MidY - 18, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 18, MidY - 18, MidX - 18, MidY + 18, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 17, MidY - 17, MidX + 17, MidY - 17, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 17, MidY + 17, MidX - 17, MidY + 17, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 17, MidY + 17, MidX + 17, MidY - 17, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 17, MidY - 17, MidX - 17, MidY + 17, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 16, MidY - 16, MidX + 16, MidY - 16, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 16, MidY + 16, MidX - 16, MidY + 16, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 16, MidY + 16, MidX + 16, MidY - 16, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 16, MidY - 16, MidX - 16, MidY + 16, Color(0, 0, 0, 255)); //left
		}
			break;
		
		case 1:
		{
			Render::Line(MidX - 17, MidY - 17, MidX + 17, MidY - 17, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 17, MidY + 17, MidX - 17, MidY + 17, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 17, MidY + 17, MidX + 17, MidY - 17, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 17, MidY - 17, MidX - 17, MidY + 17, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 16, MidY - 16, MidX + 16, MidY - 16, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 16, MidY + 16, MidX - 16, MidY + 16, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 16, MidY + 16, MidX + 16, MidY - 16, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 16, MidY - 16, MidX - 16, MidY + 16, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 15, MidY - 15, MidX + 15, MidY - 15, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 15, MidY + 15, MidX - 15, MidY + 15, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 15, MidY + 15, MidX + 15, MidY - 15, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 15, MidY - 15, MidX - 15, MidY + 15, Color(0, 0, 0, 255)); //left
		}
			break;

		case 2:
		{
			Render::Line(MidX - 16, MidY - 16, MidX + 16, MidY - 16, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 16, MidY + 16, MidX - 16, MidY + 16, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 16, MidY + 16, MidX + 16, MidY - 16, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 16, MidY - 16, MidX - 16, MidY + 16, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 15, MidY - 15, MidX + 15, MidY - 15, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 15, MidY + 15, MidX - 15, MidY + 15, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 15, MidY + 15, MidX + 15, MidY - 15, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 15, MidY - 15, MidX - 15, MidY + 15, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 14, MidY - 14, MidX + 14, MidY - 14, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 14, MidY + 14, MidX - 14, MidY + 14, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 14, MidY + 14, MidX + 14, MidY - 14, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 14, MidY - 14, MidX - 14, MidY + 14, Color(0, 0, 0, 255)); //left
		}
			break;

		case 3:
		{
			Render::Line(MidX - 15, MidY - 15, MidX + 15, MidY - 15, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 15, MidY + 15, MidX - 15, MidY + 15, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 15, MidY + 15, MidX + 15, MidY - 15, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 15, MidY - 15, MidX - 15, MidY + 15, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 14, MidY - 14, MidX + 14, MidY - 14, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 14, MidY + 14, MidX - 14, MidY + 14, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 14, MidY + 14, MidX + 14, MidY - 14, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 14, MidY - 14, MidX - 14, MidY + 14, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 13, MidY - 13, MidX + 13, MidY - 13, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 13, MidY + 13, MidX - 13, MidY + 13, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 13, MidY + 13, MidX + 13, MidY - 13, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 13, MidY - 13, MidX - 13, MidY + 13, Color(0, 0, 0, 255)); //left
		}
			break;

		case 4:
		{
			Render::Line(MidX - 14, MidY - 14, MidX + 14, MidY - 14, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 14, MidY + 14, MidX - 14, MidY + 14, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 14, MidY + 14, MidX + 14, MidY - 14, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 14, MidY - 14, MidX - 14, MidY + 14, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 13, MidY - 13, MidX + 13, MidY - 13, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 13, MidY + 13, MidX - 13, MidY + 13, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 13, MidY + 13, MidX + 13, MidY - 13, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 13, MidY - 13, MidX - 13, MidY + 13, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 12, MidY - 12, MidX + 12, MidY - 12, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 12, MidY + 12, MidX - 12, MidY + 12, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 12, MidY + 12, MidX + 12, MidY - 12, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 12, MidY - 12, MidX - 12, MidY + 12, Color(0, 0, 0, 255)); //left
		}
		break;

		case 5:
		{
			Render::Line(MidX - 13, MidY - 13, MidX + 13, MidY - 13, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 13, MidY + 13, MidX - 13, MidY + 13, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 13, MidY + 13, MidX + 13, MidY - 13, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 13, MidY - 13, MidX - 13, MidY + 13, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 12, MidY - 12, MidX + 12, MidY - 12, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 12, MidY + 12, MidX - 12, MidY + 12, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 12, MidY + 12, MidX + 12, MidY - 12, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 12, MidY - 12, MidX - 12, MidY + 12, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 11, MidY - 11, MidX + 11, MidY - 11, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 11, MidY + 11, MidX - 11, MidY + 11, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 11, MidY + 11, MidX + 11, MidY - 11, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 11, MidY - 11, MidX - 11, MidY + 11, Color(0, 0, 0, 255)); //left
		}
		break;

		case 6:
		{
			Render::Line(MidX - 12, MidY - 12, MidX + 12, MidY - 12, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 12, MidY + 12, MidX - 12, MidY + 12, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 12, MidY + 12, MidX + 12, MidY - 12, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 12, MidY - 12, MidX - 12, MidY + 12, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 11, MidY - 11, MidX + 11, MidY - 11, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 11, MidY + 11, MidX - 11, MidY + 11, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 11, MidY + 11, MidX + 11, MidY - 11, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 11, MidY - 11, MidX - 11, MidY + 11, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 10, MidY - 10, MidX + 10, MidY - 10, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 10, MidY + 10, MidX - 10, MidY + 10, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 10, MidY + 10, MidX + 10, MidY - 10, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 10, MidY - 10, MidX - 10, MidY + 10, Color(0, 0, 0, 255)); //left
		}
		break;

		case 7:
		{
			Render::Line(MidX - 11, MidY - 11, MidX + 11, MidY - 11, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 11, MidY + 11, MidX - 11, MidY + 11, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 11, MidY + 11, MidX + 11, MidY - 11, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 11, MidY - 11, MidX - 11, MidY + 11, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 10, MidY - 10, MidX + 10, MidY - 10, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 10, MidY + 10, MidX - 10, MidY + 10, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 10, MidY + 10, MidX + 10, MidY - 10, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 10, MidY - 10, MidX - 10, MidY + 10, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 9, MidY - 9, MidX + 9, MidY - 9, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 9, MidY + 9, MidX - 9, MidY + 9, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 9, MidY + 9, MidX + 9, MidY - 9, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 9, MidY - 9, MidX - 9, MidY + 9, Color(0, 0, 0, 255)); //left
		}
		break;

		case 8:
		{
			Render::Line(MidX - 10, MidY - 10, MidX + 10, MidY - 10, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 10, MidY + 10, MidX - 10, MidY + 10, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 10, MidY + 10, MidX + 10, MidY - 10, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 10, MidY - 10, MidX - 10, MidY + 10, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 9, MidY - 9, MidX + 9, MidY - 9, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 9, MidY + 9, MidX - 9, MidY + 9, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 9, MidY + 9, MidX + 9, MidY - 9, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 9, MidY - 9, MidX - 9, MidY + 9, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 8, MidY - 8, MidX + 8, MidY - 8, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 8, MidY + 8, MidX - 8, MidY + 8, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 8, MidY + 8, MidX + 8, MidY - 8, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 8, MidY - 8, MidX - 8, MidY + 8, Color(0, 0, 0, 255)); //left
		}
		break;

		case 9:
		{
			Render::Line(MidX - 9, MidY - 9, MidX + 9, MidY - 9, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 9, MidY + 9, MidX - 9, MidY + 9, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 9, MidY + 9, MidX + 9, MidY - 9, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 9, MidY - 9, MidX - 9, MidY + 9, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 8, MidY - 8, MidX + 8, MidY - 8, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 8, MidY + 8, MidX - 8, MidY + 8, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 8, MidY + 8, MidX + 8, MidY - 8, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 8, MidY - 8, MidX - 8, MidY + 8, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 7, MidY - 7, MidX + 7, MidY - 7, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 7, MidY + 7, MidX - 7, MidY + 7, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 7, MidY + 7, MidX + 7, MidY - 7, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 7, MidY - 7, MidX - 7, MidY + 7, Color(0, 0, 0, 255)); //left
		}
		break;

		case 10:
		{
			Render::Line(MidX - 8, MidY - 8, MidX + 8, MidY - 8, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 8, MidY + 8, MidX - 8, MidY + 8, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 8, MidY + 8, MidX + 8, MidY - 8, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 8, MidY - 8, MidX - 8, MidY + 8, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 7, MidY - 7, MidX + 7, MidY - 7, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 7, MidY + 7, MidX - 7, MidY + 7, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 7, MidY + 7, MidX + 7, MidY - 7, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 7, MidY - 7, MidX - 7, MidY + 7, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 6, MidY - 6, MidX + 6, MidY - 6, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 6, MidY + 6, MidX - 6, MidY + 6, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 6, MidY + 6, MidX + 6, MidY - 6, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 6, MidY - 6, MidX - 6, MidY + 6, Color(0, 0, 0, 255)); //left
		}
		break;

		case 11:
		{
			Render::Line(MidX - 7, MidY - 7, MidX + 7, MidY - 7, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 7, MidY + 7, MidX - 7, MidY + 7, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 7, MidY + 7, MidX + 7, MidY - 7, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 7, MidY - 7, MidX - 7, MidY + 7, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 6, MidY - 6, MidX + 6, MidY - 6, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 6, MidY + 6, MidX - 6, MidY + 6, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 6, MidY + 6, MidX + 6, MidY - 6, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 6, MidY - 6, MidX - 6, MidY + 6, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 5, MidY - 5, MidX + 5, MidY - 5, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 5, MidY + 5, MidX - 5, MidY + 5, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 5, MidY + 5, MidX + 5, MidY - 5, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 5, MidY - 5, MidX - 5, MidY + 5, Color(0, 0, 0, 255)); //left
		}
		break;

		case 12:
		{
			Render::Line(MidX - 6, MidY - 6, MidX + 6, MidY - 6, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 6, MidY + 6, MidX - 6, MidY + 6, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 6, MidY + 6, MidX + 6, MidY - 6, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 6, MidY - 6, MidX - 6, MidY + 6, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 5, MidY - 5, MidX + 5, MidY - 5, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 5, MidY + 5, MidX - 5, MidY + 5, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 5, MidY + 5, MidX + 5, MidY - 5, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 5, MidY - 5, MidX - 5, MidY + 5, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 4, MidY - 4, MidX + 4, MidY - 4, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 4, MidY + 4, MidX - 4, MidY + 4, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 4, MidY + 4, MidX + 4, MidY - 4, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 4, MidY - 4, MidX - 4, MidY + 4, Color(0, 0, 0, 255)); //left
		}
		break;

		case 13:
		{
			Render::Line(MidX - 7, MidY - 7, MidX + 7, MidY - 7, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 7, MidY + 7, MidX - 7, MidY + 7, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 7, MidY + 7, MidX + 7, MidY - 7, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 7, MidY - 7, MidX - 7, MidY + 7, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 6, MidY - 6, MidX + 6, MidY - 6, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 6, MidY + 6, MidX - 6, MidY + 6, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 6, MidY + 6, MidX + 6, MidY - 6, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 6, MidY - 6, MidX - 6, MidY + 6, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 5, MidY - 5, MidX + 5, MidY - 5, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 5, MidY + 5, MidX - 5, MidY + 5, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 5, MidY + 5, MidX + 5, MidY - 5, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 5, MidY - 5, MidX - 5, MidY + 5, Color(0, 0, 0, 255)); //left
		}
		break;

		case 14:
		{
			Render::Line(MidX - 8, MidY - 8, MidX + 8, MidY - 8, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 8, MidY + 8, MidX - 8, MidY + 8, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 8, MidY + 8, MidX + 8, MidY - 8, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 8, MidY - 8, MidX - 8, MidY + 8, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 7, MidY - 7, MidX + 7, MidY - 7, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 7, MidY + 7, MidX - 7, MidY + 7, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 7, MidY + 7, MidX + 7, MidY - 7, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 7, MidY - 7, MidX - 7, MidY + 7, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 6, MidY - 6, MidX + 6, MidY - 6, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 6, MidY + 6, MidX - 6, MidY + 6, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 6, MidY + 6, MidX + 6, MidY - 6, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 6, MidY - 6, MidX - 6, MidY + 6, Color(0, 0, 0, 255)); //left
		}
		break;

		case 15:
		{
			Render::Line(MidX - 9, MidY - 9, MidX + 9, MidY - 9, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 9, MidY + 9, MidX - 9, MidY + 9, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 9, MidY + 9, MidX + 9, MidY - 9, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 9, MidY - 9, MidX - 9, MidY + 9, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 8, MidY - 8, MidX + 8, MidY - 8, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 8, MidY + 8, MidX - 8, MidY + 8, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 8, MidY + 8, MidX + 8, MidY - 8, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 8, MidY - 8, MidX - 8, MidY + 8, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 7, MidY - 7, MidX + 7, MidY - 7, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 7, MidY + 7, MidX - 7, MidY + 7, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 7, MidY + 7, MidX + 7, MidY - 7, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 7, MidY - 7, MidX - 7, MidY + 7, Color(0, 0, 0, 255)); //left
		}
		break;

		case 16:
		{
			Render::Line(MidX - 10, MidY - 10, MidX + 10, MidY - 10, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 10, MidY + 10, MidX - 10, MidY + 10, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 10, MidY + 10, MidX + 10, MidY - 10, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 10, MidY - 10, MidX - 10, MidY + 10, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 9, MidY - 9, MidX + 9, MidY - 9, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 9, MidY + 9, MidX - 9, MidY + 9, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 9, MidY + 9, MidX + 9, MidY - 9, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 9, MidY - 9, MidX - 9, MidY + 9, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 8, MidY - 8, MidX + 8, MidY - 8, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 8, MidY + 8, MidX - 8, MidY + 8, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 8, MidY + 8, MidX + 8, MidY - 8, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 8, MidY - 8, MidX - 8, MidY + 8, Color(0, 0, 0, 255)); //left
		}
		break;

		case 17:
		{
			Render::Line(MidX - 11, MidY - 11, MidX + 11, MidY - 11, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 11, MidY + 11, MidX - 11, MidY + 11, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 11, MidY + 11, MidX + 11, MidY - 11, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 11, MidY - 11, MidX - 11, MidY + 11, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 10, MidY - 10, MidX + 10, MidY - 10, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 10, MidY + 10, MidX - 10, MidY + 10, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 10, MidY + 10, MidX + 10, MidY - 10, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 10, MidY - 10, MidX - 10, MidY + 10, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 9, MidY - 9, MidX + 9, MidY - 9, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 9, MidY + 9, MidX - 9, MidY + 9, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 9, MidY + 9, MidX + 9, MidY - 9, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 9, MidY - 9, MidX - 9, MidY + 9, Color(0, 0, 0, 255)); //left
		}
		break;

		case 18:
		{
			Render::Line(MidX - 12, MidY - 12, MidX + 12, MidY - 12, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 12, MidY + 12, MidX - 12, MidY + 12, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 12, MidY + 12, MidX + 12, MidY - 12, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 12, MidY - 12, MidX - 12, MidY + 12, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 11, MidY - 11, MidX + 11, MidY - 11, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 11, MidY + 11, MidX - 11, MidY + 11, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 11, MidY + 11, MidX + 11, MidY - 11, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 11, MidY - 11, MidX - 11, MidY + 11, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 10, MidY - 10, MidX + 10, MidY - 10, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 10, MidY + 10, MidX - 10, MidY + 10, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 10, MidY + 10, MidX + 10, MidY - 10, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 10, MidY - 10, MidX - 10, MidY + 10, Color(0, 0, 0, 255)); //left
		}
		break;

		case 19:
		{
			Render::Line(MidX - 13, MidY - 13, MidX + 13, MidY - 13, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 13, MidY + 13, MidX - 13, MidY + 13, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 13, MidY + 13, MidX + 13, MidY - 13, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 13, MidY - 13, MidX - 13, MidY + 13, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 12, MidY - 12, MidX + 12, MidY - 12, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 12, MidY + 12, MidX - 12, MidY + 12, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 12, MidY + 12, MidX + 12, MidY - 12, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 12, MidY - 12, MidX - 12, MidY + 12, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 11, MidY - 11, MidX + 11, MidY - 11, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 11, MidY + 11, MidX - 11, MidY + 11, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 11, MidY + 11, MidX + 11, MidY - 11, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 11, MidY - 11, MidX - 11, MidY + 11, Color(0, 0, 0, 255)); //left
		}
		break;

		case 20:
		{
			Render::Line(MidX - 14, MidY - 14, MidX + 14, MidY - 14, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 14, MidY + 14, MidX - 14, MidY + 14, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 14, MidY + 14, MidX + 14, MidY - 14, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 14, MidY - 14, MidX - 14, MidY + 14, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 13, MidY - 13, MidX + 13, MidY - 13, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 13, MidY + 13, MidX - 13, MidY + 13, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 13, MidY + 13, MidX + 13, MidY - 13, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 13, MidY - 13, MidX - 13, MidY + 13, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 12, MidY - 12, MidX + 12, MidY - 12, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 12, MidY + 12, MidX - 12, MidY + 12, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 12, MidY + 12, MidX + 12, MidY - 12, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 12, MidY - 12, MidX - 12, MidY + 12, Color(0, 0, 0, 255)); //left
		}
		break;

		case 21:
		{
			Render::Line(MidX - 15, MidY - 15, MidX + 15, MidY - 15, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 15, MidY + 15, MidX - 15, MidY + 15, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 15, MidY + 15, MidX + 15, MidY - 15, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 15, MidY - 15, MidX - 15, MidY + 15, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 14, MidY - 14, MidX + 14, MidY - 14, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 14, MidY + 14, MidX - 14, MidY + 14, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 14, MidY + 14, MidX + 14, MidY - 14, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 14, MidY - 14, MidX - 14, MidY + 14, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 13, MidY - 13, MidX + 13, MidY - 13, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 13, MidY + 13, MidX - 13, MidY + 13, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 13, MidY + 13, MidX + 13, MidY - 13, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 13, MidY - 13, MidX - 13, MidY + 13, Color(0, 0, 0, 255)); //left
		}
		break;

		case 22:
		{
			Render::Line(MidX - 16, MidY - 16, MidX + 16, MidY - 16, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 16, MidY + 16, MidX - 16, MidY + 16, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 16, MidY + 16, MidX + 16, MidY - 16, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 16, MidY - 16, MidX - 16, MidY + 16, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 15, MidY - 15, MidX + 15, MidY - 15, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 15, MidY + 15, MidX - 15, MidY + 15, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 15, MidY + 15, MidX + 15, MidY - 15, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 15, MidY - 15, MidX - 15, MidY + 15, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 14, MidY - 14, MidX + 14, MidY - 14, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 14, MidY + 14, MidX - 14, MidY + 14, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 14, MidY + 14, MidX + 14, MidY - 14, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 14, MidY - 14, MidX - 14, MidY + 14, Color(0, 0, 0, 255)); //left
		}
		break;

		case 23:
		{
			Render::Line(MidX - 17, MidY - 17, MidX + 17, MidY - 17, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 17, MidY + 17, MidX - 17, MidY + 17, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 17, MidY + 17, MidX + 17, MidY - 17, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 17, MidY - 17, MidX - 17, MidY + 17, Color(0, 0, 0, 255)); //left

			Render::Line(MidX - 16, MidY - 16, MidX + 16, MidY - 16, Color(0, 255, 0, 255)); //top
			Render::Line(MidX + 16, MidY + 16, MidX - 16, MidY + 16, Color(0, 255, 0, 255)); //bottom
			Render::Line(MidX + 16, MidY + 16, MidX + 16, MidY - 16, Color(0, 255, 0, 255)); //right
			Render::Line(MidX - 16, MidY - 16, MidX - 16, MidY + 16, Color(0, 255, 0, 255)); //left

			Render::Line(MidX - 15, MidY - 15, MidX + 15, MidY - 15, Color(0, 0, 0, 255)); //top
			Render::Line(MidX + 15, MidY + 15, MidX - 15, MidY + 15, Color(0, 0, 0, 255)); //bottom
			Render::Line(MidX + 15, MidY + 15, MidX + 15, MidY - 15, Color(0, 0, 0, 255)); //right
			Render::Line(MidX - 15, MidY - 15, MidX - 15, MidY + 15, Color(0, 0, 0, 255)); //left
		}
		break;

		}
		counter++;
	}

}