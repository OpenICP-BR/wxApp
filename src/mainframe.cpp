#include "mainframe.h"

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style ) {
	
	// Basics
	wxBoxSizer* sizerMain;
	sizerMain = new wxBoxSizer( wxVERTICAL );
	nbMain = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	nbMain->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MainFrame::OnChangedPanel, this);

	// Sign panel
	panelSign = new wxPanel( nbMain, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
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
	
	wxBoxSizer* sizerSign3;
	sizerSign3 = new wxBoxSizer( wxVERTICAL );
	
	rbtnSignTwoFile = new wxRadioButton( panelSign, wxID_ANY, wxT("Em arquivos diferentes (.p7s) (recomendado)"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSign3->Add( rbtnSignTwoFile, 0, wxALL, 5 );
	
	rbtnSignOneFile = new wxRadioButton( panelSign, wxID_ANY, wxT("No mesmo arquivo (.p7m)"), wxDefaultPosition, wxDefaultSize, 0 );
	sizerSign3->Add( rbtnSignOneFile, 0, wxALL, 5 );
	
	
	sizerSign2->Add( sizerSign3, 1, wxEXPAND, 5 );
	
	
	sizerSign1->Add( sizerSign2, 1, wxEXPAND, 5 );
	
	btnSign = new wxButton( panelSign, wxID_ANY, wxT("Assinar"), wxDefaultPosition, wxDefaultSize, 0 );
	btnSign->SetDefault(); 
	sizerSign1->Add( btnSign, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	panelSign->SetSizer( sizerSign1 );
	panelSign->Layout();
	sizerSign1->Fit( panelSign );
	minSizePanelSign = panelSign->GetBestSize();
	nbMain->AddPage( panelSign, wxT("Assinar"), false );

	// Verify panel

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
	minSizePanelVerify = panelVerify->GetBestSize();

	// First cert panel
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

	// Help panel
	panelHelp = new wxPanel( nbMain, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	panelHelp->SetMinSize(panelHelp->GetBestSize());
	minSizePanelHelp = panelHelp->GetBestSize();
	nbMain->AddPage( panelHelp, wxT("Ajuda"), false );


	// Finish	
	sizerMain->Add( nbMain, 1, wxALL|wxEXPAND, 5 );
	sizerMain->Fit( this );
	this->SetSizer( sizerMain );
	this->Layout();
	this->Centre( wxBOTH );
	OnChangedPanelCore();
}

void MainFrame::OnChangedPanel(wxBookCtrlEvent& WXUNUSED(event)) {
	OnChangedPanelCore();
}


// Set the notebook to the propper size based on what pannel is on.
void MainFrame::OnChangedPanelCore() {
	wxSize size = nbMain->GetCurrentPage()->GetBestSize();
	size.SetHeight(NOTEBOOK_HEADER_HEIGHT+size.GetHeight());
	size.SetHeight(MAX(size.GetHeight(), MIN_NOTEBOOK_HEIGHT));
	size.SetWidth(MAX(size.GetWidth(), MIN_NOTEBOOK_WIDTH));
	this->SetMinSize(size);
	this->SetSize(size);
}

MainFrame::~MainFrame() {
}