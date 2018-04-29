#include "common.h"
#include <wx/wizard.h>
#include <wx/filepicker.h>
#include <openssl/pkcs12.h>

class CertsPanelClass {
protected:
	wxFrame *frame;
	wxWizard *wizAddCert;
	wxWizardPage *wpAddCertLoc;
	wxButton *btnFirstCert, *btnAddCert;
	wxFilePickerCtrl *fpCertFile;
	wxTextCtrl *inpCertPass;
	PKCS12 *new_p12;
	X509 *new_cert;
	STACK_OF(X509) *new_ca = NULL;
	EVP_PKEY *new_key_pair;
public:
	void Init(wxFrame *frame);
	void PreExit();
	void OpenAddCertDialog(wxCommandEvent& event);
	void OnWizPageChanging(wxWizardEvent& event);
	bool LoadCert(wxString cert_path);
	bool UnlockCert(wxString pass);
	~CertsPanelClass();
};
