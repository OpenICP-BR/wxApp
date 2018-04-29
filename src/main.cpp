#include "main.h"

wxIMPLEMENT_APP(ICPApp);

bool ICPApp::OnInit() {
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load("src/ui.xrc");

    // Get window and frame
    theWindow = this->GetTopWindow();
    theFrame = wxXmlResource::Get()->LoadFrame(theWindow, "MainFrame");
    if (theFrame != NULL) {
    	// Process some things
    	sign_panel->Init(theFrame);
    	certs_panel->Init(theFrame);
    	theFrame->Bind(wxEVT_CLOSE_WINDOW, &ICPApp::OnClose, this);
    	// Show it
        theFrame->Show(true);
    }
    return true;
}

ICPApp::ICPApp () {
	sign_panel = new SignPanelClass();
	certs_panel = new CertsPanelClass();
}

void ICPApp::PreExit () {
	printf("ICPApp::PreExit\n");
	certs_panel->PreExit();
}

void ICPApp::OnClose(wxCloseEvent& WXUNUSED(event)) {
	PreExit();
	theFrame->Destroy();
}

ICPApp::~ICPApp () {
	printf("~ICPApp\n");
	free(sign_panel);
	free(certs_panel);
}