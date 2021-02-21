#include "seMain.h"
#include "se_set.h"

wxBEGIN_EVENT_TABLE(seMain, wxFrame)
	EVT_BUTTON(10001, setLow)
wxEND_EVENT_TABLE()

seMain::seMain() : wxFrame(nullptr, wxID_ANY, "Title", wxPoint(50,50), wxSize(800,600))
{
	testbtn = new wxButton(this, 10001, "TestBTN", wxPoint(10, 10), wxSize(10,10));
}

seMain::~seMain()
{
}

void seMain::setLow(wxCommandEvent& evt)
{
	HDC main_context = GetDC(NULL);
	set_gamma(256, 256, 256, main_context);
	evt.Skip();
}