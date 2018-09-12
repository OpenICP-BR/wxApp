#include "ICPApp.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/filefn.h>
#include <wx/cmdline.h>
#include <wx/colour.h>
#include "icon-32.xpm"

wxDECLARE_APP(ICPApp);

bool ICPApp::OnInit() {
	wxString ui_path;
	wxString executable_dir = wxStandardPaths::Get().GetExecutablePath().BeforeLast(wxFileName::GetPathSeparator()) + wxFileName::GetPathSeparator();
	wxLogDebug("executable_dir = %s", executable_dir);

	// Load UI
	wxXmlResource::Get()->InitAllHandlers();
	LoadUI(executable_dir + "../Resources/ui.xrc");
	LoadUI(wxGetCwd()+"/res/ui.xrc");
	LoadUI(wxGetCwd()+"/../	res/ui.xrc");
	LoadUI("/usr/share/openicpbr/ui.xrc");
	LoadUI("/usr/local/openicpbr/ui.xrc");
	LoadUI("/usr/local/share/openicpbr/ui.xrc");

	// Get window and frame
	theWindow = this->GetTopWindow();
	theFrame = wxXmlResource::Get()->LoadFrame(theWindow, "MainFrame");
	theFrame->SetIcon(wxIcon(xpm_icon_32));
	XRCCTRL(*theFrame, "outOpenICPVer", wxStaticText)->SetLabel(OpenICP_Version);
	XRCCTRL(*theFrame, "outLibICPVer", wxStaticText)->SetLabel(LibICP_Version);
	XRCCTRL(*theFrame, "outWxVer", wxStaticText)->SetLabel(wxGetLibraryVersionInfo().GetVersionString());
	if (theFrame != NULL) {
		// Process some things
		theFrame->Bind(wxEVT_CLOSE_WINDOW, &ICPApp::OnClose, this);
		// Show it
		theFrame->Show(true);
	}

	// Prepare macOS menu
	#ifdef __WXOSX_COCOA__
	wxMenuBar* menubar = new wxMenuBar();
	theFrame->SetMenuBar(menubar);
	theFrame->Show();
	#endif

	return wxAppConsole::OnInit();
}

bool ICPApp::LoadUI(wxString path) {
	if (uiLoaded) {
		return true;
	}
	wxLogDebug("wxFileExists(\"%s\") = %d", path, wxFileExists(path));
	if (wxFileExists(path)) {
		wxLogDebug("Loading %s", path);
		wxXmlResource::Get()->Load(path);
		uiLoaded = true;
		return true;
	}
	return false;
}

ICPApp::ICPApp () {
	uiLoaded = false;
}

void ICPApp::PreExit () {
	printf("ICPApp::PreExit\n");
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
		printf("OpenICP version: ?\n");
		ExitMainLoop();
		PreExit();
		theFrame->Destroy();
	}
	return true;
}

ICPApp::~ICPApp () {
	printf("~ICPApp\n");
}

ICPApp& wxGetApp() {
	return *static_cast<ICPApp*>(wxAppConsole::GetInstance());
}

wxAppConsole *wxCreateApp() {
	return new ICPApp;
}

wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) wxCreateApp);
