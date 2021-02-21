#include "seApp.h"

wxIMPLEMENT_APP(seApp);

seApp::seApp()
{
}

seApp::~seApp()
{
}

bool seApp::OnInit()
{
	mframe1 = new seMain();
	mframe1->Show();
	return true;
}
