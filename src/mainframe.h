#pragma once

#include "common.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/filepicker.h>
#include <wx/choice.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/hyperlink.h>
#include <wx/notebook.h>
#include <wx/frame.h>

class MainFrame : public wxFrame 
{
	private:
	protected:
		wxNotebook* nbMain;
		wxPanel* panelSign;
		wxStaticText* lblFileToSign;
		wxFilePickerCtrl* fpFileToSign;
		wxStaticText* lblSignAs;
		wxChoice* choSignAs;
		wxStaticText* lblSignatureType;
		wxRadioButton* rbtnSignTwoFiles;
		wxRadioButton* rbtnSignOneFile;
		wxButton* btnSign;
		wxPanel* panelVerify;
		wxStaticText* lblSignatureFile;
		wxFilePickerCtrl* fpSignatureFile;
		wxStaticText* lblMainFile;
		wxFilePickerCtrl* fpMainFile;
		wxPanel* panelFirstCert;
		wxButton* btnInstallFirstCert;
		wxHyperlinkCtrl* linkGetCertificate;
		wxPanel* panelHelp;
		wxSize minSizePanelSign;
		wxSize minSizePanelVerify;
		wxSize minSizePanelFirstCert;
		wxSize minSizePanelHelp;
	public:
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OpenICPBr"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		void OnChangedPanel(wxBookCtrlEvent& event);
		void OnChangedPanelCore();
		~MainFrame();
};