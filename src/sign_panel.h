#include "common.h"
#include <wx/event.h>
#include <sstream>

class SignPanelClass {
protected:
	wxFrame *frame;
	wxFileDialog *file_dialog;
	wxArrayString *files_to_sign;
	wxButton *btnFileToSign;
	wxTextCtrl *inpFileToSign;
public:
	void Init(wxFrame *frame);
	void OpenFileDialog(wxCommandEvent& event);
	~SignPanelClass();
};
