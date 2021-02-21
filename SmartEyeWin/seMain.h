#pragma once

#include <wx/wx.h>
#include <wx/thread.h>
#include <vector>
#include <string>

class seMain : public wxFrame, public wxThreadHelper
{
public:
	seMain();
	~seMain();

	wxButton* testbtn = nullptr;
	wxCheckListBox* brightSel = nullptr;

	void start_checker();
	void OnThreadUpdate(wxThreadEvent& evt);
	void OnClose(wxCloseEvent&);

	wxDECLARE_EVENT_TABLE();

protected:
	//false for bright, true for blue light filtering mode
	bool cur_lighting_state = false;
	std::vector<std::string>* brightKW = new std::vector<std::string>();
	std::string** brightTOT = nullptr;
	int brightLen = 0;
	wxString choices[11];
	HDC main_context = GetDC(NULL);
	void scanWindows();
	virtual wxThread::ExitCode Entry();
};

