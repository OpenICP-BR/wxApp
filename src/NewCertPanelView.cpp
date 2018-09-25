#include "NewCertPanelView.h"
#include <sstream>
#include <wx/stdpaths.h>
#include <wx/gdicmn.h>

NewCertPanelView::NewCertPanelView() {
}

void NewCertPanelView::Init(wxFrame *the_frame) {
	frame = the_frame;

	// Get some stuff
	isRootCA = XRCCTRL(*frame, "inNewCertRootCA", wxCheckBox);
	inIssuerFile = XRCCTRL(*frame, "inNewCertIssuer", wxFilePickerCtrl);
	inIssuerPass = XRCCTRL(*frame, "inNewCertIssuerPassword", wxTextCtrl);
	inName = XRCCTRL(*frame, "inNewCertName", wxTextCtrl);
	// inpFileToSign = XRCCTRL(*frame, "inpFileToSign", wxTextCtrl);
	// inpCertSignerPass = XRCCTRL(*frame, "inpCertSignerPass", wxTextCtrl);
	btnAddRootCA = XRCCTRL(*frame, "btnAddRootCA", wxButton);
	btnGenCert = XRCCTRL(*frame, "btnGenCert", wxButton);

	// Bind events
	isRootCA->Bind(wxEVT_CHECKBOX,
		&NewCertPanelView::onRootCAChange, this);
	btnAddRootCA->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
		&NewCertPanelView::onAddRootCA, this);
	// XRCCTRL(*frame, "nbMain", wxNotebook)->Bind(wxEVT_NOTEBOOK_PAGE_CHANGING,
	// 	&NewCertPanelView::OnPageChanged, this);
}

void NewCertPanelView::onRootCAChange(wxCommandEvent& WXUNUSED(event)) {
	if (inIssuerPass->IsEnabled() || inIssuerFile->IsEnabled() || inName->IsEnabled()) {
		old_name_value = inName->GetValue();
		inName->Disable();
		inIssuerPass->Disable();
		inIssuerFile->Disable();
		inName->SetValue("Autoridade Certificadora Raiz de Testes - SEM VALOR LEGAL");
	} else {
		inName->Enable();
		inIssuerPass->Enable();
		inIssuerFile->Enable();
		inName->SetValue(old_name_value);
	}
}

void NewCertPanelView::onAddRootCA(wxCommandEvent& WXUNUSED(event)) {
	if (!XRCCTRL(*frame, "lblTestVersion", wxStaticText)->IsShown()) {
		XRCCTRL(*frame, "lblTestVersion", wxStaticText)->Show();
		wxSize size = frame->GetSize();
		size.IncBy(0, 32);
		frame->SetSize(size);
	}
}

NewCertPanelView::~NewCertPanelView() {
}
