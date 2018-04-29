#include "main.h"

wxIMPLEMENT_APP(ICPApp);

bool ICPApp::OnInit() {
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load("src/ui.xrc");

    // Get out frame
    wxFrame *frame = wxXmlResource::Get()->LoadFrame(this->GetTopWindow(), "MainFrame");
    if (frame != NULL) {
    	// Process some things
    	sign_panel->Init(frame);
    	certs_panel->Init(frame);
    	// Show it
        frame->Show(true);
    }
    return true;
}

ICPApp::ICPApp () {
	sign_panel = new SignPanelClass();
	certs_panel = new CertsPanelClass();
}

ICPApp::~ICPApp () {
	free(sign_panel);
	free(certs_panel);
}