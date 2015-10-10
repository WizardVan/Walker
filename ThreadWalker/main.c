#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <tchar.h>

//  Forward declarations:
BOOL ListProcessThreads(DWORD dwOwnerPID);
void printError(TCHAR* msg);
typedef LONG    NTSTATUS;
typedef NTSTATUS(WINAPI *pNtQIT)(HANDLE, LONG, PVOID, ULONG, PULONG);
#define STATUS_SUCCESS    ((NTSTATUS)0x00000000L)
#define ThreadQuerySetWin32StartAddress 9
DWORD GetThreadStartAddress(HANDLE hThread);
LPVOID addr;

int main(void)
{
	while (1)
	{ 
		LoadLibrary("kernel32.dll");
		addr = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibrary");
		printf("0x%08X\n", addr);
		ListProcessThreads(GetCurrentProcessId());
		Sleep(100);
	}
	getchar();
	return 0;
}

BOOL ListProcessThreads(DWORD dwOwnerPID)
{
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	HANDLE hThread=NULL;
	THREADENTRY32 te32;

	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hThreadSnap == INVALID_HANDLE_VALUE)
		return(FALSE);

	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32);

	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if (!Thread32First(hThreadSnap, &te32))
	{
		printError(TEXT("Thread32First"));  // Show cause of failure
		CloseHandle(hThreadSnap);     // Must clean up the snapshot object!
		return(FALSE);
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do
	{
		if (te32.th32OwnerProcessID == dwOwnerPID)
		{
			hThread = OpenThread(THREAD_QUERY_INFORMATION, FALSE, te32.th32ThreadID);
			//_tprintf(TEXT("\n     THREAD ID      = 0x%08X"), te32.th32ThreadID);
			//_tprintf(TEXT("\n     base priority  = %d"), te32.tpBasePri);
			//_tprintf(TEXT("\n     StartAddress  = 0x%08X"), GetThreadStartAddress(hThread));
			if (GetThreadStartAddress(hThread) == (DWORD)addr)
			{
				ExitProcess(-1);
			}
			//_tprintf(TEXT("\n     delta priority = %d"), te32.tpDeltaPri);
		}
	} while (Thread32Next(hThreadSnap, &te32));

	//_tprintf(TEXT("\n"));

	//  Don't forget to clean up the snapshot object.
	CloseHandle(hThreadSnap);
	return(TRUE);
}

void printError(TCHAR* msg)
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}

DWORD GetThreadStartAddress(HANDLE hThread)

{

	NTSTATUS ntStatus;


	DWORD dwStartAddress=0;



	pNtQIT NtQueryInformationThread = (pNtQIT)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtQueryInformationThread");
	if (NtQueryInformationThread == NULL)
		return 0;
	
	ntStatus = NtQueryInformationThread(hThread, ThreadQuerySetWin32StartAddress, &dwStartAddress, sizeof(DWORD), NULL);

	CloseHandle(hThread);



	if (ntStatus != STATUS_SUCCESS) return 0;

	return dwStartAddress;

}