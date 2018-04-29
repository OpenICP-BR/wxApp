#pragma once

#include "common.h"
#include "sign_panel.h"
#include "certs_panel.h"

class ICPApp: public wxApp {
protected:
	SignPanelClass *sign_panel;
	CertsPanelClass *certs_panel;
public:
    virtual bool OnInit();
    ICPApp();
    ~ICPApp();
};