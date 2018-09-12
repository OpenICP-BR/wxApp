#include "main-ui.h"
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
	if (theFrame != NULL) {
		// Process some things
		theFrame->Bind(wxEVT_CLOSE_WINDOW, &ICPApp::OnClose, this);
		// Show it
		theFrame->Show(true);
	}

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
	}
	return true;
}

ICPApp::~ICPApp () {
	printf("~ICPApp\n");
}

char** str_array_new(int n) {
	return (char**) malloc(n * sizeof(char *));
}

void str_array_set(char **v, int i, char *s) {
	v[i] = s;
}

void str_array_free(int n, char **v) {
	for (int i=0; i < n; i++) {
		free(v[i]);
	}
	free(v);
}

int start_app(int argc, char **argv) {
	printf("%d\n", argc);
	printf("%p\n", argv);
	printf("%s\n", argv[0]);
	printf("wxEntry(argc, argv)\n");
	return wxEntry(argc, argv);
}

ICPApp& wxGetApp() {
	return *static_cast<ICPApp*>(wxAppConsole::GetInstance());
}

wxAppConsole *wxCreateApp() {
	return new ICPApp;
}

wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction) wxCreateApp);

