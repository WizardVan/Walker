#include <windows.h>
#include <stdio.h>
#include <tchar.h>
BOOL CALLBACK EnumWindowsProc(HWND hwnd, DWORD lParam);

void main()
{
	HANDLE hwFind;
	EnumWindows((WNDENUMPROC)EnumWindowsProc, 0);
	hwFind = FindWindow(TEXT("Window"), TEXT("Cheat Engine 6.4"));
	if (hwFind)
		ExitProcess(0);
	hwFind = FindWindow(TEXT("TfMain"),NULL);
	if (hwFind)
	{
		hwFind = FindWindow(TEXT("TApplication"), NULL);
		if (hwFind)
			ExitProcess(0);
	}
		
	getchar();
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, DWORD lParam)
{
	CHAR NAME[255];
	LPTSTR lpString = NAME;
	LPTSTR lpClassName = NAME;
	INT nMaxCounte = 255;
	
	if (!IsWindowVisible(hwnd))
	{
		return TRUE;
	}

	
	if (!IsWindowEnabled(hwnd))
	{
		return TRUE;
	}

	// Do something
	
	GetClassName(hwnd, lpClassName, nMaxCounte);
	_tprintf("classname:%s\r\n", lpClassName);
	return TRUE;
}