#include "SignPanelClass.h"
#include <sstream>
#include <wx/stdpaths.h>

void SignPanelClass::Init(wxFrame *the_frame) {
	frame = the_frame;

	// Add some stuff
	file_dialog = new wxFileDialog(frame, wxT("Escolha o arquivo para assinar"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_OPEN|wxFD_FILE_MUST_EXIST|wxFD_MULTIPLE);
	file_dialog->SetDirectory(wxStandardPaths::Get().GetDocumentsDir());

	// Get some stuff
	btnSign = XRCCTRL(*frame, "btnSign", wxButton);
	btnFileToSign = XRCCTRL(*frame, "btnFileToSign", wxButton);
	inpFileToSign = XRCCTRL(*frame, "inpFileToSign", wxTextCtrl);
	inpCertSignerPass = XRCCTRL(*frame, "inpCertSignerPass", wxTextCtrl);
	choSignAs = XRCCTRL(*frame, "choSignAs", wxChoice);

	// Bind events
	btnFileToSign->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&SignPanelClass::OpenFileDialog, this);
	btnSign->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&SignPanelClass::SignFiles, this);
	XRCCTRL(*frame, "nbMain", wxNotebook)->Bind(wxEVT_NOTEBOOK_PAGE_CHANGING,
		&SignPanelClass::OnPageChanged, this);

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

void SignPanelClass::OnPageChanged(wxBookCtrlEvent& WXUNUSED(event)) {
	updateCerts();
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
}

void SignPanelClass::SignFiles(wxCommandEvent& WXUNUSED(event)) {
	// Try to get and unlock certificate
	PKCS12Class *p12 = Config.GetPKCS12(choSignAs->GetStringSelection());
	if (p12 == NULL) {
		wxLogMessage(wxT("Certificado não encontrado :(\nTente readiconá-lo"));
		inpCertSignerPass->Clear();
		return;
	}
	int err_unlock = p12->Unlock(inpCertSignerPass->GetLineText(0));
	inpCertSignerPass->Clear();
	if (err_unlock == PKCS12_UNLOCK_ERR_WRONG_PASSWORD) {
		wxLogMessage(wxT("Senha incorreta"));
		return;
	} else if (err_unlock != OK) {
		wxLogMessage(wxT("Falha ao abrir o certificado digital"));
		return;
	}

	wxString err_msg;
	wxArrayString files_to_sign;
	map<wxString, wxString> files_and_status;
	// Get full paths
	file_dialog->GetPaths(files_to_sign);
	for (wxString &filename : files_to_sign) {
		p12->SignFile(filename, err_msg);
		files_and_status[filename] = err_msg;
	}
	wxString final_msg;
	for (auto &pair : files_and_status) {
		final_msg += pair.first+": "+pair.second+"\n";
	}
	wxLogMessage(final_msg);
	free(p12);
}

SignPanelClass::~SignPanelClass() {
	free(file_dialog);
}