#pragma once
#include "Common.h"
#include "SignPanelClass.h"
#include "CertsPanelClass.h"
#include "VerifyPanelClass.h"
#include "ConfigClass.h"

class ICPApp: public wxApp {
protected:
	wxWindow *theWindow;
	wxFrame *theFrame;
	// SignPanelClass *sign_panel;
	// CertsPanelClass *certs_panel;
	// VerifyPanelClass *verify_panel;
	bool LoadUI(wxString path);
public:
	bool OnInit();
	void PreExit();
	void OnClose(wxCloseEvent& event);
	ICPApp();
	~ICPApp();
};