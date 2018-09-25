#pragma once
#include "Common.h"
#include "ConfigClass.h"
#include <wx/notebook.h>

class SignPanelView {
protected:
	wxFrame *frame;
	wxFileDialog *file_dialog;
	wxButton *btnSign, *btnFileToSign;
	wxTextCtrl *inpFileToSign, *inpCertSignerPass;
	wxChoice *choSignAs;
	unsigned int last_n_certs;
	void updateCerts();
public:
	void Init(wxFrame *frame);
	void OpenFileDialog(wxCommandEvent& event);
	void OnPageChanged(wxBookCtrlEvent& event);
	void SignFiles(wxCommandEvent& event);
	wxArrayString& FilesToSign();
	SignPanelView();
	~SignPanelView();
};
