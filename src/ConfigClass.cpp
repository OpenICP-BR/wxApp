#include "ConfigClass.h"
#include <wx/stdpaths.h>

ConfigClass Config;

ConfigClass::ConfigClass() {
}

void ConfigClass::Init() {
	config_dir = wxStandardPaths::Get().GetUserDataDir();
	config_dir.MakeAbsolute();

	if (!config_dir.DirExists()) {
		config_dir.Mkdir();
	}
	certs_path = wxFileName(config_dir);
	cas_path = wxFileName(config_dir);

	certs_path.AppendDir("certs");
	cas_path.AppendDir("CAs");
	if (!certs_path.DirExists()) {
		certs_path.Mkdir();
	}
	if (!cas_path.DirExists()) {
		cas_path.Mkdir();
	}
}


wxString ConfigClass::CAsPath() {
	return cas_path.GetPath();
}

bool ConfigClass::Save() {
	return false;
}

bool ConfigClass::AddCert(CertClass cert) {
	return cert.SaveCert(certs_path.GetPath());
}

bool ConfigClass::AddCert(PKCS12Class p12) {
	return p12.SaveKeylessCert(certs_path.GetPath());
}

bool ConfigClass::AddPKCS12(PKCS12Class p12) {
	return p12.SaveEncryptedP12(certs_path.GetPath());
}

vector<CertClass>* ConfigClass::GetUserCerts() {
	return NULL;
}

PKCS12Class* ConfigClass::GetPKCS12(wxString subject_hash, wxString password) {
	return NULL;
}

ConfigClass::~ConfigClass() {
}
