#include "ConfigClass.h"
#include <wx/stdpaths.h>
#include <wx/dir.h>

ConfigClass Config;

ConfigClass::ConfigClass() {
}

void ConfigClass::Init() {
	config_dir = wxStandardPaths::Get().GetUserDataDir();
	config_dir.SetFullName("");
	config_dir.MakeAbsolute();

	if (!config_dir.DirExists()) {
		config_dir.Mkdir();
	}
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
}

void ConfigClass::ReloadCerts() {
	int total_counter=0;
	wxString filename, dir_path;

	// Open dir
	dir_path = certs_path.GetPathWithSep();
	wxLogDebug("Loading all certs from %s", dir_path);
	wxDir dir(dir_path);
	user_certs.clear();
	
	// For each file...
	bool cont = dir.GetFirst(&filename);
	while (cont) {
		CertClass cert;
		wxString full_path = dir.GetNameWithSep()+filename;
		// ... check the file extension
		if (full_path.Right(4) != ".pem") {
			wxLogDebug("Skiping %s", full_path);
			cont = dir.GetNext(&filename);
			continue;
		}
		// ... try to read it
		if (!cert.LoadPEMFile(full_path)) {
			wxLogDebug("Invalid cert on %s", full_path);
		}
		// ... and verify if it is a valid certificate
		if (CAStore.Verify(cert)) {
			total_counter++;
			wxLogDebug("Added cert for %s on %s", cert.Subject.CommonName(), full_path);
			user_certs[cert.NiceName()] = cert;
		} else {
			wxLogDebug("Invalid cert for %s on %s", cert.Subject.CommonName(), full_path);
		}
		cont = dir.GetNext(&filename);
	}
	wxLogDebug("Finished loading %d certs from: %s", total_counter, dir.GetName());
}

wxString ConfigClass::CAsPath() {
	return cas_path.GetPathWithSep();
}

bool ConfigClass::Save() {
	return false;
}

bool ConfigClass::AddCert(CertClass cert) {
	bool b = cert.SaveCert(certs_path.GetPathWithSep());
	if (b) {
		wxLogDebug("Adding cert for %s to the current certs list.", cert.NiceName());
		user_certs[cert.NiceName()] = cert;
	}
	return b;
}

bool ConfigClass::AddCert(PKCS12Class p12) {
	return AddCert(p12.Cert());
}

bool ConfigClass::AddPKCS12(PKCS12Class p12) {
	return p12.SaveEncryptedP12(certs_path.GetPathWithSep());
}

map<wxString, CertClass> &ConfigClass::GetUserCerts() {
	return user_certs;
}

PKCS12Class* ConfigClass::GetPKCS12(wxString subject_hash, wxString password) {
	return NULL;
}

ConfigClass::~ConfigClass() {
}
