#include "ConfigClass.h"
#include <wx/stdpaths.h>

ConfigClass::ConfigClass() {
	config_dir = wxStandardPaths::Get().GetUserDataDir();
	config_dir.MakeAbsolute();
}

wxString ConfigClass::CAsPath() {
	return "";
}

bool ConfigClass::Save() {
	return false;
}

bool ConfigClass::Load(CAStoreClass &CAs) {
	cout << "Loding config stuff on " << config_dir.GetPath() << " and creating subdirectories" << endl;
	if (!config_dir.DirExists()) {
		config_dir.Mkdir();
	}
	wxFileName certs_path = wxFileName(config_dir);
	wxFileName cas_path = wxFileName(config_dir);

	certs_path.AppendDir("certs");
	cas_path.AppendDir("CAs");
	if (!certs_path.DirExists()) {
		certs_path.Mkdir();
	}
	if (!cas_path.DirExists()) {
		cas_path.Mkdir();
	}

	return CAs.AddAllCAsFromDir(cas_path.GetPath());
}

bool ConfigClass::AddCert(CertClass cert) {
	return false;
}

vector<CertClass>* ConfigClass::GetUserCerts() {
	return NULL;
}

PKCS12Class* ConfigClass::GetPKCS12(wxString subject_hash, wxString password) {
	return NULL;
}

ConfigClass::~ConfigClass() {
}
