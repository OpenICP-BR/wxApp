#include "ICPApp.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "CertClass.h"

wxIMPLEMENT_APP(ICPApp);

bool ICPApp::OnInit() {
	// Load basic config
	CAs.AddAllCAsFromDir("./cas/");
	Config.Load(CAs);

	// Load OpenSSL
	OPENSSL_add_all_algorithms_noconf();
	ERR_load_crypto_strings();
	OpenSSL_add_all_ciphers();

	// Load UI
	cout << "Loading: " << wxGetCwd()+"/ui.xrc" << endl;
	wxXmlResource::Get()->InitAllHandlers();
	wxXmlResource::Get()->Load(wxGetCwd()+"/ui.xrc");

	// Get window and frame
	theWindow = this->GetTopWindow();
	theFrame = wxXmlResource::Get()->LoadFrame(theWindow, "MainFrame");
	if (theFrame != NULL) {
		#ifndef USE_FAKE_ICP_ROOT
			XRCCTRL(*theFrame, "lblTestVersion", wxStaticText)->Hide();
		#endif

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
	#ifdef USE_FAKE_ICP_ROOT
	cout << "WARNING: Using FAKE ICP root certificate. DO NOT USE IN PRODUCTION!!!" << endl;
	#endif
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
