#pragma once
#include "Common.h"
#include "SignPanelClass.h"
#include "CertsPanelClass.h"

class ICPApp: public wxApp {
protected:
	wxWindow *theWindow;
	wxFrame *theFrame;
	SignPanelClass *sign_panel;
	CertsPanelClass *certs_panel;
public:
    virtual bool OnInit();
    void PreExit();
    void OnClose(wxCloseEvent& WXUNUSED(event));
    ICPApp();
    ~ICPApp();
};