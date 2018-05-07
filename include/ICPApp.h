#pragma once
#include "Common.h"
#include "SignPanelClass.h"
#include "CertsPanelClass.h"
#include "CAStoreClass.h"

class ICPApp: public wxApp {
protected:
	wxWindow *theWindow;
	wxFrame *theFrame;
	SignPanelClass *sign_panel;
	CertsPanelClass *certs_panel;
	CAStoreClass CAs;
public:
    virtual bool OnInit();
    void PreExit();
    void OnClose(wxCloseEvent& WXUNUSED(event));
    ICPApp();
    ~ICPApp();
};