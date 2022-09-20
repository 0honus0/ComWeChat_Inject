#include <Windows.h>
#include <TlHelp32.h>
#include "utils.h"

typedef BOOL (*START_LISTEN)(DWORD pid, int port);
typedef BOOL(*STOP_LISTEN)(DWORD pid);

DWORD ProcessNameFindPID(LPCSTR ProcessName)
{
	HANDLE ProcessAll = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS ,NULL);
	
	PROCESSENTRY32 ProcessEntry = {0};
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	do
	{
		if (strcmp((char *)ProcessEntry.szExeFile, ProcessName) == 0)
		{
			return ProcessEntry.th32ProcessID;
		}
	} while (Process32Next(ProcessAll, &ProcessEntry));
	MessageBox(NULL, "未找到进程", "错误", 0);
	return 0;
}

BOOL StartListen(DWORD PID , int port)
{
	HMODULE hDLL = LoadLibrary(DLLNAME);
	if (hDLL == NULL)
	{
		MessageBox(NULL, "未找到DLL", "错误", 0);
		return FALSE;
	}

	START_LISTEN pStartListen = (START_LISTEN)GetProcAddress(hDLL, "start_listen");  // 获取函数指针

	pStartListen(PID, port);
	
	FreeLibrary(hDLL);  // 使用完后释放。

	return TRUE;
}

BOOL StopListen(DWORD PID)
{
	HMODULE hDLL = LoadLibrary(DLLNAME);
	if (hDLL == NULL)
	{
		return FALSE;
	}

	STOP_LISTEN pStopListen = (STOP_LISTEN)GetProcAddress(hDLL, "stop_listen");  // 获取函数指针

	pStopListen(PID);

	FreeLibrary(hDLL);  // 使用完后释放。

	return TRUE;
}
