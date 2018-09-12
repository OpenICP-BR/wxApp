#pragma once

#include "common.h"

class ICPApp: public wxApp {
protected:
	wxWindow *theWindow;
	wxFrame *theFrame;
	bool uiLoaded;
	bool LoadUI(wxString path);
public:
	bool OnInit();
	void PreExit();
	void OnClose(wxCloseEvent& WXUNUSED(event));
	void OnInitCmdLine(wxCmdLineParser& parser);
	bool OnCmdLineParsed(wxCmdLineParser& parser);
	ICPApp();
	~ICPApp();
};