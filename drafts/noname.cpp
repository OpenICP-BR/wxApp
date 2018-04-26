///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 25 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel2 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* gSizer_SignPanel;
	gSizer_SignPanel = new wxGridSizer( 0, 2, 0, 0 );
	
	m_FileToSign = new wxStaticText( m_panel2, wxID_ANY, wxT("Arquivo para assinar:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_FileToSign->Wrap( -1 );
	gSizer_SignPanel->Add( m_FileToSign, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fpFileToSign = new wxFilePickerCtrl( m_panel2, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	gSizer_SignPanel->Add( fpFileToSign, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	lblSignAs = new wxStaticText( m_panel2, wxID_ANY, wxT("Assinar como:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSignAs->Wrap( -1 );
	gSizer_SignPanel->Add( lblSignAs, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxArrayString choSignAsChoices;
	choSignAs = new wxChoice( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, choSignAsChoices, 0 );
	choSignAs->SetSelection( 0 );
	gSizer_SignPanel->Add( choSignAs, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	m_panel2->SetSizer( gSizer_SignPanel );
	m_panel2->Layout();
	gSizer_SignPanel->Fit( m_panel2 );
	m_notebook1->AddPage( m_panel2, wxT("Assinar"), false );
	m_panel3 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook1->AddPage( m_panel3, wxT("Verificar"), false );
	m_panel4 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook1->AddPage( m_panel4, wxT("Certificados Digitais"), false );
	m_panel5 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_notebook1->AddPage( m_panel5, wxT("Ajuda"), false );
	
	bSizer1->Add( m_notebook1, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
}

MyFrame1::~MyFrame1()
{
}
