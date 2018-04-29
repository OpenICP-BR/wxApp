#include "certs_panel.h"

void CertsPanelClass::Init(wxFrame *the_frame) {
	frame = the_frame;

	// Get some stuff
	wizAddCert = XRCCTRL(*frame, "wizAddCert", wxWizard);
	btnAddCert = XRCCTRL(*frame, "btnAddCert", wxButton);
	btnFirstCert = XRCCTRL(*frame, "btnFirstCert", wxButton);

	// Bind events
	btnFirstCert->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
        &CertsPanelClass::OpenAddCertDialog, this);
}

void CertsPanelClass::OpenAddCertDialog(wxCommandEvent& WXUNUSED(event)) {
	wizAddCert->ShowModal();
}

CertsPanelClass::~CertsPanelClass() {
}