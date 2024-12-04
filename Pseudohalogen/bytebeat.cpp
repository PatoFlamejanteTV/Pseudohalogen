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
void WINAPI Bytebeat1() {
	WAVEFORMATEX wavef = { WAVE_FORMAT_PCM, 1, 8000, 0, WAVE_FORMAT_PCM, 8, 0 };

	waveOutOpen(&wave, 0, &wavef, 0, 0, 0);
	char buffer[8000 * 60];

	for (DWORD t = 0; t < sizeof(buffer); t++) {
		buffer[t] = (t * (t << 2 | t >> 7));
	}

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };

	waveOutPrepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutWrite(wave, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutClose(wave);
}

void WINAPI Bytebeat2() {
	WAVEFORMATEX wavef = { WAVE_FORMAT_PCM, 1, 8000, 0, WAVE_FORMAT_PCM, 8, 0 };

	waveOutOpen(&wave, 0, &wavef, 0, 0, 0);
	char buffer[8000 * 60];

	for (DWORD t = 0; t < sizeof(buffer); t++) {
		buffer[t] = (t * (t >> 2 | t >> 7));
	}

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };

	waveOutPrepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutWrite(wave, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutClose(wave);
}

/*void WINAPI BytebeatPato1() {
	WAVEFORMATEX wavef = { WAVE_FORMAT_PCM, 1, 8000, 0, WAVE_FORMAT_PCM, 8, 0 };

	waveOutOpen(&wave, 0, &wavef, 0, 0, 0);
	char buffer[8000 * 60];

	for (DWORD t = 0; t < sizeof(buffer); t++) {
		buffer[t] = ((t>>9&1+t>>12&7?0:9001/(t%4096)-t/9&8?-1:0)^t>>4&100*((t<<2|t>>5|t^63)&(t<<10|t>>11)));
	}

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };

	waveOutPrepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutWrite(wave, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutClose(wave);
}*/

void WINAPI BytebeatPato2() {
	WAVEFORMATEX wavef = { WAVE_FORMAT_PCM, 1, 8000, 0, WAVE_FORMAT_PCM, 8, 0 };

	waveOutOpen(&wave, 0, &wavef, 0, 0, 0);
	char buffer[8000 * 60];

	for (DWORD t = 0; t < sizeof(buffer); t++) {
		buffer[t] = ((t>>9&1+t>>12&7?0:9001/(t%4096)-t/9&8?-1:0)^t>>4&t*(t>>5|t>>8)>>(t>>16));
	}

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };

	waveOutPrepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutWrite(wave, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutClose(wave);
}

/*void WINAPI BytebeatPato3() {
	WAVEFORMATEX wavef = { WAVE_FORMAT_PCM, 1, 8000, 0, WAVE_FORMAT_PCM, 8, 0 };

	waveOutOpen(&wave, 0, &wavef, 0, 0, 0);
	char buffer[8000 * 60];

	for (DWORD t = 0; t < sizeof(buffer); t++) {
		buffer[t] = (t*t*4/((5656>>(t>>12&14)&7)+9)*(t>>10&893)&t>>4^((t>>16&1?0:t>>10&-t>>14&3)|t>>9&1+t>>12&7?0:9001/(t%4096)-t/9&8?-1:0));
	}

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };

	waveOutPrepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutWrite(wave, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutClose(wave);
}*/


void WINAPI Bytebeat3() {
	WAVEFORMATEX wavef = { WAVE_FORMAT_PCM, 1, 8000, 0, WAVE_FORMAT_PCM, 8, 0 };

	waveOutOpen(&wave, 0, &wavef, 0, 0, 0);
	char buffer[8000 * 80];

	for (DWORD t = 0; t < sizeof(buffer); t++) {
		buffer[t] = (t * (t >> 7));
	}

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };

	waveOutPrepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutWrite(wave, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutClose(wave);
}

void WINAPI Bytebeat4() {
	WAVEFORMATEX wavef = { WAVE_FORMAT_PCM, 1, 8000, 0, WAVE_FORMAT_PCM, 8, 0 };

	waveOutOpen(&wave, 0, &wavef, 0, 0, 0);
	char buffer[8000 * 60];

	for (DWORD t = 0; t < sizeof(buffer); t++) {
		buffer[t] = (t * ((t >> t | t >> 10) * 10 & 30));
	}

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };

	waveOutPrepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutWrite(wave, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutClose(wave);
}

void WINAPI Bytebeat5() {
	WAVEFORMATEX wavef = { WAVE_FORMAT_PCM, 1, 8000, 0, WAVE_FORMAT_PCM, 8, 0 };

	waveOutOpen(&wave, 0, &wavef, 0, 0, 0);
	char buffer[8000 * 60];

	for (DWORD t = 0; t < sizeof(buffer); t++) {
		buffer[t] = (t * ((t >> 6 | t >> 13) & 50));
	}

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };

	waveOutPrepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutWrite(wave, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(wave, &header, sizeof(WAVEHDR));
	waveOutClose(wave);
}