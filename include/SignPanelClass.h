#pragma once
#include "Common.h"
#include "ConfigClass.h"

class SignPanelClass {
protected:
	wxFrame *frame;
	wxFileDialog *file_dialog;
	wxArrayString *files_to_sign;
	wxButton *btnFileToSign;
	wxTextCtrl *inpFileToSign;
	wxChoice *choSignAs;
	int last_n_certs=0;
	void updateCerts();
public:
	void Init(wxFrame *frame);
	void OpenFileDialog(wxCommandEvent& event);
	void OnSignAsClick(wxCommandEvent& event);
	~SignPanelClass();
};
