#pragma once
#include "Common.h"
#include <wx/filename.h>
#include "CertClass.h"
#include "PKCS12Class.h"
#include "CAStoreClass.h"

class ConfigClass {
protected:
	wxFileName config_dir, certs_path, cas_path;
	map<wxString, CertClass> user_certs;
public:
	ConfigClass();
	void Init();
	void ReloadCerts();
	wxString CAsPath();
	bool Save();
	bool AddCert(CertClass cert);
	bool AddCert(PKCS12Class p12);
	bool AddPKCS12(PKCS12Class p12);
	map<wxString, CertClass> &GetUserCerts();
	PKCS12Class* GetPKCS12(wxString subject_hash, wxString password);
	~ConfigClass();
};

extern ConfigClass Config;