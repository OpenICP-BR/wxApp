#pragma once
#include "Common.h"
#include "ConfigClass.h"
#include <wx/filepicker.h>

class NewCertPanelView {
protected:
	wxFrame *frame;
	wxCheckBox *isRootCA;
	wxFilePickerCtrl *inIssuerFile;
	wxTextCtrl *inIssuerPass, *inName;
	wxString old_name_value;
	wxButton *btnAddRootCA, *btnGenCert;
public:
	void Init(wxFrame *frame);
	void SignFiles(wxCommandEvent& event);
	wxArrayString& FilesToSign();
	void onAddRootCA(wxCommandEvent& event);
	void onRootCAChange(wxCommandEvent& event);
	NewCertPanelView();
	~NewCertPanelView();
};
