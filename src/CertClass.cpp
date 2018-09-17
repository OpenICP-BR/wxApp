#include "CertClass.h"

CertClass::CertClass() {
}

CertClass::CertClass(icp_cert new_cert) {
	LoadCert(new_cert);
}

CertClass::~CertClass() {
}

icp_cert CertClass::_get_raw() {
	return cert;
}

wxString CertClass::NiceName() {
	return Subject;
}

wxString CertClass::NotBeforeString() {
	return NotBefore.FormatDate();
}

wxString CertClass::NotAfterString() {
	return NotAfter.FormatDate();
}

wxString CertClass::FingerPrintSHA256_HumanReadable() {
	return fp_sha_256_human;
}

wxString CertClass::FingerPrintSHA256_FileFriendly() {
	return fp_sha_256_fs;
}

bool CertClass::LoadPEMFile(char path[]) {
	icp_cert *certs;
	icp_errc *errcs;
	
	icp_new_cert_from_file(path, &certs, &errcs);
	for (int i=0; errcs[i] != NULL; i++) {
		wxLogDebug("CertClass::LoadPEMFile(%s) %s", path, icp_errc_code_str(errcs[i]));
	}
	if (certs[0] == NULL) {
		return false;
	}
	return LoadCert(certs[0]);
}

bool CertClass::LoadPEMString(char data[]) {	
	icp_cert *certs;
	icp_errc *errcs;
	
	icp_new_cert_from_bytes((uint8_t*) data, strlen(data), &certs, &errcs);
	for (int i=0; errcs[i] != NULL; i++) {
		wxLogDebug("CertClass::LoadPEMString %s", icp_errc_code_str(errcs[i]));
	}
	icp_free_errcs(errcs);
	if (certs[0] == NULL) {
		return false;
	}
	return LoadCert(certs[0]);
}

bool CertClass::LoadCert(icp_cert new_cert) {
	icp_kvp *kvps, kvp;
	if (new_cert == NULL) {
		return false;
	}

	cert = new_cert;

	Subject = wxString::FromUTF8(icp_cert_subject(cert));
	Issuer = wxString::FromUTF8(icp_cert_issuer(cert));

	kvps = icp_cert_issuer_map(cert);
	SubjectMap.clear();
	for (int i=0; kvps[i].key != NULL; i++) {
		kvp = kvps[i];
		SubjectMap[wxString::FromUTF8(kvp.key)] = wxString::FromUTF8(kvp.val);
	}
	icp_free_kvps(kvps);
	kvps = icp_cert_issuer_map(cert);
	IssuerMap.clear();
	for (int i=0; kvps[i].key != NULL; i++) {
		kvp = kvps[i];
		IssuerMap[wxString::FromUTF8(kvp.key)] = wxString::FromUTF8(kvp.val);
	}
	icp_free_kvps(kvps);

	// Get dates
	NotBefore.Set((time_t) icp_cert_not_before(cert));
	NotAfter.Set((time_t) icp_cert_not_after(cert));

	return true;
}
