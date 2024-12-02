#include "stuff.h"

int main() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	if (MessageBoxA(0, "You are about to run a GDI Only.\n\n\
THIS WILL N O T destroy your PC.", "Holzer (GDI Only)", MB_YESNO | MB_ICONWARNING) != IDYES) {
		ExitProcess(0);
	}
    if (MessageBoxA(0, "FINAL WARNING!\n\n\
Theres noises and flashing lights.\nDo you still wanna execute this GDI Only?", "Holzer (GDI Only)", MB_YESNO | MB_ICONWARNING) != IDYES) {
		ExitProcess(0);
	}

	

	startPayloads();
}