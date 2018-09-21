#pragma once
#include "Common.h"
#include <wx/filename.h>

class ConfigClass {
protected:
	wxFileName config_dir, certs_path, cas_path;
public:
	ICP::CAStore Store;
	// Associate each "nice name" with the path to the PFX file.
	map<wxString, wxString> PFXs;
	ConfigClass();
	void Init();
	void ReloadCerts();
	bool AddPFX(ICP::PFX pfx);
	ICP::PFX* GetPFX(wxString nice_name);
	~ConfigClass();
};

extern ConfigClass Config;