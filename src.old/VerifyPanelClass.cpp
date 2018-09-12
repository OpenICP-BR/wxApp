#include "VerifyPanelClass.h"
#include <wx/stdpaths.h>

void VerifyPanelClass::Init(wxFrame *the_frame) {
	frame = the_frame;

	// Add some stuff
	file_dialog = new wxFileDialog(frame, wxT("Escolha o arquivo para verificar"), wxEmptyString, wxEmptyString, "*.p7s", wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);
	file_dialog->SetDirectory(wxStandardPaths::Get().GetDocumentsDir());

	// Get some stuff
	btnFileToVerify = XRCCTRL(*frame, "btnFileToVerify", wxButton);
	inpFileToVerify = XRCCTRL(*frame, "inpFileToVerify", wxTextCtrl);

	// Bind events
	btnFileToVerify->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&VerifyPanelClass::OpenFileDialog, this);
}

void VerifyPanelClass::OpenFileDialog(wxCommandEvent& WXUNUSED(event)) {
	int n;
	wxArrayString filenames;

	// Show file dialog
	file_dialog->ShowModal();

	// How many files?
	file_dialog->GetFilenames(filenames);
	n = (int) filenames.GetCount();
	if (n == 0) {
		// Change nothing if the user hit cancel.
		return;
	}
	
	// Get filenames and show them for the user
	inpFileToVerify->Clear();
	if (n == 1) {
		*inpFileToVerify << filenames[0];
	} else {
		*inpFileToVerify << n << " arquivos";
	}

	VerifyFiles();
}

void VerifyPanelClass::VerifyFiles() {
	wxLogMessage(wxT("Não implementado"));
	return;
}

VerifyPanelClass::~VerifyPanelClass() {
	free(file_dialog);
}