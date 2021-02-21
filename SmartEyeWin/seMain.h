#pragma once

#include <wx/wx.h>

class seMain : public wxFrame
{
public:
	seMain();
	~seMain();

	wxButton* testbtn = nullptr;

	void setLow(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

