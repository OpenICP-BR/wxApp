#pragma once
#include "Common.h"
#include "ConfigClass.h"
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
	wxPanel *panelCertsFirst, *panelCertsList;
	wxListBox *listCerts;
	bool hack_disable_wiz_evt;
public:
	void Init(wxFrame *frame);
	void updateCerts();
	void PreExit();
	void OpenAddCertDialog(wxCommandEvent& event);
	void OnWizPageChanging(wxWizardEvent& event);
	void OnCertsListClick(wxCommandEvent& event);
	bool LoadCert(wxString cert_path);
	bool UnlockCert(wxString pass);
	bool ShowCertInfo();
	~CertsPanelClass();
};
