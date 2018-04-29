#pragma once

#include "common.h"
#include "sign_panel.h"
#include "certs_panel.h"

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