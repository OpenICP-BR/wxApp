#include "common.h"
#include "pkcs12_class.h"
#include <wx/wizard.h>
#include <wx/filepicker.h>

class CertsPanelClass {
protected:
	wxFrame *frame;
	wxWizard *wizAddCert;
	wxWizardPage *wpAddCertLoc;
	wxButton *btnFirstCert, *btnAddCert;
	wxFilePickerCtrl *fpCertFile;
	wxTextCtrl *inpCertPass;
	PKCS12Class new_cert;
	bool hack_disable_wiz_evt;
public:
	void Init(wxFrame *frame);
	void PreExit();
	void OpenAddCertDialog(wxCommandEvent& event);
	void OnWizPageChanging(wxWizardEvent& event);
	bool LoadCert(wxString cert_path);
	bool UnlockCert(wxString pass);
	bool ShowCertInfo();
	~CertsPanelClass();
};
