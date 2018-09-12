#pragma once

#include "common.h"

class ICPApp: public wxApp {
protected:
	wxWindow *theWindow;
	wxFrame *theFrame;
	bool LoadUI(wxString path);
public:
	bool OnInit();
	// int  OnRun();
	void PreExit();
	void OnClose(wxCloseEvent& WXUNUSED(event));
	void OnInitCmdLine(wxCmdLineParser& parser);
	bool OnCmdLineParsed(wxCmdLineParser& parser);
	ICPApp();
	~ICPApp();
};