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
	ConfigClass Config;
public:
    virtual bool OnInit();
    void PreExit();
    void OnClose(wxCloseEvent& WXUNUSED(event));
    ICPApp();
    ~ICPApp();
};