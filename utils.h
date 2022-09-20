//#pragma once
#include <Windows.h>
#pragma comment(lib, "SWeChatRobot.dll")

#define WeChatProcessName "WeChat.exe"
#define DLLNAME "wxDriver.dll"

DWORD ProcessNameFindPID(LPCSTR ProcessName);
BOOL StartListen(DWORD PID, int port);
BOOL StopListen(DWORD PID);