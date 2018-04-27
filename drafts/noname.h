///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 25 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __NONAME_H__
#define __NONAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/radiobut.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/filepicker.h>
#include <wx/hyperlink.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/statbox.h>
#include <wx/textctrl.h>
#include <wx/wizard.h>
#include <wx/dynarray.h>
WX_DEFINE_ARRAY_PTR( wxWizardPageSimple*, WizardPages );

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame 
{
	private:
	
	protected:
		wxNotebook* nbMain;
		wxPanel* panelSign;
		wxStaticText* lblFileToSign;
		wxStaticText* lblFileChosenToSign;
		wxButton* btnFileToSign;
		wxStaticText* lblSignAs;
		wxChoice* choSignAs;
		wxStaticText* lblSignatureType;
		wxRadioButton* m_radioBtn5;
		wxRadioButton* m_radioBtn6;
		wxButton* btnSign;
		wxPanel* panelVerify;
		wxStaticText* lblSignatureFile;
		wxFilePickerCtrl* fpSignatureFile;
		wxStaticText* m_staticText5;
		wxFilePickerCtrl* m_filePicker3;
		wxPanel* panelFirstCert;
		wxButton* btnFirstCert;
		wxHyperlinkCtrl* linkGetCertificate;
		wxPanel* panelHelp;
		
		// Virtual event handlers, overide them in your derived class
		virtual void SignPanel_OpenFileDialog( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OpenICPBr"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~MainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MyWizard1
///////////////////////////////////////////////////////////////////////////////
class MyWizard1 : public wxWizard 
{
	private:
	
	protected:
		wxStaticText* m_staticText6;
		wxFilePickerCtrl* m_filePicker4;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText16;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText10;
		wxStaticText* m_staticText13;
		wxStaticText* m_staticText14;
		wxStaticText* m_staticText17;
		wxStaticText* m_staticText7;
		wxTextCtrl* m_textCtrl1;
	
	public:
		
		MyWizard1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Instalação de certificado digital"), const wxBitmap& bitmap = wxNullBitmap, const wxPoint& pos = wxDefaultPosition, long style = wxCAPTION|wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX|wxRESIZE_BORDER );
		WizardPages m_pages;
		~MyWizard1();
	
};

#endif //__NONAME_H__
