#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <math.h>
#include <codecvt>
#include <Psapi.h>
#include <list>
#include <timeapi.h>
#include <winnt.h>
#pragma comment(lib,"Kernel32.lib")
#pragma comment(lib,"Winmm.lib")

HMODULE g_hModule = NULL;
DWORD ProcessID;
uintptr_t ModuleBase;
HWND cmd_msg = NULL;

void SendMouseKeyDown(DWORD keyCode, DWORD mouseCode)
{
	// Simulate the SHIFT key press
	INPUT shiftDownInput;
	shiftDownInput.type = INPUT_KEYBOARD;
	shiftDownInput.ki.wVk = keyCode;
	shiftDownInput.ki.dwFlags = 0;

	// Simulate the LEFT MOUSE BUTTON press
	INPUT leftButtonDownInput;
	leftButtonDownInput.type = INPUT_MOUSE;
	leftButtonDownInput.mi.dx = 0;
	leftButtonDownInput.mi.dy = 0;
	leftButtonDownInput.mi.dwFlags = mouseCode;

	// Put the input events into an array
	INPUT inputEvents[2] = {shiftDownInput, leftButtonDownInput };

	// Send the input events
	UINT numInputs = sizeof(inputEvents) / sizeof(INPUT);
	SendInput(numInputs, inputEvents, sizeof(INPUT));
}


void SendMouseKeyRelease(DWORD keyCode, DWORD mouseCode)
{
	// Simulate the LEFT MOUSE BUTTON release
	INPUT leftButtonUpInput;
	leftButtonUpInput.type = INPUT_MOUSE;
	leftButtonUpInput.mi.dx = 0;
	leftButtonUpInput.mi.dy = 0;
	leftButtonUpInput.mi.dwFlags = mouseCode;

	// Simulate the SHIFT key release
	INPUT shiftUpInput;
	shiftUpInput.type = INPUT_KEYBOARD;
	shiftUpInput.ki.wVk = keyCode;
	shiftUpInput.ki.dwFlags = KEYEVENTF_KEYUP;

	// Put the input events into an array
	INPUT inputEvents[2] = {shiftUpInput, leftButtonUpInput };

	// Send the input events
	UINT numInputs = sizeof(inputEvents) / sizeof(INPUT);
	SendInput(numInputs, inputEvents, sizeof(INPUT));
}

void SendKeyDown(DWORD keyCode, DWORD _keyCode)
{
	// Simulate the SHIFT key press
	INPUT shiftDownInput;
	shiftDownInput.type = INPUT_KEYBOARD;
	shiftDownInput.ki.wVk = keyCode;
	shiftDownInput.ki.dwFlags = 0;

	// Simulate the LEFT MOUSE BUTTON press
	INPUT leftButtonDownInput;
	leftButtonDownInput.type = INPUT_KEYBOARD;
	leftButtonDownInput.ki.wVk = _keyCode;
	leftButtonDownInput.ki.dwFlags = 0;

	// Put the input events into an array
	INPUT inputEvents[2] = {shiftDownInput, leftButtonDownInput };

	// Send the input events
	UINT numInputs = sizeof(inputEvents) / sizeof(INPUT);
	SendInput(numInputs, inputEvents, sizeof(INPUT));
}

void SendKeyRelease(DWORD keyCode, DWORD _keyCode)
{
	// Simulate the LEFT MOUSE BUTTON release
	INPUT leftButtonUpInput;
	leftButtonUpInput.type = INPUT_KEYBOARD;
	leftButtonUpInput.ki.wVk = keyCode;
	leftButtonUpInput.mi.dwFlags = KEYEVENTF_KEYUP;

	// Simulate the SHIFT key release
	INPUT shiftUpInput;
	shiftUpInput.type = INPUT_KEYBOARD;
	shiftUpInput.ki.wVk = _keyCode;
	shiftUpInput.ki.dwFlags = KEYEVENTF_KEYUP;

	// Put the input events into an array
	INPUT inputEvents[2] = {shiftUpInput, leftButtonUpInput };

	// Send the input events
	UINT numInputs = sizeof(inputEvents) / sizeof(INPUT);
	SendInput(numInputs, inputEvents, sizeof(INPUT));
}