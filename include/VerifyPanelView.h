#pragma once
#include "Common.h"
#include "ConfigClass.h"
#include <wx/notebook.h>

class VerifyPanelView {
protected:
	wxFrame *frame;
	wxFileDialog *file_dialog;
	wxButton *btnFileToVerify;
	wxTextCtrl *inpFileToVerify;
public:
	void Init(wxFrame *frame);
	void OpenFileDialog(wxCommandEvent& event);
	void VerifyFiles();
	VerifyPanelView();
	~VerifyPanelView();
};
