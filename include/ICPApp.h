#pragma once
#include "Common.h"
#include "SignPanelClass.h"
#include "CertsPanelClass.h"
#include "CAStoreClass.h"
#include "ConfigClass.h"

class ICPApp: public wxApp {
protected:
	wxWindow *theWindow;
	wxFrame *theFrame;
	SignPanelClass *sign_panel;
	CertsPanelClass *certs_panel;
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