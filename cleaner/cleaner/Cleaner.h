#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <tlhelp32.h>

#define MAX_USERNAME_SIZE 100

class Cleaner
{
public:
	Cleaner();
	~Cleaner();
	BOOL		removeOfStartingProcess();
	BOOL		showSources();
	BOOL		removeFiles();
	BOOL		reloadExplorer();

private:
	DWORD		findProcess(std::wstring processName);
};
