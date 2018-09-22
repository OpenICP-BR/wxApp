#include "ConfigClass.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>

ConfigClass *Config=NULL;

ConfigClass::ConfigClass() {
	Store.SetDebug(false);
	Store.SetAutoDownload(true);
}

void ConfigClass::Init() {
	config_dir = wxStandardPaths::Get().GetUserDataDir();
	config_dir.SetFullName("");
	config_dir.MakeAbsolute();
	if (!config_dir.DirExists()) {
		config_dir.Mkdir();
	}
	
	#ifdef __linux__
	config_dir.AppendDir(".config");
	if (!config_dir.DirExists()) {
		config_dir.Mkdir();
	}
	#endif //__linux__

	config_dir.AppendDir("OpenICP");
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

	wxLogDebug("Config Path: %s", config_dir.GetPathWithSep());
	wxLogDebug("Certs Path: %s", certs_path.GetPathWithSep());
	wxLogDebug("CAs Path: %s", cas_path.GetPathWithSep());

	// Load CAs
	wxString cas_path_std = cas_path.GetPathWithSep().ToStdString();
	Store.AddAllCAsFromDirParallel(cas_path_std.ToStdString());
	Store.SetCachePath(cas_path_std.ToStdString());
}

void ConfigClass::ReloadCerts() {
	int total_counter=0;
	wxString filename, dir_path;

	// Open dir
	dir_path = certs_path.GetPathWithSep();
	wxLogDebug("Loading all certs from %s", dir_path);
	
	wxDir dir(dir_path);
	PFXs.clear();
	
	// For each file...
	bool cont = dir.GetFirst(&filename);
	while (cont) {
		wxString full_path = dir.GetNameWithSep()+filename;
		// ... check for a certificate with key
		if (full_path.Right(4) != ".pfx") {
			cont = dir.GetNext(&filename);
			continue;
		}
		// Do we have the public certificate?
		wxString cert_full_path = full_path.Truncate(full_path.Len()-3)+"crt";
		if (!wxFileExists(cert_full_path)) {
			wxLogDebug("Skiping %s (no public certificate found)", full_path);
			cont = dir.GetNext(&filename);
			continue;
		}

		// Load certificate
		vector<Cert> certs;
		vector<CodedError> errs;
		LoadCertsFromFile(cert_full_path.ToStdString(), certs, errs);
		if (certs.size() == 0) {
			cont = dir.GetNext(&filename);
			continue;
		}
		wxLogDebug("%s", certs[0].Subject);

		// Check validity


		// // ... try to read it
		// if (!cert.LoadPEMFile(full_path)) {
		// 	wxLogDebug("Invalid cert on %s", full_path);
		// }
		// // ... and verify if it is a valid certificate
		// if (CAStore.Verify(cert)) {
		// 	total_counter++;
		// 	wxLogDebug("Added cert for %s on %s", cert.Subject.CommonName(), full_path);
		// 	user_certs[cert.NiceName()] = cert;
		// } else {
		// 	wxLogDebug("Invalid cert for %s on %s", cert.Subject.CommonName(), full_path);
		// }
		cont = dir.GetNext(&filename);
	}
	wxLogDebug("Finished loading %d certs from: %s", total_counter, dir.GetName());
}

bool ConfigClass::AddPFX(PFX WXUNUSED(pfx)) {
	// save the pfx and cert as two files to the certs dir
	ReloadCerts();
	return false;
}

PFX* ConfigClass::GetPFX(wxString WXUNUSED(nice_name)) {
	// if (user_certs.find(nice_name) == user_certs.end()) {
	// 	return NULL;
	// }
	// wxString fp = user_certs[nice_name].FingerPrintSHA256_FileFriendly();
	// wxFileName fname = certs_path.GetPathWithSep();
	// fname.SetFullName(fp+".p12");
	// PKCS12Class *p12 = new PKCS12Class();
	// if (p12->LoadFromFile(fname.GetFullPath()) == OK) {
	// 	return p12;
	// } else {
	// 	return NULL;
	// }
	return NULL;
}

ConfigClass::~ConfigClass() {
}
