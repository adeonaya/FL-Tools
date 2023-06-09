#include "main.h"

BOOL IsValid(DWORD64 address)
{
	if (!IsBadReadPtr((const void*)address, (UINT_PTR)8)) return TRUE;
	else return FALSE;
}


const char* FL_GetWindowTitle(HWND window) {
	char windowTitle[256];
	GetWindowText(window, windowTitle, sizeof(windowTitle));
	return windowTitle;
}

const char* FL_GetWindowClassName(HWND window) {
	char className[256];
	GetClassName(window, className, sizeof(className));
	return className;
}

const char* FL_GetText(HWND window) {
	char text[256];
	SendMessage(window, WM_GETTEXT, sizeof(text), LPARAM(text));
	return text;
}

extern "C" __declspec(dllexport)
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		g_hModule = hModule;
		DisableThreadLibraryCalls(hModule);
		ProcessID = GetCurrentProcessId();
		ModuleBase = (uintptr_t)GetModuleHandle(0);
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

// Exporting function usable with SetWindowsHookEx
extern "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam) {
	if (code == HC_ACTION)
	{
		LPMSG msg = (LPMSG)lParam;
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(msg->hwnd, &p);
		const char* WindowTitle = FL_GetWindowTitle(msg->hwnd);
		const char* WindowClassName = FL_GetWindowClassName(msg->hwnd);
		const char* Text = FL_GetText(msg->hwnd);
		switch (msg->message) {
		case WM_COMMAND:
			printf("WM_COMMAND: %p, HWND: %s, wParam: %p, lParam: %p\n", msg->hwnd, WindowClassName, msg->wParam, msg->lParam);
			cmd_msg = msg->hwnd;
			switch (msg->wParam)
			{
			case 0x3E3:
				keybd_event('O', 0, 0, 0);
				keybd_event('O', 0, KEYEVENTF_KEYUP, 0);
				break;
			case 0x3E4:
				keybd_event('O', 0, 0, 0);
				keybd_event('O', 0, KEYEVENTF_KEYUP, 0);
				break;
			}
			break;
		case WM_SYSCOMMAND:
			printf("WM_SYSCOMMAND: %p, HWND: %s, wParam: %p, lParam: %p\n", msg->hwnd, WindowClassName, msg->wParam, msg->lParam);
			break;
		case WM_LBUTTONDOWN:
			printf("WM_LBUTTONDOWN: %p, HWND: %s, wParam: %p, lParam: %p, Text: %s\n", msg->hwnd, WindowClassName, msg->wParam, msg->lParam, Text);
			break;
		case WM_LBUTTONUP:
			//printf("WM_LBUTTONUP: %p, wParam: %i, lParam: %p\n", msg->hwnd, msg->wParam, msg->lParam);
			break;
		case WM_KEYDOWN:
			printf("WM_KEYDOWN: %p, HWND: %s, wParam: %p, lParam: %p, Text: %s\n", msg->hwnd, WindowClassName, msg->wParam, msg->lParam, Text);
			if (cmd_msg)
			{
				// KEY 1
				if (msg->wParam == 0x31) 
				{
					msg->message = WM_NULL;
					if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
					{
						SendMessage(cmd_msg, WM_COMMAND, 0x149, NULL);
						return 1;
					}
					else if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					{
						return 1;
					}
					SendMouseKeyDown(VK_RSHIFT, MOUSEEVENTF_LEFTDOWN);
					return 1;
				}
				// KEY 2
				else if (msg->wParam == 0x32)
				{
					msg->message = WM_NULL;
					if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
					{
						return 1;
					}
					else if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					{
						return 1;
					}
					SendMouseKeyDown(VK_RSHIFT, MOUSEEVENTF_RIGHTDOWN);
					return 1;
				}
				// KEY 3
				else if (msg->wParam == 0x33)
				{
					msg->message = WM_NULL;
					if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
					{
						SendMessage(cmd_msg, WM_COMMAND, 0x174, NULL);
						return 1;
					}
					else if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					{
						return 1;
					}
					SendMessage(cmd_msg, WM_COMMAND, 0x126, NULL);
					//SendMessage(msg->hwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(p.x, p.y));
					return 1;
				}
				// KEY 4
				else if (msg->wParam == 0x34)
				{
					msg->message = WM_NULL;
					if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
					{
						SendMessage(cmd_msg, WM_COMMAND, 0x154, NULL);
						return 1;
					}
					else if (GetAsyncKeyState(VK_SHIFT))
					{
						return 1;
					}
					keybd_event(VK_ESCAPE, 0, 0, 0);
					keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
					return 1;
				}
				// KEY 5
				else if (msg->wParam == 0x35)
				{
					msg->message = WM_NULL;
					if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
					{
						SendMessage(cmd_msg, WM_COMMAND, 0x155, NULL);
						return 1;
					}
					else if (GetAsyncKeyState(VK_SHIFT))
					{
						return 1;
					}
					return 1;
				}
				// KEY 6
				else if (msg->wParam == 0x36)
				{
					msg->message = WM_NULL;
					return 1;
				}
				// KEY 7
				else if (msg->wParam == 0x37)
				{
					msg->message = WM_NULL;
					SendMessage(cmd_msg, WM_COMMAND, 0x5D, NULL);
					return 1;
				}
				// KEY 8
				else if (msg->wParam == 0x38)
				{
					msg->message = WM_NULL;
					SendMessage(cmd_msg, WM_COMMAND, 0x5E, NULL);
					return 1;
				}
				// KEY 9
				else if (msg->wParam == 0x39)
				{
					msg->message = WM_NULL;
					SendMessage(cmd_msg, WM_COMMAND, 0x5F, NULL);
					return 1;
				}
				// KEY 10
				else if (msg->wParam == 0x6B)
				{
					msg->message = WM_NULL;
					SendMessage(cmd_msg, WM_COMMAND, 0x3E, NULL);
					return 1;
				}
			}
			break;

		case WM_KEYUP:
			//printf("WM_KEYUP: %p, wParam: %i, lParam: %p\n", msg->hwnd, msg->wParam, msg->lParam);
			if (cmd_msg)
			{
				// KEY 1
				if (msg->wParam == 0x31)
				{
					msg->message = WM_NULL;
					SendMouseKeyRelease(VK_RSHIFT, MOUSEEVENTF_LEFTUP);
					return 1;
				}
				// KEY 2
				else if (msg->wParam == 0x32)
				{
					msg->message = WM_NULL;
					SendMouseKeyRelease(VK_RSHIFT, MOUSEEVENTF_RIGHTUP);
					return 1;
				}
				// KEY 3
				else if (msg->wParam == 0x33)
				{
					msg->message = WM_NULL;
					SendMessage(cmd_msg, WM_COMMAND, 0x121, NULL);
					//SendMessage(msg->hwnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(p.x, p.y));
					return 1;
				}

			}
			break;
		}
	}
	return CallNextHookEx(NULL, code, wParam, lParam);
}