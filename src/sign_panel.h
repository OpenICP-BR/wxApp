#include "common.h"
#include <wx/event.h>

class SignPanelClass {
public:
	void AddEvents(wxFrame *frame);
	void OpenFileDialog(wxCommandEvent& event);
};
