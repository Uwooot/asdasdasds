/*
Syn's AyyWare Framework 2015
*/

#pragma once

#include "GUI.h"
#include "Controls.h"

class CLegitBotTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Aimbot Settings
	CSilentGroupBox AimbotGroup;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CCheckBox AimbotFriendlyFire;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CCheckBox AimbotAutoPistol;
	CKeyBind  AimbotDisableVis;

	//Other Stuff
	CGroupBox Other;
	CSlider   TickModulation;
	CCheckBox AimbotBacktrack;
};

class CAutomaticsTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Main
	CSilentGroupBox WeaponMainGroup;
	CSlider   WeaponMainSpeed;
	CSlider   WeaponMainFoV;
	CSlider WeaponMainRecoilVal;
	CSlider RcsSmoothMain;
	CSlider RcsRandMain;
	CCheckBox WeaponMainPSilent;
	CSlider   WeaponMainInacc;
	CComboBox WeaponMainHitbox;
	CSlider StopAimTimeMain;
};

class CPistolsTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Pistol
	CSilentGroupBox WeaponPistGroup;
	CSlider   WeaponPistSpeed;
	CCheckBox   WeaponPistShotDelay;
	CSlider   WeaponPistFoV;
	CSlider WeaponPistRecoilVal;
	CSlider RcsSmoothPistols;
	CSlider RcsRandPistols;
	CCheckBox WeaponPistPSilent;
	CSlider   WeaponPistInacc;
	CComboBox WeaponPistHitbox;
	CSlider StopAimTimePist;
};

class CSnipersTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Sniper
	CSilentGroupBox WeaponSnipGroup;
	CSlider   WeaponSnipSpeed;
	CCheckBox   WeaponSnipShotDelay;
	CSlider   WeaponSnipFoV;
	CSlider WeaponSnipRecoilVal;
	CSlider RcsSmoothSnipers;
	CSlider RcsRandSnipers;
	CCheckBox WeaponSnipPSilent;
	CSlider   WeaponSnipInacc;
	CComboBox WeaponSnipHitbox;
	CSlider StopAimTimeSnip;
};

class CVisualTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	// Options Settings
	CSilentGroupBox OptionsGroup;
	CComboBox OptionsBox;
	CCheckBox OptionsHealth;
	CCheckBox OptionsInfo;
	CCheckBox OptionsHelmet;
	CCheckBox OptionsKit;
	CCheckBox OptionsDefuse;
	//CCheckBox OptionsGlow;
	CComboBox OptionsChams;
	CCheckBox OptionsSkeleton;
	CCheckBox OptionsWallhackChams;
	CCheckBox BacktrackingLol;
	CCheckBox OptionsAimLine;
	CCheckBox OptionsAimSpot;
	CCheckBox OptionsCompRank;

	// Filters Settings
	CSilentGroupBox FiltersGroup;
	CCheckBox FiltersAll;
	CCheckBox FiltersPlayers;
	CCheckBox FiltersEnemiesOnly;
	CCheckBox FiltersWeapons;
	CCheckBox FiltersChickens;
	CCheckBox FiltersC4;



	CSilentGroupBox OtherGroup;
	CComboBox OtherRecoilCrosshair;
	CSlider   AnimCrossSpeed;
	CSlider   StaticCrossSize;
	CCheckBox OtherHitmarker;
	CCheckBox OtherRadar;
	CCheckBox OtherNoVisualRecoil;
	CCheckBox OtherNoSky; 
	CCheckBox OtherNoFlash; 
	CCheckBox OtherNoScope;
	CComboBox OtherNoHands;
	CCheckBox BulletTracers;
	CSlider OtherViewmodelFOV;
	CSlider OtherFOV;
};

class CMiscTab : public CTab
{
public:
	void Setup();

	//configs
	CComboBox lstPlayers;
	// Other Settings
	CSilentGroupBox OtherGroup;
	CCheckBox OtherAutoJump;
	CComboBox OtherAutoStrafe;
	CKeyBind  OtherLagSwitch;
	CCheckBox OtherSpectators;
	CCheckBox FakePingExploit;
	CSlider FakePingValue;
	//CCheckBox OtherAutoAccept;
	CComboBox OtherClantag;
	// Fake Lag Settings
	CSilentGroupBox FakeLagGroup;
	//CCheckBox FakeLagWhileShooting;
};

class AyyWareWindow : public CWindow
{
public:
	void Setup();

	CLegitBotTab LegitBotTab;
	CAutomaticsTab AutomaticsTab;
	CPistolsTab PistolsTab;
	CSnipersTab SnipersTab;
	CVisualTab VisualsTab;
	CMiscTab MiscTab;

	CButton LoadButton;
	CButton SaveButton2;
	CButton LoadButton2;
	CButton SaveButton3;
	CButton LoadButton3;

	CButton UnloadButton;
};

namespace Menu
{
	void SetupMenu();
	void DoUIFrame();

	extern AyyWareWindow Window;

};