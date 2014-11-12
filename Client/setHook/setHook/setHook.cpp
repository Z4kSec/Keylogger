// setHook.cpp : définit les fonctions exportées pour l'application DLL.
//

#include "stdafx.h"
#include <Windows.h>
#define SETHOOK_EXPORT extern "C" __declspec(dllexport)

SETHOOK_EXPORT void initHook()
{
	MessageBox(NULL, L"initHook works", L"Message init ", NULL);
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		MessageBox(NULL, L"Hook.dll has been injected !", L"Hook.dll", 0);

	}
	return TRUE;
}