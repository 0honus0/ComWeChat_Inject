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
	MessageBox(NULL, "δ�ҵ�����", "����", 0);
	return 0;
}

BOOL StartListen(DWORD PID , int port)
{
	HMODULE hDLL = LoadLibrary(DLLNAME);
	if (hDLL == NULL)
	{
		MessageBox(NULL, "δ�ҵ�DLL", "����", 0);
		return FALSE;
	}

	START_LISTEN pStartListen = (START_LISTEN)GetProcAddress(hDLL, "start_listen");  // ��ȡ����ָ��

	pStartListen(PID, port);
	
	FreeLibrary(hDLL);  // ʹ������ͷš�

	return TRUE;
}

BOOL StopListen(DWORD PID)
{
	HMODULE hDLL = LoadLibrary(DLLNAME);
	if (hDLL == NULL)
	{
		return FALSE;
	}

	STOP_LISTEN pStopListen = (STOP_LISTEN)GetProcAddress(hDLL, "stop_listen");  // ��ȡ����ָ��

	pStopListen(PID);

	FreeLibrary(hDLL);  // ʹ������ͷš�

	return TRUE;
}
