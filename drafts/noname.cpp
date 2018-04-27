///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Apr 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "noname.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxSize( -1,-1 ) );
	
	wxBoxSizer* sizerMain;
	sizerMain = new wxBoxSizer( wxVERTICAL );
	
	nbMain = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0|wxHSCROLL|wxVSCROLL );
	panelSign = new wxPanel( nbMain, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxHSCROLL|wxTAB_TRAVERSAL|wxVSCROLL );
	wxBoxSizer* sizerSign1;
	sizerSign1 = new wxBoxSizer( wxVERTICAL );
	
	wxGridSizer* sizerSign2;
	sizerSign2 = new wxGridSizer( 0, 2, 0, 0 );
	
	lblFileToSign = new wxStaticText( panelSign, wxID_ANY, wxT("Arquivo(s) para assinar:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblFileToSign->Wrap( -1 );
	sizerSign2->Add( lblFileToSign, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fpFileToSign = new wxFilePickerCtrl( panelSign, wxID_ANY, wxEmptyString, wxT("Qual arquvio assinar?"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	sizerSign2->Add( fpFileToSign, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	lblSignAs = new wxStaticText( panelSign, wxID_ANY, wxT("Assinar como:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSignAs->Wrap( -1 );
	sizerSign2->Add( lblSignAs, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxArrayString choSignAsChoices;
	choSignAs = new wxChoice( panelSign, wxID_ANY, wxDefaultPosition, wxDefaultSize, choSignAsChoices, 0 );
	choSignAs->SetSelection( 0 );
	sizerSign2->Add( choSignAs, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	lblSignatureType = new wxStaticText( panelSign, wxID_ANY, wxT("Assinatura e conteúdo:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSignatureType->Wrap( -1 );
	sizerSign2->Add( lblSignatureType, 0, wxALL, 5 );
	
	rbtnSignTwoFile = new wxRadioButton( panelSign, wxID_ANY, wxT("Em arquivos diferentes (.p7s)"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSign2->Add( rbtnSignTwoFile, 0, wxALL, 5 );
	
	
	sizerSign2->Add( 0, 0, 1, wxEXPAND, 5 );
	
	rbtnSignOneFile = new wxRadioButton( panelSign, wxID_ANY, wxT("No mesmo arquivo (.p7m)"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSign2->Add( rbtnSignOneFile, 0, wxALL, 5 );
	
	
	sizerSign1->Add( sizerSign2, 1, wxEXPAND, 5 );
	
	btnSign = new wxButton( panelSign, wxID_ANY, wxT("Assinar"), wxDefaultPosition, wxDefaultSize, 0 );
	btnSign->SetDefault(); 
	sizerSign1->Add( btnSign, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	panelSign->SetSizer( sizerSign1 );
	panelSign->Layout();
	sizerSign1->Fit( panelSign );
	nbMain->AddPage( panelSign, wxT("Assinar"), false );
	panelVerify = new wxPanel( nbMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxGridSizer* sizerVerify;
	sizerVerify = new wxGridSizer( 0, 2, 0, 0 );
	
	lblSignatureFile = new wxStaticText( panelVerify, wxID_ANY, wxT("Arquivo de assinatura (.p7m ou .p7s):"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSignatureFile->Wrap( -1 );
	sizerVerify->Add( lblSignatureFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fpSignatureFile = new wxFilePickerCtrl( panelVerify, wxID_ANY, wxEmptyString, wxT("Arquivo de assiantura"), wxT("*.p7m,*.p7s"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	sizerVerify->Add( fpSignatureFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	lblMainFile = new wxStaticText( panelVerify, wxID_ANY, wxT("Arquivo de conteúdo:"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMainFile->Wrap( -1 );
	lblMainFile->Hide();
	
	sizerVerify->Add( lblMainFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fpMainFile = new wxFilePickerCtrl( panelVerify, wxID_ANY, wxEmptyString, wxT("Conteúdo assinado"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	fpMainFile->Hide();
	
	sizerVerify->Add( fpMainFile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	sizerVerify->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	panelVerify->SetSizer( sizerVerify );
	panelVerify->Layout();
	sizerVerify->Fit( panelVerify );
	nbMain->AddPage( panelVerify, wxT("Verificar"), false );
	panelFirstCert = new wxPanel( nbMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* sizerCerts;
	sizerCerts = new wxBoxSizer( wxVERTICAL );
	
	
	sizerCerts->Add( 0, 0, 1, wxEXPAND, 5 );
	
	btnInstallFirstCert = new wxButton( panelFirstCert, wxID_ANY, wxT("Instalar certificado"), wxDefaultPosition, wxDefaultSize, 0 );
	btnInstallFirstCert->SetDefault(); 
	sizerCerts->Add( btnInstallFirstCert, 0, wxALIGN_CENTER|wxALIGN_CENTER_VERTICAL|wxALL|wxTOP, 5 );
	
	linkGetCertificate = new wxHyperlinkCtrl( panelFirstCert, wxID_ANY, wxT("Onde consigo um?"), wxT("http://www.iti.gov.br/certificado-digital/58-certificado-digital/87-como-obter"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	sizerCerts->Add( linkGetCertificate, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	sizerCerts->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	panelFirstCert->SetSizer( sizerCerts );
	panelFirstCert->Layout();
	sizerCerts->Fit( panelFirstCert );
	nbMain->AddPage( panelFirstCert, wxT("Certificados Digitais"), false );
	panelHelp = new wxPanel( nbMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	nbMain->AddPage( panelHelp, wxT("Ajuda"), false );
	
	sizerMain->Add( nbMain, 1, wxALL|wxEXPAND, 5 );
	
	
	this->SetSizer( sizerMain );
	this->Layout();
	sizerMain->Fit( this );
	
	this->Centre( wxBOTH );
}

MainFrame::~MainFrame()
{
}

MyFrame2::MyFrame2( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	
	this->Centre( wxBOTH );
}

MyFrame2::~MyFrame2()
{
}

MyWizard1::MyWizard1( wxWindow* parent, wxWindowID id, const wxString& title, const wxBitmap& bitmap, const wxPoint& pos, long style ) 
{
	this->Create( parent, id, title, bitmap, pos, style );
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxWizardPageSimple* wizNewCertFind = new wxWizardPageSimple( this );
	m_pages.Add( wizNewCertFind );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText6 = new wxStaticText( wizNewCertFind, wxID_ANY, wxT("Arquivo com o certificado A1 (.p12):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer12->Add( m_staticText6, 0, wxALL, 5 );
	
	m_filePicker4 = new wxFilePickerCtrl( wizNewCertFind, wxID_ANY, wxEmptyString, wxT("Certificado tipo A1"), wxT("*.p12"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer12->Add( m_filePicker4, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	wizNewCertFind->SetSizer( bSizer12 );
	wizNewCertFind->Layout();
	bSizer12->Fit( wizNewCertFind );
	wxWizardPageSimple* wizNewCertPassword = new wxWizardPageSimple( this );
	m_pages.Add( wizNewCertPassword );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( wizNewCertPassword, wxID_ANY, wxT("Informações do Certificado") ), wxVERTICAL );
	
	wxGridSizer* gSizer4;
	gSizer4 = new wxGridSizer( 0, 2, 0, 0 );
	
	m_staticText8 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Nome:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	gSizer4->Add( m_staticText8, 0, wxALL, 5 );
	
	m_staticText9 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	gSizer4->Add( m_staticText9, 0, wxALL, 5 );
	
	m_staticText16 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Email:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	gSizer4->Add( m_staticText16, 0, wxALL, 5 );
	
	m_staticText11 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	gSizer4->Add( m_staticText11, 0, wxALL, 5 );
	
	m_staticText10 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("CPF:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	gSizer4->Add( m_staticText10, 0, wxALL, 5 );
	
	m_staticText13 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	gSizer4->Add( m_staticText13, 0, wxALL, 5 );
	
	m_staticText14 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("Emissor:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	gSizer4->Add( m_staticText14, 0, wxALL, 5 );
	
	m_staticText17 = new wxStaticText( sbSizer2->GetStaticBox(), wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	gSizer4->Add( m_staticText17, 0, wxALL, 5 );
	
	
	sbSizer2->Add( gSizer4, 1, wxEXPAND, 5 );
	
	
	bSizer13->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	wxGridSizer* gSizer3;
	gSizer3 = new wxGridSizer( 1, 0, 0, 0 );
	
	m_staticText7 = new wxStaticText( wizNewCertPassword, wxID_ANY, wxT("Senha do certificado:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	gSizer3->Add( m_staticText7, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	m_textCtrl1 = new wxTextCtrl( wizNewCertPassword, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	bSizer15->Add( m_textCtrl1, 0, wxALL|wxEXPAND, 5 );
	
	
	gSizer3->Add( bSizer15, 1, wxEXPAND, 5 );
	
	
	bSizer13->Add( gSizer3, 1, wxEXPAND, 5 );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	wizNewCertPassword->SetSizer( bSizer13 );
	wizNewCertPassword->Layout();
	bSizer13->Fit( wizNewCertPassword );
	wxWizardPageSimple* wizNewCertEnd = new wxWizardPageSimple( this );
	m_pages.Add( wizNewCertEnd );
	
	
	this->Centre( wxBOTH );
	
	for ( unsigned int i = 1; i < m_pages.GetCount(); i++ )
	{
		m_pages.Item( i )->SetPrev( m_pages.Item( i - 1 ) );
		m_pages.Item( i - 1 )->SetNext( m_pages.Item( i ) );
	}
}

MyWizard1::~MyWizard1()
{
	m_pages.Clear();
}
