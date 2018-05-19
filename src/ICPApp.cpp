#include "ICPApp.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <wx/filefn.h>
#include <wx/cmdline.h>
#include "CertClass.h"

wxIMPLEMENT_APP(ICPApp);

bool ICPApp::OnInit() {
	wxString ui_path;
	wxString executable_dir = wxStandardPaths::Get().GetExecutablePath().BeforeLast(wxFileName::GetPathSeparator()) + wxFileName::GetPathSeparator();
	wxLogDebug("executable_dir = %s", executable_dir);

	// Load basic config
	Config.Init();
	CAStore.AddAllCAsFromDir("./res/CAs/");
	CAStore.AddAllCAsFromDir(executable_dir+"/../Resources/CAs/");
	CAStore.AddAllCAsFromDir("/usr/share/openicpbr/CAs/");
	CAStore.AddAllCAsFromDir("/usr/local/openicpbr/CAs/");
	CAStore.AddAllCAsFromDir(Config.CAsPath());
	Config.ReloadCerts();

	// Load OpenSSL
	OPENSSL_add_all_algorithms_noconf();
	ERR_load_crypto_strings();
	OpenSSL_add_all_ciphers();

	// Load UI
	wxXmlResource::Get()->InitAllHandlers();
	LoadUI(executable_dir + "../Resources/ui.xrc");
	LoadUI(wxGetCwd()+"/res/ui.xrc");
	LoadUI("/usr/share/openicpbr/ui.xrc");
	LoadUI("/usr/local/openicpbr/ui.xrc");
	LoadUI("/usr/local/share/openicpbr/ui.xrc");

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

	// return this->wxAppConsole->OnInit();
	return wxAppConsole::OnInit();
}

bool ICPApp::LoadUI(wxString path) {
	wxLogDebug("wxFileExists(\"%s\") = %d", path, wxFileExists(path));
	if (wxFileExists(path)) {
		wxLogDebug("Loading %s", path);
		wxXmlResource::Get()->Load(path);
		return true;
	}
	return false;
}

ICPApp::ICPApp () {
	sign_panel = new SignPanelClass();
	certs_panel = new CertsPanelClass();
	#ifdef USE_FAKE_ICP_ROOT
	cout << "WARNING: Using FAKE ICP root certificate. DO NOT USE IN PRODUCTION!!!" << endl;
	#endif
	printf("OpenICP version: %s\n", OpenICP_Version);
	printf("OpenICP version major: %d\n", OpenICP_Version_Major);
	printf("OpenICP version minor: %d\n", OpenICP_Version_Minor);
	printf("OpenICP version patch: %d\n", OpenICP_Version_Patch);
	printf("OpenICP version suffix: %s\n", OpenICP_Version_Suffix);
}

void ICPApp::PreExit () {
	printf("ICPApp::PreExit\n");
	certs_panel->PreExit();
}

void ICPApp::OnClose(wxCloseEvent& WXUNUSED(event)) {
	PreExit();
	theFrame->Destroy();
}

void ICPApp::OnInitCmdLine(wxCmdLineParser& parser) {
	parser.AddSwitch("V", "version",  "Prints the OpenICP current version");
	// must refuse '/' as parameter starter or cannot use "/path" style paths
	parser.SetSwitchChars("-");
}

bool ICPApp::OnCmdLineParsed(wxCmdLineParser& parser) {
	bool print_version = parser.Found("V");
	if (print_version) {
		printf("OpenICP version: %s\n", OpenICP_Version);
		ExitMainLoop();
	}
	return true;
}

ICPApp::~ICPApp () {
	printf("~ICPApp\n");
	free(sign_panel);
	free(certs_panel);
}
