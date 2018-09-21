#include "ICPApp.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/filefn.h>
#include <wx/cmdline.h>
#include <wx/colour.h>
#include "icon-32.xpm"

wxIMPLEMENT_APP(ICPApp);

bool ICPApp::OnInit() {
	wxString ui_path;
	wxString executable_dir = wxStandardPaths::Get().GetExecutablePath().BeforeLast(wxFileName::GetPathSeparator()) + wxFileName::GetPathSeparator();
	wxLogDebug("executable_dir = %s", executable_dir);

	// Load basic config
	Config.Init();
	Config.ReloadCerts();

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
	theFrame->SetIcon(wxIcon(xpm_icon_32));
	if (theFrame != NULL) {
		#ifndef USE_FAKE_ICP_ROOT
			XRCCTRL(*theFrame, "lblTestVersion", wxStaticText)->Hide();
		#endif

		// Process some things
		sign_panel->Init(theFrame);
		verify_panel->Init(theFrame);
		certs_panel->Init(theFrame);
		theFrame->Bind(wxEVT_CLOSE_WINDOW, &ICPApp::OnClose, this);
		// Show it
		theFrame->Show(true);
	}

	// Set version strings
	XRCCTRL(*theFrame, "outOpenICPVer", wxStaticText)->SetLabel(OpenICP_Version);
	// XRCCTRL(*theFrame, "outOpenSSLVer", wxStaticText)->SetLabel(SSLeay_version(SSLEAY_VERSION));
	XRCCTRL(*theFrame, "outWxVer", wxStaticText)->SetLabel(wxGetLibraryVersionInfo().GetVersionString());

	// Some UI tweeks
	#ifdef __WXMSW__
		wxColour bg = XRCCTRL(*theFrame, "panelSign", wxPanel)->GetBackgroundColour();
		theFrame->SetBackgroundColour(bg);
		theFrame->Refresh();
		XRCCTRL(*theFrame, "panelCerts", wxPanel)->Fit();
	#endif

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
	verify_panel = new VerifyPanelClass();
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
	free(verify_panel);
	free(certs_panel);
}
