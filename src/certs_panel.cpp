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
	wizAddCert->Bind(wxEVT_WIZARD_PAGE_CHANGING,
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

//https://stackoverflow.com/questions/6371775/how-to-load-a-pkcs12-file-in-openssl-programmatically?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa

void CertsPanelClass::OnWizPageChanging(wxWizardEvent& event) {
	wxString p_name = event.GetPage()->GetName();
	std::cout << "Changing from: " << p_name << std::endl;
	bool ok = true;
	if (p_name == "wpAddCertLoc") {
		ok = LoadCert(fpCertFile->GetPath());
	}
	if (!ok) {
	 	event.Veto();
	}
}

void CertsPanelClass::PreExit() {
	printf("CertsPanelClass::PreExit\n");
	wizAddCert->Destroy();
}

CertsPanelClass::~CertsPanelClass() {
}