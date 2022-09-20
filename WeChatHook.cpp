// WeChatHook.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WeChatHook.h"
#include <Windows.h>
#include "utils.h"

int PORT = 25555;

// 此代码模块中包含的函数的前向声明:
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DialogProc(_In_ HWND hDlg, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	BOOL result;
	DWORD PID = ProcessNameFindPID(WeChatProcessName);
	if (PID == 0)
	{
		return 0;
	}
	else
	{
		result = StartListen(PID, PORT);
		if(result == 0)
		{
			return 0;
		}
	}
	DialogBox(hInstance, MAKEINTRESOURCE(ID_MAIN), NULL, DialogProc);
    return 0;
}

INT_PTR CALLBACK DialogProc(_In_ HWND hDlg, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	BOOL result;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == INJECT)
		{
			DWORD PID = ProcessNameFindPID(WeChatProcessName);
			StartListen(PID, PORT);
		}
		if (LOWORD(wParam) == UNJECT)
		{
			DWORD PID = ProcessNameFindPID(WeChatProcessName);
			if (PID == 0)
			{
				MessageBox(NULL, "未找到进程", "错误", 0);
				return 0;
			}
			result = StopListen(PID);
			if (result == 0)
			{
				MessageBox(NULL, "未找到DLL", "错误", 0);
				return 0;
			}
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	}
	return (INT_PTR)FALSE;
}