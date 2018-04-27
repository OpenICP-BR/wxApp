#include "sign_panel.h"
#include <stdio.h>

void SignPanelClass::AddEvents(wxFrame *frame) {
	XRCCTRL(*frame, "btnFileToSign", wxButton)->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
        &SignPanelClass::OpenFileDialog, this);
}

void SignPanelClass::OpenFileDialog(wxCommandEvent& event) {
	printf("hi2\n");
}