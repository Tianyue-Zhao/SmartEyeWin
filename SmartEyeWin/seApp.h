#pragma once

#include <wx/wx.h>
#include "seMain.h"

class seApp : public wxApp
{
public:
	seApp();
	~seApp();
	bool OnInit();
private:
	seMain* mframe1;
};

