#include "certs_panel.h"

void CertsPanelClass::Init(wxFrame *the_frame) {
	frame = the_frame;

	// Get some stuff
	wizAddCert = (wxWizard*) wxXmlResource::Get()->LoadObject(NULL, "wizAddCert", "wxWizard");
	wpAddCertLoc = XRCCTRL(*wizAddCert, "wpAddCertLoc", wxWizardPage);
	btnAddCert = XRCCTRL(*frame, "btnAddCert", wxButton);
	btnFirstCert = XRCCTRL(*frame, "btnFirstCert", wxButton);
	fpCertFile = XRCCTRL(*wizAddCert, "fpCertFile", wxFilePickerCtrl);
	inpCertPass = XRCCTRL(*wizAddCert, "inpCertPass", wxTextCtrl);

	// Bind events
	btnAddCert->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
        &CertsPanelClass::OpenAddCertDialog, this);
	btnFirstCert->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
        &CertsPanelClass::OpenAddCertDialog, this);
	wizAddCert->Bind(wxEVT_WIZARD_PAGE_CHANGED,
		&CertsPanelClass::OnWizPageChanged, this);
	wizAddCert->Bind(wxEVT_WIZARD_PAGE_CHANGED,
		&CertsPanelClass::OnWizPageChanging, this);
}

void CertsPanelClass::OpenAddCertDialog(wxCommandEvent& WXUNUSED(event)) {
	// Yes, this code is weird, but simply running RunWizard will fail if the page has not changed due to an assert at the begining of said method.
	if (wizAddCert->GetCurrentPage() == NULL) {
		wizAddCert->RunWizard(wpAddCertLoc);
	} else if (wizAddCert->GetCurrentPage()->GetName() != wpAddCertLoc->GetName()) {
		wizAddCert->RunWizard(wpAddCertLoc);
	} else {
		wizAddCert->Show();
	}
}

void CertsPanelClass::OnWizPageChanged(wxWizardEvent& event) {
	std::cout << "Changed to: " << event.GetPage()->GetName() << std::endl;
}

void CertsPanelClass::OnWizPageChanging(wxWizardEvent& event) {
	std::cout << "Changing to: " << event.GetPage()->GetName() << std::endl;
}

void CertsPanelClass::PreExit() {
	printf("CertsPanelClass::PreExit\n");
	wizAddCert->Destroy();
}

CertsPanelClass::~CertsPanelClass() {
}