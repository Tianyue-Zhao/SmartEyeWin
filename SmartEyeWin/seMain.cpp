#include "seMain.h"
#include "se_set.h"
#include "se_scan.h"
#include <thread>
#include <chrono>

wxBEGIN_EVENT_TABLE(seMain, wxFrame)
	//EVT_BUTTON(10001, setLow)
	EVT_CLOSE(seMain::OnClose)
wxEND_EVENT_TABLE()

seMain::seMain() : wxFrame(nullptr, wxID_ANY, "Title", wxPoint(50, 50), wxSize(800, 600))
{
	//testbtn = new wxButton(this, 10001, "TestBTN", wxPoint(30, 30), wxSize(50,50));
	const wxString test[1] = { wxString::FromAscii("test") };
	//wxWidgets allows actions when the thread updates
	Bind(wxEVT_THREAD, &seMain::OnThreadUpdate, this);
	brightTOT = (std::string**)malloc(11*sizeof(std::string*));
	brightTOT[0] = new std::string("Blender");
	brightTOT[1] = new std::string("Console");
	brightTOT[2] = new std::string("Discord");
	brightTOT[3] = new std::string("Elite");
	brightTOT[4] = new std::string("Epic");
	brightTOT[5] = new std::string("Firefox");
	brightTOT[6] = new std::string("Notepad");
	brightTOT[7] = new std::string("PyCharm");
	brightTOT[8] = new std::string("Snipping Tool");
	brightTOT[9] = new std::string("Steam");
	brightTOT[10] = new std::string("Visual Studio");
	brightLen = 11;
	brightKWK = scanWindows();
	//Initialize the main list
	//Start the checker thread
	//This checks the current foreground window
	start_checker();
}

//Memory is freed in OnClose
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
		HWND handle = GetForegroundWindow();
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
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	free(title_buffer);
	return (wxThread::ExitCode)0;
}

void seMain::OnClose(wxCloseEvent&)
{
	if ((GetThread()) && (GetThread()->IsRunning())) { GetThread()->Wait(); }
	ReleaseDC(NULL, main_context);
	delete testbtn;
	Destroy();
}

void seMain::OnThreadUpdate(wxThreadEvent& evt)
{
}

std::string** seMain::scanWindows()
{
	std::vector<std::string>* window_list = window_scan();
	brightKW->clear();
	int i;
	int len = window_list->size();
	auto begin = window_list->begin();
	auto end = window_list->end();
	for (;begin != end;begin++)
	{
		if (!(*begin).length()) { continue; }
		for (i = 0;i < brightLen;i++)
		{
			//TODO Make sure duplicates are not repeated
			if ((*begin).find(*(brightTOT[i])) != std::string::npos)
			{
				brightKW->push_back(*(brightTOT[i]));
			}
		}
	}
	len = brightKW->size();
	for (i = 0;i < len;i++)
	{
		choices[i] = wxString((*brightKW)[i]);
	}
	//Two-step creation of the checklistbox
	brightSel = new wxCheckListBox();
	brightSel->Create(this, 10002, wxPoint(10, 10), wxSize(100, 200), len, choices, 0);
}