/*
MIT License

Copyright (c) 2024 UltimateQuack

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "stuff.h"
#include <windows.h>
#include <windowsx.h>
#include "resource.h"

#include "strsafe.h"
#pragma comment(lib, "winmm.lib")

#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )

// tray icon data
NOTIFYICONDATA m_NID;

BOOL CreateTrayIcon()
{
    memset(&m_NID, 0, sizeof(m_NID));
    m_NID.cbSize = sizeof(m_NID);

    //m_NID.uID = 102;

    // set handle to the window that receives tray icon notifications
    m_NID.hWnd = GetForegroundWindow();

    // fields that are being set when adding tray icon 
    m_NID.uFlags = NIF_MESSAGE | NIF_ICON;

    // set image
    m_NID.hIcon = LoadIcon(NULL,MAKEINTRESOURCE(IDI_BATTERY_IMAGE));

    if (!m_NID.hIcon)
        return FALSE;

    m_NID.uVersion = NOTIFYICON_VERSION_4;

    if (!Shell_NotifyIcon(NIM_ADD, &m_NID))
        return FALSE;

    return Shell_NotifyIcon(NIM_SETVERSION, &m_NID);
}

BOOL ShowTrayIconBalloon(LPCTSTR pszTitle, LPCTSTR pszText, UINT unTimeout, DWORD dwInfoFlags)
{
    Sleep(rand() % 3000 + 2400);
    m_NID.uFlags |= NIF_INFO;
    m_NID.uTimeout = unTimeout;
    m_NID.dwInfoFlags = dwInfoFlags;

    if (StringCchCopy(m_NID.szInfoTitle, sizeof(m_NID.szInfoTitle), pszTitle) != S_OK)
        return FALSE;

    if (StringCchCopy(m_NID.szInfo, sizeof(m_NID.szInfo), pszText) != S_OK)
        return FALSE;

    return Shell_NotifyIcon(NIM_MODIFY, &m_NID);
}

int main() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	if (MessageBoxA(0, "You are about to run a GDI Only.\n\n\
THIS WILL [[N O T]] destroy your PC.", "Pseudohalogen (GDI Only)", MB_YESNO | MB_ICONWARNING) != IDYES) {
		ExitProcess(0);
	}
    if (MessageBoxA(0, "FINAL WARNING!\n\n\
Theres noises and flashing lights.\nDo you still wanna execute this GDI Only?", "Pseudohalogen (GDI Only)", MB_YESNO | MB_ICONWARNING) != IDYES) {
		ExitProcess(0);
	}
    startPayloads();
    
	CreateTrayIcon();
	ShowTrayIconBalloon(L"Battery overflowed", L"Your battery cant be trusted because it overflows the 100 percent hard-coded limit.\nPlease call technical support at:\nsupport.microsoft.com/en-us/home/contact", 1000, NIIF_WARNING);
	
}