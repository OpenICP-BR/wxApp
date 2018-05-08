#pragma once
#include "Common.h"
#include <wx/filename.h>
#include "CertClass.h"
#include "PKCS12Class.h"
#include "CAStoreClass.h"

class ConfigClass {
protected:
	wxFileName config_dir;
	vector<CertClass> *user_certs;
public:
	ConfigClass();
	wxString CAsPath();
	bool Save();
	bool Load(CAStoreClass &CAs);
	bool AddCert(CertClass cert);
	std::vector<CertClass>* GetUserCerts();
	PKCS12Class* GetPKCS12(wxString subject_hash, wxString password);
	~ConfigClass();
};