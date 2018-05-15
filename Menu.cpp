#include "Menu.h"
#include "Controls.h"
#include "Hooks.h" // for the unload meme
#include "Interfaces.h"
#include "CRC32.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300

AyyWareWindow Menu::Window;

void SaveLegitCallbk()
{
	switch (Menu::Window.MiscTab.lstPlayers.GetIndex())
	{
	case 0:
		GUI.SaveWindowState(&Menu::Window, "SkillSimulatorLegit1.cfg");
		break;
	case 1:
		GUI.SaveWindowState(&Menu::Window, "SkillSimulatorLegit2.cfg");
		break;
	case 2:
		GUI.SaveWindowState(&Menu::Window, "SkillSimulatorLegit3.cfg");
		break;
	case 3:
		GUI.SaveWindowState(&Menu::Window, "SkillSimulatorRage1.cfg");
		break;
	case 4:
		GUI.SaveWindowState(&Menu::Window, "SkillSimulatorRage2.cfg");
		break;
	case 5:
		GUI.SaveWindowState(&Menu::Window, "SkillSimulatorRage3.cfg");
		break;

	}
}

void LoadLegitCallbk()
{
	static ConVar* Meme = Interfaces::CVar->FindVar("cl_fullupdate");
	Interfaces::Engine->ClientCmd_Unrestricted("cl_fullupdate");

	switch (Menu::Window.MiscTab.lstPlayers.GetIndex())
	{
	case 0:
		GUI.LoadWindowState(&Menu::Window, "SkillSimulatorLegit1.cfg");
	
		break;
	case 1:
		GUI.LoadWindowState(&Menu::Window, "SkillSimulatorLegit2.cfg");
	
		break;
	case 2:
		GUI.LoadWindowState(&Menu::Window, "SkillSimulatorLegit3.cfg");
	
		break;
	case 3:
		GUI.LoadWindowState(&Menu::Window, "SkillSimulatorRage1.cfg");
		
		break;
	case 4:
		GUI.LoadWindowState(&Menu::Window, "SkillSimulatorRage2.cfg");
	
		break;
	case 5:
		GUI.LoadWindowState(&Menu::Window, "SkillSimulatorRage3.cfg");
	
		break;
	}
}

void UnLoadCallbk()
{
	DoUnload = true;
}

void KnifeApplyCallbk()
{
	static ConVar* Meme = Interfaces::CVar->FindVar("cl_fullupdate");
	Meme->nFlags &= ~FCVAR_CHEAT;
	Interfaces::Engine->ClientCmd_Unrestricted("cl_fullupdate");
}

void AyyWareWindow::Setup()
{
	SetPosition(300, 50);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//SetTitle("                                                    Skill Simulator");
	SetTitle("Compile date: 01.04.2018 11:43 PM                                            Skill Simulator");

	RegisterTab(&LegitBotTab);
	RegisterTab(&AutomaticsTab);
	RegisterTab(&PistolsTab);
	RegisterTab(&SnipersTab);
	RegisterTab(&VisualsTab);
	RegisterTab(&MiscTab);

	RECT Client = GetClientArea();
	Client.bottom -= 29;

	LegitBotTab.Setup();
	AutomaticsTab.Setup();
	PistolsTab.Setup();
	SnipersTab.Setup();
	VisualsTab.Setup();
	MiscTab.Setup();

#pragma region Bottom Buttons
	SaveButton3.SetText("Save");
	SaveButton3.SetCallback(SaveLegitCallbk);
	SaveButton3.SetPosition(230, 200);

	LoadButton3.SetText("Load");
	LoadButton3.SetCallback(LoadLegitCallbk);
	LoadButton3.SetPosition(270, 200);

	MiscTab.RegisterControl(&SaveButton3);
	MiscTab.RegisterControl(&LoadButton3);
#pragma endregion Setting up the settings buttons
}

void CLegitBotTab::Setup()
{
	SetTitle("Aim");

	ActiveLabel.SetPosition(1, 1);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetState(true);
	Active.SetPosition(41, 1);
	RegisterControl(&Active);

#pragma region Aimbot
	AimbotGroup.SetPosition(10, 10);
	AimbotGroup.SetText("Aimbot");
	AimbotGroup.SetSize(280, 250);
	RegisterControl(&AimbotGroup);

	AimbotEnable.SetFileId("aim_enable");
	AimbotEnable.SetState(true);
	AimbotGroup.PlaceLabledControl("Enable", this, &AimbotEnable);

	AimbotKeyPress.SetFileId("aim_usekey");
	AimbotKeyPress.SetState(true);
	AimbotGroup.PlaceLabledControl("On Key", this, &AimbotKeyPress);

	AimbotKeyBind.SetFileId("aim_key");
	AimbotKeyBind.SetKey(1);
	AimbotGroup.PlaceLabledControl("Key Bind", this, &AimbotKeyBind);
	
	AimbotAutoPistol.SetFileId("aim_apistol");
	AimbotGroup.PlaceLabledControl("Auto Pistol", this, &AimbotAutoPistol);

	AimbotBacktrack.SetFileId("legit_backtrack");
	AimbotBacktrack.SetState(true);
	AimbotGroup.PlaceLabledControl("Backtrack", this, &AimbotBacktrack);

	TickModulation.SetFileId("tick_modulate");
	TickModulation.SetBoundaries(1.f, 13.f);
	TickModulation.SetValue(13.f);
	AimbotGroup.PlaceLabledControl("Backtrack Ticks", this, &TickModulation);

#pragma endregion Aimbot shit
}

void CAutomaticsTab::Setup()
{
	SetTitle("Rifles");

#pragma region Main Weapon
	WeaponMainGroup.SetPosition(10, 10);
	WeaponMainGroup.SetText("Rifles/Other");
	WeaponMainGroup.SetSize(240, 210);
	RegisterControl(&WeaponMainGroup);

	WeaponMainSpeed.SetFileId("main_speed");
	WeaponMainSpeed.SetBoundaries(0.1f, 100.f);
	WeaponMainSpeed.SetValue(85.f);
	WeaponMainGroup.PlaceLabledControl("Smooth", this, &WeaponMainSpeed);

	WeaponMainFoV.SetFileId("main_fov");
	WeaponMainFoV.SetBoundaries(0.1f, 30.f);
	WeaponMainFoV.SetValue(5.f);
	WeaponMainGroup.PlaceLabledControl("Main FoV", this, &WeaponMainFoV);

	StopAimTimeMain.SetFileId("main_stopaim");
	StopAimTimeMain.SetBoundaries(0.f, 5.f);
	StopAimTimeMain.SetValue(2.f);
	WeaponMainGroup.PlaceLabledControl("Main Humanise", this, &StopAimTimeMain);

	WeaponMainRecoilVal.SetFileId("main_recoil");
	WeaponMainRecoilVal.SetBoundaries(0.f, 100.f);
	WeaponMainRecoilVal.SetValue(100.f);
	WeaponMainGroup.PlaceLabledControl("Main Recoil", this, &WeaponMainRecoilVal);

	RcsSmoothMain.SetFileId("rcs_smoothmain");
	RcsSmoothMain.SetBoundaries(0.f, 10.f);
	RcsSmoothMain.SetValue(4.f);
	WeaponMainGroup.PlaceLabledControl("Recoil Smooth", this, &RcsSmoothMain);

	RcsRandMain.SetFileId("rcs_Randmain");
	RcsRandMain.SetBoundaries(0.f, 5.f);
	RcsRandMain.SetValue(4.f);
	WeaponMainGroup.PlaceLabledControl("Recoil Rand", this, &RcsRandMain);

	WeaponMainPSilent.SetFileId("main_psilent");
	WeaponMainGroup.PlaceLabledControl("Silent", this, &WeaponMainPSilent);

	WeaponMainHitbox.SetFileId("main_hitbox");
	WeaponMainHitbox.AddItem("Head");
	WeaponMainHitbox.AddItem("Neck");
	WeaponMainHitbox.AddItem("Chest");
	WeaponMainHitbox.AddItem("Stomach");
	WeaponMainGroup.PlaceLabledControl("Hitbox", this, &WeaponMainHitbox);
#pragma endregion

}

void CPistolsTab::Setup()
{
	SetTitle("Pistols");

#pragma region Pistols
	WeaponPistGroup.SetPosition(10, 10);
	WeaponPistGroup.SetText("Pistols");
	WeaponPistGroup.SetSize(240, 210);
	RegisterControl(&WeaponPistGroup);

	WeaponPistSpeed.SetFileId("Pist_speed");
	WeaponPistSpeed.SetBoundaries(0.1f, 100.f);
	WeaponPistSpeed.SetValue(50.f);
	WeaponPistGroup.PlaceLabledControl("Smooth", this, &WeaponPistSpeed);

	WeaponPistFoV.SetFileId("Pist_fov");
	WeaponPistFoV.SetBoundaries(0.1f, 30.f);
	WeaponPistFoV.SetValue(5.f);
	WeaponPistGroup.PlaceLabledControl("Pist FoV", this, &WeaponPistFoV);

	StopAimTimePist.SetFileId("pist_stopaim");
	StopAimTimePist.SetBoundaries(0.f, 5.f);
	StopAimTimePist.SetValue(0.f);
	//	WeaponPistGroup.PlaceLabledControl("Pist Humanise", this, &StopAimTimePist);

	WeaponPistRecoilVal.SetFileId("Pist_recoil");
	WeaponPistRecoilVal.SetBoundaries(0.f, 100.f);
	WeaponPistRecoilVal.SetValue(0.f);
	WeaponPistGroup.PlaceLabledControl("Pist Recoil", this, &WeaponPistRecoilVal);

	RcsSmoothPistols.SetFileId("rcs_smoothPist");
	RcsSmoothPistols.SetBoundaries(0.f, 10.f);
	RcsSmoothPistols.SetValue(4.f);
	WeaponPistGroup.PlaceLabledControl("Recoil Smooth", this, &RcsSmoothPistols);

	RcsRandPistols.SetFileId("rcs_RandPist");
	RcsRandPistols.SetBoundaries(0.f, 5.f);
	RcsRandPistols.SetValue(0.f);
	WeaponPistGroup.PlaceLabledControl("Recoil Rand", this, &RcsRandPistols);

	WeaponPistPSilent.SetFileId("Pist_psilent");
	WeaponPistGroup.PlaceLabledControl("Silent", this, &WeaponPistPSilent);

	WeaponPistShotDelay.SetFileId("shotdelaypist");
	WeaponPistShotDelay.SetState(true);
	WeaponPistGroup.PlaceLabledControl("Shot Delay", this, &WeaponPistShotDelay);

	WeaponPistHitbox.SetFileId("Pist_hitbox");
	WeaponPistHitbox.AddItem("Head");
	WeaponPistHitbox.AddItem("Neck");
	WeaponPistHitbox.AddItem("Chest");
	WeaponPistHitbox.AddItem("Stomach");
	WeaponPistGroup.PlaceLabledControl("Hitbox", this, &WeaponPistHitbox);
#pragma endregion

}

void CSnipersTab::Setup()
{
	SetTitle("Snipers");

#pragma region Snipers
	WeaponSnipGroup.SetPosition(10, 10);
	WeaponSnipGroup.SetText("Snipers");
	WeaponSnipGroup.SetSize(240, 210);
	RegisterControl(&WeaponSnipGroup);

	WeaponSnipSpeed.SetFileId("Snip_speed");
	WeaponSnipSpeed.SetBoundaries(0.1f, 100.f);
	WeaponSnipSpeed.SetValue(50.f);
	WeaponSnipGroup.PlaceLabledControl("Smooth", this, &WeaponSnipSpeed);

	WeaponSnipFoV.SetFileId("Snip_fov");
	WeaponSnipFoV.SetBoundaries(0.1f, 30.f);
	WeaponSnipFoV.SetValue(13.f);
	WeaponSnipGroup.PlaceLabledControl("Snip FoV", this, &WeaponSnipFoV);

	StopAimTimeSnip.SetFileId("Snip_stopaim");
	StopAimTimeSnip.SetBoundaries(0.f, 5.f);
	StopAimTimeSnip.SetValue(0.f);
	//	WeaponSnipGroup.PlaceLabledControl("Snip Humanise", this, &StopAimTimeSnip);

	WeaponSnipRecoilVal.SetFileId("Snip_recoil");
	WeaponSnipRecoilVal.SetBoundaries(0.f, 100.f);
	WeaponSnipRecoilVal.SetValue(0.f);
	WeaponSnipGroup.PlaceLabledControl("Snip Recoil", this, &WeaponSnipRecoilVal);

	RcsSmoothSnipers.SetFileId("rcs_smoothSnip");
	RcsSmoothSnipers.SetBoundaries(0.f, 10.f);
	RcsSmoothSnipers.SetValue(4.f);
	WeaponSnipGroup.PlaceLabledControl("Recoil Smooth", this, &RcsSmoothSnipers);

	RcsRandSnipers.SetFileId("rcs_RandSnip");
	RcsRandSnipers.SetBoundaries(0.f, 5.f);
	RcsRandSnipers.SetValue(0.f);
	WeaponSnipGroup.PlaceLabledControl("Recoil Rand", this, &RcsRandSnipers);

	WeaponSnipPSilent.SetFileId("Snip_psilent");
	WeaponSnipGroup.PlaceLabledControl("Silent", this, &WeaponSnipPSilent);

	WeaponSnipShotDelay.SetFileId("shotdelaysnip");
	WeaponSnipShotDelay.SetState(true);
	WeaponSnipGroup.PlaceLabledControl("Shot Delay", this, &WeaponSnipShotDelay);

	WeaponSnipHitbox.SetFileId("Snip_hitbox");
	WeaponSnipHitbox.AddItem("Head");
	WeaponSnipHitbox.AddItem("Neck");
	WeaponSnipHitbox.AddItem("Chest");
	WeaponSnipHitbox.AddItem("Stomach");
	WeaponSnipHitbox.SelectIndex(3);
	WeaponSnipGroup.PlaceLabledControl("Hitbox", this, &WeaponSnipHitbox);
#pragma endregion

}

void CVisualTab::Setup()
{
	SetTitle("Visuals");

	ActiveLabel.SetPosition(1, 1);
	ActiveLabel.SetText("Active");
	RegisterControl(&ActiveLabel);

	Active.SetFileId("active");
	Active.SetState(true);
	Active.SetPosition(41, 1);
	RegisterControl(&Active);

#pragma region Options
//	OptionsGroup.SetText("Options");
//	OptionsGroup.SetPosition(0, 10);
//	OptionsGroup.SetSize(193, 430);

	OptionsGroup.SetPosition(0, 0);
	OptionsGroup.SetSize(200, 380);
	RegisterControl(&OptionsGroup);


	OptionsBox.SetFileId("opt_box");
	OptionsBox.AddItem("Off");
	OptionsBox.AddItem("Corner");
	OptionsBox.AddItem("Full");
	OptionsGroup.PlaceLabledControl("Box", this, &OptionsBox);

	OptionsHealth.SetFileId("opt_hp");
	OptionsGroup.PlaceLabledControl("Health", this, &OptionsHealth);

	OptionsInfo.SetFileId("opt_info");
	OptionsGroup.PlaceLabledControl("Info", this, &OptionsInfo);

	OptionsChams.SetFileId("opt_chams");
	OptionsChams.AddItem("Off");
	OptionsChams.AddItem("Normal");
	OptionsChams.AddItem("Flat");
	OptionsChams.SelectIndex(1);
	OptionsGroup.PlaceLabledControl("Chams", this, &OptionsChams);

	OptionsWallhackChams.SetFileId("opt_whcham");
	OptionsGroup.PlaceLabledControl("Wallhack Chams", this, &OptionsWallhackChams);

	OptionsSkeleton.SetFileId("opt_bone");
	OptionsGroup.PlaceLabledControl("Skeleton", this, &OptionsSkeleton);

	BacktrackingLol.SetFileId("opt_backdot");
	OptionsGroup.PlaceLabledControl("Backtrack Dots", this, &BacktrackingLol);

	OptionsAimLine.SetFileId("aimline");
	OptionsGroup.PlaceLabledControl("Aim - Line", this, &OptionsAimLine);

	OptionsCompRank.SetFileId("opt_comprank");
	OptionsGroup.PlaceLabledControl("Player Ranks", this, &OptionsCompRank);

	FiltersPlayers.SetState(true);

	FiltersEnemiesOnly.SetFileId("ftr_enemyonly");
	OptionsGroup.PlaceLabledControl("Enemies Only", this, &FiltersEnemiesOnly);

	FiltersWeapons.SetFileId("ftr_weaps");
	OptionsGroup.PlaceLabledControl("Weapons", this, &FiltersWeapons);

	FiltersC4.SetFileId("ftr_c4");
	OptionsGroup.PlaceLabledControl("C4", this, &FiltersC4);

#pragma endregion Setting up the Options controls

#pragma region Filters
	FiltersGroup.SetText("Extra");
	FiltersGroup.SetPosition(180, 0);
	FiltersGroup.SetSize(200, 380);
	RegisterControl(&FiltersGroup);

	BulletTracers.SetFileId("bullettracers");
	FiltersGroup.PlaceLabledControl("Bullet Tracers", this, &BulletTracers);

	OtherNoVisualRecoil.SetFileId("otr_visrecoil");
	FiltersGroup.PlaceLabledControl("No Visual Recoil", this, &OtherNoVisualRecoil);

	OtherRecoilCrosshair.SetFileId("otr_crosshair");
	OtherRecoilCrosshair.AddItem("Off");
	OtherRecoilCrosshair.AddItem("Static");
	OtherRecoilCrosshair.AddItem("Recoil");
	OtherRecoilCrosshair.AddItem("FOV Circle");
	OtherRecoilCrosshair.AddItem("Animated");
	OtherRecoilCrosshair.SelectIndex(3);
	FiltersGroup.PlaceLabledControl("Crosshairs", this, &OtherRecoilCrosshair);

	AnimCrossSpeed.SetFileId("AnimCrossSpeed");
	AnimCrossSpeed.SetBoundaries(4, 128);
	AnimCrossSpeed.SetValue(16);
	FiltersGroup.PlaceLabledControl("Animation Speed", this, &AnimCrossSpeed);

	StaticCrossSize.SetFileId("StaticCrossSize");
	StaticCrossSize.SetBoundaries(2, 20);
	StaticCrossSize.SetValue(12);
	FiltersGroup.PlaceLabledControl("Crosshair Size", this, &StaticCrossSize);

	OtherNoFlash.SetFileId("otr_noflash");
	FiltersGroup.PlaceLabledControl("No Flash", this, &OtherNoFlash);

	OtherNoScope.SetFileId("otr_noscope");
	FiltersGroup.PlaceLabledControl("No Scope", this, &OtherNoScope);

	OtherNoHands.SetFileId("otr_hands");
	OtherNoHands.AddItem("Off");
	OtherNoHands.AddItem("None");
	OtherNoHands.AddItem("Transparent");
	OtherNoHands.AddItem("Chams");
	OtherNoHands.AddItem("Rainbow");
	FiltersGroup.PlaceLabledControl("Hands", this, &OtherNoHands);

	OtherViewmodelFOV.SetFileId("otr_viewfov");
	OtherViewmodelFOV.SetBoundaries(0.f, 180.f);
	OtherViewmodelFOV.SetValue(0.f);
	FiltersGroup.PlaceLabledControl("VMDL Changer", this, &OtherViewmodelFOV);

	OtherFOV.SetFileId("otr_fov");
	OtherFOV.SetBoundaries(0.f, 180.f);
	OtherFOV.SetValue(90.f);
	FiltersGroup.PlaceLabledControl("FOV Changer", this, &OtherFOV);
	
#pragma endregion Setting up the Filters controls


}

void CMiscTab::Setup()
{
	SetTitle("Misc");

#pragma region Other
	OtherGroup.SetPosition(10, 10);
	OtherGroup.SetSize(360, 430);
	OtherGroup.SetText("Other");
	RegisterControl(&OtherGroup);

	OtherAutoJump.SetFileId("otr_autojump");
	OtherGroup.PlaceLabledControl("Auto Jump", this, &OtherAutoJump);

	OtherAutoStrafe.SetFileId("otr_strafe");
	OtherAutoStrafe.AddItem("Off");
	OtherAutoStrafe.AddItem("Legit");
	OtherAutoStrafe.AddItem("Rage");
	OtherGroup.PlaceLabledControl("Auto Strafer", this, &OtherAutoStrafe);

	OtherClantag.SetFileId("otr_spam");
	OtherClantag.AddItem("Off");
	OtherClantag.AddItem("skill simulator");
	OtherClantag.AddItem("skeet.cc");
	OtherClantag.AddItem("Blank");
	OtherClantag.AddItem("Valve");
	OtherGroup.PlaceLabledControl("Custom Clantag", this, &OtherClantag);

	OtherSpectators.SetFileId("otr_speclist");
	OtherGroup.PlaceLabledControl("Spectators List", this, &OtherSpectators);

	FakePingExploit.SetFileId("otr_fakepingexploit");
	OtherGroup.PlaceLabledControl("Fake ping exploit", this, &FakePingExploit);

	FakePingValue.SetFileId("otr_fakepingspike");
	FakePingValue.SetBoundaries(0, 800);
	FakePingValue.SetValue(0);
	OtherGroup.PlaceLabledControl("Fake ping spike", this, &FakePingValue);

	lstPlayers.SetFileId("configs");
	lstPlayers.AddItem("Legit 1");
	lstPlayers.AddItem("Legit 2");
	lstPlayers.AddItem("Legit 3");
	lstPlayers.AddItem("Rage 1");
	lstPlayers.AddItem("Rage 2");
	lstPlayers.AddItem("Rage 3");
	OtherGroup.PlaceLabledControl("Configs", this, &lstPlayers);

#pragma endregion other random options*/
}

void Menu::SetupMenu()
{
	Window.Setup();

	GUI.RegisterWindow(&Window);
	GUI.BindWindow(VK_INSERT, &Window);
	GUI.BindWindow(VK_F11, &Window);
}

void Menu::DoUIFrame()
{
	// General Processing

	// If the "all filter is selected tick all the others
	if (Window.VisualsTab.FiltersAll.GetState())
	{
		Window.VisualsTab.FiltersAll.SetState(false);
		Window.VisualsTab.FiltersC4.SetState(true);
		Window.VisualsTab.FiltersChickens.SetState(true);
		Window.VisualsTab.FiltersPlayers.SetState(true);
		Window.VisualsTab.FiltersWeapons.SetState(true);
	}

	GUI.Update();
	GUI.Draw();
}
