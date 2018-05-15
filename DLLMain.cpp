//       With love from ur bruddah Omi
//                 to my bruddah Uwooot
//
//      pasted, cleaned, improved, made p by Uwooot
//      menu colors changed by Omi, but the menu still was made by Uwooot
// This is for you:
/*
_____8888888888____________________
____888888888888888_________________
__888888822222228888________________
_88888822222222288888_______________
888888222222222228888822228888______
888882222222222222288222222222888___
8888822222222222222222222222222288__
_8888822222222222222222222222222_88_
__88888222222222222222222222222__888
___888822222222222222222222222___888
____8888222222222222222222222____888
_____8888222222222222222222_____888_
______8882222222222222222_____8888__
_______888822222222222______888888__
________8888882222______88888888____
_________888888_____888888888_______
__________88888888888888____________
___________8888888888_______________
____________8888888_________________
_____________88888__________________
______________888___________________
_______________8____________________
*/
// xD


//#define AYY_DEBUG

// General shit
//#include "DLLMain.h"
#include "Utilities.h"
#include "CBulletListener.h"
// Injection stuff
#include "INJ/ReflectiveLoader.h"

// Stuff to initialise
#include "Offsets.h"
#include "Interfaces.h"
#include "Hooks.h"
#include "RenderManager.h"
#include "Hacks.h"
#include "Menu.h"
#include "Dumping.h"

// Used as part of the reflective DLL injection
extern HINSTANCE hAppInstance;
bool lbyupdate1;
// Our DLL Instance
HINSTANCE HThisModule;
bool DoUnload;

float lineLBY;
float lineRealAngle;
float lineFakeAngle;


// Our thread we use to setup everything we need
// Everything appart from code in hooks get's called from inside 
// here.

int InitialThread()
{
	Offsets::Initialise(); // Set our VMT offsets and do any pattern scans
	Interfaces::Initialise(); // Get pointers to the valve classes
	NetVar.RetrieveClasses(); // Setup our NetVar manager (thanks shad0w bby)
	NetvarManager::Instance()->CreateDatabase();
	Render::Initialise();
	Hacks::SetupHacks();
	Menu::SetupMenu();
	Hooks::Initialise();
	CBulletListener::singleton()->init();

	//---------------------------------------------------------
	Utilities::Log("Ready");

	// While our cheat is running
	while (DoUnload == false)
	{
		Sleep(1000);
	}

	Hooks::UndoHooks();
	Sleep(2000); // Make sure none of our hooks are running
	FreeLibraryAndExitThread(HThisModule, 0);

	return 0;
}

// DllMain
// Entry point for our module
BOOL WINAPI DllMain(
	_In_ HINSTANCE hinstDLL,
	_In_ DWORD     fdwReason,
	_In_ LPVOID    lpvReserved
	)
{
	switch (fdwReason)
	{
	case DLL_QUERY_HMODULE:
		if (lpvReserved != NULL)
			*(HMODULE *)lpvReserved = hAppInstance;
		break;
	case DLL_PROCESS_ATTACH:
		HThisModule = hinstDLL;
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitialThread, NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}
