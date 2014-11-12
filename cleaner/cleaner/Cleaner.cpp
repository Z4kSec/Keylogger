#include "Cleaner.h"


Cleaner::Cleaner()
{
}


Cleaner::~Cleaner()
{
}


BOOL Cleaner::removeOfStartingProcess()
{
	HKEY	hKey = NULL;
	DWORD	regType = REG_SZ;
	wchar_t	sizePath[MAX_PATH] = {};
	DWORD	len = sizeof(sizePath);
	BOOL	check = FALSE;

	if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey) == 0)
	{
		if (RegDeleteValueW(hKey, L"injector") == ERROR_SUCCESS)
			check = TRUE;
		else
			check = FALSE;
	}

	if (hKey != NULL)
		RegCloseKey(hKey);
	return (check);
}

BOOL Cleaner::showSources()
{
	HKEY key;
	DWORD dwData = 1;

	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 0, KEY_WRITE, &key) == ERROR_SUCCESS)
	{
		if (RegSetValueEx(key, L"Hidden", 0, REG_DWORD, (LPBYTE)&dwData, sizeof(DWORD)))
			RegCloseKey(key);
		return (TRUE);
		RegCloseKey(key);
	}
	return (FALSE);
}

DWORD Cleaner::findProcess(std::wstring processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return (NULL);

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return (processInfo.th32ProcessID);
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return (processInfo.th32ProcessID);
		}
	}

	CloseHandle(processesSnapshot);
	return (NULL);
}

BOOL Cleaner::reloadExplorer()
{
	DWORD				pid = findProcess(L"explorer.exe");;
	HANDLE				proc = NULL;
	STARTUPINFOW		siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	DWORD				secWait = 10;

	proc = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);
	if (proc == NULL)
		return (FALSE);
	TerminateProcess(proc, 0);
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);
	if (!CreateProcessW(L"C:\\Windows\\explorer.exe", NULL, 0, 0, FALSE, CREATE_DEFAULT_ERROR_MODE, 0, 0, &siStartupInfo, &piProcessInfo))
		return (FALSE);
	WaitForSingleObject(piProcessInfo.hProcess, (secWait * 1000));
	return (TRUE);
}

BOOL Cleaner::removeFiles()
{
	wchar_t			userNameW[MAX_USERNAME_SIZE];
	DWORD			sizeUsername = MAX_USERNAME_SIZE;
	std::wstring	pathDirectory;
	std::wstring	pathFileInjector;
	std::wstring	pathFileDll;
	std::wstring	pathFilePem;

	if (GetUserNameW((LPWSTR)userNameW, &sizeUsername))
	{
		std::wstring userW(userNameW);
		pathDirectory.append(L"C:\\Users\\");
		pathDirectory.append(userW);
		pathDirectory.append(L"\\Documents\\Injector\\");
		pathFileInjector.append(pathDirectory);
		pathFileInjector.append(L"injector.exe");
		pathFileDll.append(pathDirectory);
		pathFileDll.append(L"setHook.dll");
		pathFilePem.append(pathDirectory);
		pathFilePem.append(L"ca.pem");
	}
	else
		return (FALSE);
	if (!DeleteFileW(pathFileInjector.c_str())
		|| !DeleteFileW(pathFileDll.c_str())
		|| !DeleteFileW(pathFilePem.c_str())
		|| !RemoveDirectoryW(pathDirectory.c_str()))
		return (FALSE);
	return (TRUE);
}