#include "certs_panel.h"

void CertsPanelClass::Init(wxFrame *the_frame) {
	frame = the_frame;

	// Get some stuff
	wizAddCert = (wxWizard*) wxXmlResource::Get()->LoadObject(NULL, "wizAddCert", "wxWizard");
	wpAddCert1 = XRCCTRL(*wizAddCert, "wpAddCert1", wxWizardPage);
	btnAddCert = XRCCTRL(*frame, "btnAddCert", wxButton);
	btnFirstCert = XRCCTRL(*frame, "btnFirstCert", wxButton);

	// Bind events
	btnAddCert->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
        &CertsPanelClass::OpenAddCertDialog, this);
	btnFirstCert->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
        &CertsPanelClass::OpenAddCertDialog, this);
}

void CertsPanelClass::OpenAddCertDialog(wxCommandEvent& WXUNUSED(event)) {
	// Yes, this code is weird, but simply running RunWizard will fail if the page has not changed due to an assert at the begining of said method.
	if (wizAddCert->GetCurrentPage() == NULL) {
		wizAddCert->RunWizard(wpAddCert1);
	} else if (wizAddCert->GetCurrentPage()->GetName() != wpAddCert1->GetName()) {
		wizAddCert->RunWizard(wpAddCert1);
	} else {
		wizAddCert->Show();
	}
}

void CertsPanelClass::PreExit() {
	printf("CertsPanelClass::PreExit\n");
	wizAddCert->Destroy();
}

CertsPanelClass::~CertsPanelClass() {
}