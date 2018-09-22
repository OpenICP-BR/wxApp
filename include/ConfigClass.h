#pragma once
#include "Common.h"
#include <wx/filename.h>

class ConfigClass {
protected:
	wxFileName config_dir, certs_path, cas_path;
public:
	CAStore Store;
	// Associate each "nice name" with the path to the PFX file.
	map<wxString, wxString> PFXs;
	map<wxString, Cert*> Certs;
	ConfigClass();
	void Init();
	void ReloadCerts();
	bool AddPFX(PFX pfx);
	PFX* GetPFX(wxString nice_name);
	void AddTestingRootCA(wxString path);
	~ConfigClass();
};

extern ConfigClass *Config;
