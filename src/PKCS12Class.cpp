#include "PKCS12Class.h"
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/pkcs12.h>

EntityInfoClass PKCS12Class::Subject() {
	return cert.Subject;
}

EntityInfoClass PKCS12Class::Issuer() {
	return cert.Issuer;
}

CertClass PKCS12Class::Cert() {
	return cert;
}

int PKCS12Class::LoadFromFile(wxString cert_path) {
	FILE *fptr;
	const char *c_path;

	cout << "Loading certificate: " << cert_path << endl;
	c_path = cert_path.mb_str();
	fptr = fopen(c_path, "r");
	if (fptr == NULL) {
		cout << "PKCS12Class::LoadFromFile - Failed to open file " << cert_path << endl;
		return 1;
	}
	p12 = d2i_PKCS12_fp(fptr, NULL);
	fclose(fptr);
	if (p12 == NULL) {
		cout << "PKCS12Class::LoadFromFile - Failed to decode file " << cert_path << endl;
		return 2;
	}

	return OK;
}

void PKCS12Class::SetPassword(wxString pass) {
	password = pass;
}

int PKCS12Class::Unlock(wxString pass) {
	const char *c_pass = pass.mb_str();
	int len = pass.Len();
	X509 *x509_cert;

	if (p12 == NULL) {
		cout << "PKCS12Class::Unlock: .p12 file was not loaded" << endl;
		return 1; // Wrong password
	}
	if (!PKCS12_verify_mac(p12, c_pass, len)) {
		cout << "PKCS12Class::Unlock: Wrong password" << endl;
		return 2; // Wrong password
	}
	if (!PKCS12_parse(p12, c_pass, &key_pair, &x509_cert, &ca_stack)) {
		cout << "PKCS12Class::Unlock: Failed to parse" << endl;
		return 3; // Failed to parse
	}

	cert.LoadCert(x509_cert);
	SetPassword(pass);
	return OK;
}

bool PKCS12Class::SaveKeylessCert(wxString dir) {
	return cert.SaveCert(dir);
}

bool PKCS12Class::SaveEncryptedP12(wxString dir) {
	// Get path
	wxFileName path = dir;
	path.SetFullName(cert.FingerPrintSHA256_FileFriendly() + ".pkcs12");
	wxLogDebug("Saving pkcs12 to %s", path.GetFullPath());

	// Open file
	FILE *file = fopen(path.GetFullPath().c_str(), "w");
	if (file == NULL) {
		wxLogDebug("Failed to open file for writing: %s", path.GetFullPath());
		return false;
	}

	// Actually save stuff
	int bytes = i2d_PKCS12_fp(file, p12);
	if (bytes <= 0) {
		wxLogDebug("Failed to write one or more bytes: %s", path.GetFullPath());
		return false;
	}

	// Finish
	fclose(file);
	return true;
}

wxString PKCS12Class::NotBeforeString() {
	return cert.NotBeforeString();
}

wxString PKCS12Class::NotAfterString() {
	return cert.NotAfterString();
}

wxString PKCS12Class::FingerPrintSHA256_FileFriendly() {
	return cert.FingerPrintSHA256_FileFriendly();
}

wxString PKCS12Class::FingerPrintSHA256_HumanReadable() {
	return cert.FingerPrintSHA256_HumanReadable();
}

PKCS12Class::~PKCS12Class () {
}