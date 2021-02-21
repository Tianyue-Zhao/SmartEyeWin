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

	void start_checker();
	void OnThreadUpdate(wxThreadEvent& evt);
	void OnClose(wxCloseEvent&);

	//wxDECLARE_EVENT_TABLE();

protected:
	//false for bright, true for blue light filtering mode
	bool cur_lighting_state = true;
	std::vector<std::string>* brightKW = new std::vector<std::string>();
	HDC main_context = GetDC(NULL);
	virtual wxThread::ExitCode Entry();
};

