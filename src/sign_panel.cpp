#include "sign_panel.h"

void SignPanelClass::Init(wxFrame *the_frame) {
	frame = the_frame;

	// Add some stuff
	files_to_sign = new wxArrayString();
	file_dialog = new wxFileDialog(frame, wxT("Escolha o arquivo para assinar"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);

	// Get some stuff
	btnFileToSign = XRCCTRL(*frame, "btnFileToSign", wxButton);
	inpFileToSign = XRCCTRL(*frame, "inpFileToSign", wxTextCtrl);

	// Bind events
	btnFileToSign->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
        &SignPanelClass::OpenFileDialog, this);
}

void SignPanelClass::OpenFileDialog(wxCommandEvent& WXUNUSED(event)) {
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
	inpFileToSign->Clear();
	if (n == 1) {
		*inpFileToSign << filenames[0];
	} else {
		*inpFileToSign << n << " arquivos";
	}

	// Store the full paths
	file_dialog->GetPaths(*files_to_sign);
}

SignPanelClass::~SignPanelClass() {
	free(file_dialog);
	free(files_to_sign);
}