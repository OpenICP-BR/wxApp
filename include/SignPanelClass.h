#pragma once
#include "Common.h"
#include "ConfigClass.h"
#include <wx/notebook.h>

class SignPanelClass {
protected:
	wxFrame *frame;
	wxFileDialog *file_dialog;
	wxButton *btnSign, *btnFileToSign;
	wxTextCtrl *inpFileToSign, *inpCertSignerPass;
	wxChoice *choSignAs;
	unsigned int last_n_certs=0;
	void updateCerts();
public:
	void Init(wxFrame *frame);
	void OpenFileDialog(wxCommandEvent& event);
	void OnPageChanged(wxBookCtrlEvent& event);
	void SignFiles(wxCommandEvent& event);
	~SignPanelClass();
};
