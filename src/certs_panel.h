#include "common.h"
#include <wx/wizard.h>

class CertsPanelClass {
protected:
	wxFrame *frame;
	wxWizard *wizAddCert;
	wxButton *btnFirstCert, *btnAddCert;
public:
	void Init(wxFrame *frame);
	void OpenAddCertDialog(wxCommandEvent& event);
	~CertsPanelClass();
};
