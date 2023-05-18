#include <Windows.h>
#include <iostream>

int wmain(int argc, wchar_t* argv[], wchar_t* envp[]) {
	wchar_t* dllPath = argv[1];
	//ShellExecute(NULL, L"open", L"C:\\Program Files (x86)\\Image-Line\\FL Studio 21\\FL64.exe", NULL, NULL, SW_SHOWDEFAULT);
	Sleep(3000);
	if (GetFileAttributes(dllPath) == INVALID_FILE_ATTRIBUTES) {
		std::cout << "[ FAILED ] DLL file does not exist." << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// FL Studio window class name
	HWND hwnd = FindWindowW(L"TFruityLoopsMainForm", NULL); 
	if (hwnd == NULL) {
		std::cout << "[ FAILED ] Could not find target window." << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Getting the thread of the window and the PID
	DWORD pid = NULL;
	DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
	if (tid == NULL) {
		std::cout << "[ FAILED ] Could not get thread ID of the target window." << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Loading DLL
	HMODULE dll = LoadLibraryEx(dllPath, NULL, DONT_RESOLVE_DLL_REFERENCES); //Loading dll from params
	if (dll == NULL) {
		std::cout << "[ FAILED ] The DLL could not be found." << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Getting exported function address
	HOOKPROC addr = (HOOKPROC)GetProcAddress(dll, "NextHook"); //export see dllmain.cpp "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam)
	if (addr == NULL) {
		std::cout << "[ FAILED ] The function was not found." << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Setting the hook in the hook chain
	HHOOK handle = SetWindowsHookEx(WH_GETMESSAGE, addr, dll, tid); // Or WH_KEYBOARD if you prefer to trigger the hook manually
	if (handle == NULL) {
		std::cout << "[ FAILED ] Couldn't set the hook with SetWindowsHookEx." << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Triggering the hook
	PostThreadMessage(tid, WM_NULL, NULL, NULL);

	// Waiting for user input to remove the hook
	std::cout << "[ OK ] Hook set and triggered." << std::endl;
	std::cout << "[ >> ] Press any key to unhook (This will unload the DLL)." << std::endl;
	system("pause > nul");

	// Unhooking
	BOOL unhook = UnhookWindowsHookEx(handle);
	if (unhook == FALSE) {
		std::cout << "[ FAILED ] Could not remove the hook." << std::endl;
		system("pause");
		return EXIT_FAILURE;
	}

	std::cout << "[ OK ] Done. Press any key to exit." << std::endl;
	system("pause > nul");
	return EXIT_SUCCESS;
}
