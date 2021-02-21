#include <windows.h>
#include <winuser.h>
#include <string>
#include <vector>

bool window_log_cb(HWND handle, LPARAM window_list)
{
	char* window_title = (char*)malloc(100 * sizeof(char));
	if (!window_title) { return false; }
	GetWindowTextA(handle, window_title, 100);
	((std::vector<std::string>*)window_list)->push_back(window_title);
	free(window_title);
	return true;
}

std::vector<std::string>* window_scan()
{
	//Assembles a list of currently running windows
	std::vector<std::string>* window_list = new std::vector<std::string>(); //Pass callback as parameter
	EnumWindows((WNDENUMPROC)&window_log_cb, (LPARAM)window_list); //Cast pointer as LPARAM, both 32-bit
	return window_list;
}