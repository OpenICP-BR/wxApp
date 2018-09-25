#pragma once
#include "Common.h"
#include "SignPanelView.h"
#include "NewCertPanelView.h"
// #include "CertsPanelView.h"
// #include "VerifyPanelView.h"
#include "ConfigClass.h"

class ICPApp: public wxApp {
protected:
	wxWindow *theWindow;
	wxFrame *theFrame;
	SignPanelView *sign_panel;
	NewCertPanelView *new_cert_panel;
	// CertsPanelView *certs_panel;
	// VerifyPanelView *verify_panel;
	bool LoadUI(wxString path);
public:
	bool OnInit();
	void PreExit();
	void OnClose(wxCloseEvent& event);
	ICPApp();
	~ICPApp();
};
