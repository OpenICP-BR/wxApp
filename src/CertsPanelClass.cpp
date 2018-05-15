#include "CertsPanelClass.h"

void CertsPanelClass::Init(wxFrame *the_frame) {
	frame = the_frame;
	hack_disable_wiz_evt = false;

	// Get some stuff
	wizAddCert = (wxWizard*) wxXmlResource::Get()->LoadObject(NULL, "wizAddCert", "wxWizard");
	wpAddCertLoc = XRCCTRL(*wizAddCert, "wpAddCertLoc", wxWizardPage);
	btnAddCert = XRCCTRL(*frame, "btnAddCert", wxButton);
	btnFirstCert = XRCCTRL(*frame, "btnFirstCert", wxButton);
	fpCertFile = XRCCTRL(*wizAddCert, "fpCertFile", wxFilePickerCtrl);
	inpCertPass = XRCCTRL(*wizAddCert, "inpCertPass", wxTextCtrl);
	panelCertsFirst = XRCCTRL(*frame, "panelCertsFirst", wxPanel);
	panelCertsList = XRCCTRL(*frame, "panelCertsList", wxPanel);
	listCerts = XRCCTRL(*frame, "listCerts", wxListBox);

	updateCerts();

	// Bind events
	btnAddCert->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
        &CertsPanelClass::OpenAddCertDialog, this);
	btnFirstCert->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
        &CertsPanelClass::OpenAddCertDialog, this);
	wizAddCert->Bind(wxEVT_WIZARD_PAGE_CHANGING,
		&CertsPanelClass::OnWizPageChanging, this);
}

void CertsPanelClass::updateCerts() {
	// Fix which panel to show
	if (Config.GetUserCerts().size() == 0) {
		panelCertsFirst->Show();
		panelCertsList->Hide();
	} else {
		panelCertsFirst->Hide();
		panelCertsList->Show();
	}

	// Fix certs list
	listCerts->Clear();
	// wxArrayString l;
	for (auto &cert : Config.GetUserCerts()) {
		// l.Add(cert.Subject.CommonName());
		listCerts->Append(cert.Subject.CommonName());
	}
}

void CertsPanelClass::OpenAddCertDialog(wxCommandEvent& WXUNUSED(event)) {
	// Clean stuff
	inpCertPass->SetValue("");

	// Yes, this code is weird, but simply running RunWizard will fail if the page has not changed due to an assert at the begining of said method.
	if (wizAddCert->GetCurrentPage() == NULL) {
		cout << "CertsPanelClass::OpenAddCertDialog - IF1" << endl;
		hack_disable_wiz_evt = false;
		wizAddCert->RunWizard(wpAddCertLoc);
	} else if (wizAddCert->GetCurrentPage()->GetName() != wpAddCertLoc->GetName()) {
		cout << "CertsPanelClass::OpenAddCertDialog - IF2" << endl;
		hack_disable_wiz_evt = true;
		wizAddCert->RunWizard(wpAddCertLoc);
	} else {
		cout << "CertsPanelClass::OpenAddCertDialog - IF3" << endl;
		hack_disable_wiz_evt = false;
		wizAddCert->Show();
	}
}

void CertsPanelClass::PreExit() {
	printf("CertsPanelClass::PreExit\n");
	wizAddCert->Destroy();
}

CertsPanelClass::~CertsPanelClass() {
}

void CertsPanelClass::OnWizPageChanging(wxWizardEvent& event) {
	// Horibble hack
	if (hack_disable_wiz_evt) {
		cout << "CertsPanelClass::OnWizPageChanging: Skipping due to hack_disable_wiz_evt" << endl;
		hack_disable_wiz_evt = false;
		return;
	}

	// Process event
	cout << "Page pointer: " << event.GetPage() << endl;
	wxString p_name = event.GetPage()->GetName();
	cout << "Changing from: " << p_name << endl;
	bool ok = true;
	if (p_name == "wpAddCertLoc") {
		ok = LoadCert(fpCertFile->GetPath());
	}
	if (p_name == "wpAddCertPass") {
		ok = UnlockCert(inpCertPass->GetValue());
	}
	if (p_name == "wpAddCertInfo") {
		ok = ShowCertInfo();
	}
	if (!ok) {
	 	event.Veto();
	}
}

bool CertsPanelClass::LoadCert(wxString cert_path) {
	int err_code = new_cert.LoadFromFile(cert_path);
	if (err_code == OK) {
		return true;
	} else if (err_code == 1) {
		wxMessageBox(wxT("Falha ao abrir o arquivo .p12/.pfx"), wxT("Erro"), wxICON_ERROR|wxOK);
	} else if (err_code == 2) {
		wxMessageBox(wxT("Falha ao decodificar o arquivo .p12/.pfx"), wxT("Erro"), wxICON_ERROR|wxOK);
	} else if (err_code == 3) {
		wxMessageBox(wxT("Falha ao alocar memória"), wxT("Erro"), wxICON_ERROR|wxOK);
	}
	return false;
}

bool CertsPanelClass::UnlockCert(wxString pass) {
	cout << "CertsPanelClass::UnlockCert: Unlocking certificate" << endl;
	int err_code = new_cert.Unlock(pass);
	if (err_code == OK) {
		cout << "Updating cert info" << endl;
		XRCCTRL(*wizAddCert, "outCertName", wxStaticText)->SetLabel(new_cert.Subject().CommonName());
		XRCCTRL(*wizAddCert, "outCertEmail", wxStaticText)->SetLabel(new_cert.Subject().Email());
		XRCCTRL(*wizAddCert, "outCertCPF", wxStaticText)->SetLabel(new_cert.Subject().DocID());
		XRCCTRL(*wizAddCert, "outCertAC", wxStaticText)->SetLabel(new_cert.Issuer().CommonName());
		XRCCTRL(*wizAddCert, "outCertNotBefore", wxStaticText)->SetLabel(new_cert.NotBeforeString());
		XRCCTRL(*wizAddCert, "outCertNotAfter", wxStaticText)->SetLabel(new_cert.NotAfterString());
		return true;
	} else if (err_code == 1) {
		wxMessageBox(wxT("Arquivo .p12 não foi carregado"), wxT("Erro"), wxICON_ERROR|wxOK);
		return false;
	} else if (err_code == 2) {
		wxMessageBox(wxT("Senha errada para o arquivo .p12"), wxT("Erro"), wxICON_ERROR|wxOK);
		return false;
	} else if (err_code == 3) {
		wxMessageBox(wxT("Falha ao processar o arquivo .p12"), wxT("Erro"), wxICON_ERROR|wxOK);
		return false;
	} else if (err_code == 4) {
		wxMessageBox(wxT("Falha ao alocar memória"), wxT("Erro"), wxICON_ERROR|wxOK);
		return false;
	}
	return false;
}

bool CertsPanelClass::ShowCertInfo() {
	int error_int, error_depth;
	wxString error_string;
	CertClass error_cert;

	if (CAStore.Verify(new_cert.Cert(), error_int, error_string, error_depth, error_cert) == false) {
		wxString msg = wxT("Certificado inválido. Motivo: ");
		msg += error_string;
		wxMessageBox(msg, wxT("Erro"), wxICON_ERROR|wxOK);
		return false;
	}
	if ((Config.AddCert(new_cert) && Config.AddPKCS12(new_cert)) == FALSE) {
		wxMessageBox(wxT("Falha ao salvar certificado."), wxT("Erro"), wxICON_ERROR|wxOK);
		return false;
	} else {
		updateCerts();
		return true;
	}
}