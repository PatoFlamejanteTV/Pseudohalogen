#pragma once
#include <windows.h>
#include <cmath>

#pragma comment(lib, "winmm.lib")

#define winapi WINAPI
#define lpvoid LPVOID
#define dword DWORD
#define ulonglong ULONGLONG
#define uint UINT
#define rdtsc __rdtsc

#include <Windows.h>
#include <WinDef.h>
#include <WinNT.h>
#include <stdint.h>
#include <math.h>

#include <string>
#include <array>



//typedef NTSTATUS(NTAPI* RtlAP)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
//typedef NTSTATUS(NTAPI* NtRHE)(NTSTATUS, ULONG, ULONG, PULONG_PTR, ULONG, PULONG);

static HWAVEOUT wave = 0;

void startPayloads(); // start lol
