#include "SignPanelClass.h"
#include <sstream>

void SignPanelClass::Init(wxFrame *the_frame) {
	frame = the_frame;

	// Add some stuff
	files_to_sign = new wxArrayString();
	file_dialog = new wxFileDialog(frame, wxT("Escolha o arquivo para assinar"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);

	// Get some stuff
	btnFileToSign = XRCCTRL(*frame, "btnFileToSign", wxButton);
	inpFileToSign = XRCCTRL(*frame, "inpFileToSign", wxTextCtrl);
	choSignAs = XRCCTRL(*frame, "choSignAs", wxChoice);

	// Bind events
	btnFileToSign->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
        &SignPanelClass::OpenFileDialog, this);
	choSignAs->Bind(wxEVT_CHOICE,
		&SignPanelClass::OnSignAsClick, this);

	updateCerts();
}

void SignPanelClass::updateCerts() {
	// Fix certs list
	if (last_n_certs != Config.GetUserCerts().size()) {
		last_n_certs = Config.GetUserCerts().size();
		choSignAs->Clear();
		for (auto &pair : Config.GetUserCerts()) {
			choSignAs->Append(pair.first);
		}
	}
}

void SignPanelClass::OnSignAsClick(wxCommandEvent& WXUNUSED(event)) {
	updateCerts();
}

void SignPanelClass::OpenFileDialog(wxCommandEvent& WXUNUSED(event)) {
	int n;
	wxArrayString filenames;

	// Just a little hack
	updateCerts();

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