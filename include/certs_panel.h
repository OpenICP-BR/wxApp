#include "common.h"
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
public:
	void Init(wxFrame *frame);
	void PreExit();
	void OpenAddCertDialog(wxCommandEvent& event);
	void OnWizPageChanging(wxWizardEvent& event);
	~CertsPanelClass();
};
