#include "common.h"
#include <wx/wizard.h>

class CertsPanelClass {
protected:
	wxFrame *frame;
	wxWizard *wizAddCert;
	wxWizardPage *wpAddCert1;
	wxButton *btnFirstCert, *btnAddCert;
public:
	void Init(wxFrame *frame);
	void PreExit();
	void OpenAddCertDialog(wxCommandEvent& event);
	~CertsPanelClass();
};
