#include "seMain.h"
#include "se_set.h"
#include "se_scan.h"
#include <thread>
#include <chrono>

/*wxBEGIN_EVENT_TABLE(seMain, wxFrame)
	EVT_BUTTON(10001, setLow)
wxEND_EVENT_TABLE()*/

seMain::seMain() : wxFrame(nullptr, wxID_ANY, "Title", wxPoint(50,50), wxSize(800,600))
{
	testbtn = new wxButton(this, 10001, "TestBTN", wxPoint(10, 10), wxSize(10,10));
}

seMain::~seMain()
{
}

void seMain::start_checker()
{
	if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
	{
		wxLogError("Error when creating the checker thread.");
		return;
	}
	GetThread()->Run();
}

wxThread::ExitCode seMain::Entry()
{
	char* title_buffer = (char*)malloc(200 * sizeof(char));
	bool flag;
	while (!GetThread()->TestDestroy())
	{
		auto begin = brightKW->begin();
		auto end = brightKW->end();
		HWND handle = GetActiveWindow();
		std::string window_title;
		GetWindowTextA(handle, title_buffer, 200);
		window_title.assign(title_buffer);
		flag = false;
		for (;begin != end;begin++)
		{
			if (window_title.find(*begin) != std::string::npos)
			{
				flag = true;
				if (cur_lighting_state)
				{
					set_gamma(256, 256, 256, main_context);
					cur_lighting_state = false;
				}
				break;
			}
		}
		if ((!flag) && (!cur_lighting_state))
		{
			set_gamma(192, 192, 144, main_context);
			cur_lighting_state = true;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	}
	free(title_buffer);
}