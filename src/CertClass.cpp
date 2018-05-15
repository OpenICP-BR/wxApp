#include <time.h>
#include "CertClass.h"

X509* PEM2X509(const char data[]) {
	BIO *bmem;
	X509 *cert;

	bmem = BIO_new_mem_buf(data, -1);
	cert = PEM_read_bio_X509(bmem, NULL, NULL, NULL);
	if (cert == NULL) {
		printf("Failed to load certificate from PEM: %s\n", data);
		BIO_free(bmem);
		return NULL;
	}
	BIO_free(bmem);
	
	return cert;
}

X509* FILE2X509(const char path[]) {
	FILE *fp;
	X509 *cert;
	fp = fopen(path, "r");
	if (fp == NULL) {
		printf("Certificate not found: %s\n", path);
		return NULL;
	}
	cert = PEM_read_X509(fp, NULL, NULL, NULL);
	fclose(fp);
	if (cert == NULL) {
		printf("Failed to load certificate: %s\n", path);
		return NULL;
	}
	return cert;
}

CertClass::CertClass() {
}

CertClass::CertClass(X509 *new_cert) {
	LoadCert(new_cert);
}

CertClass::~CertClass() {
}

wxString CertClass::NiceName() {
	return Subject.CommonName() + ":" + Subject.DocID() + " (" + Issuer.CommonName() + ")";
}

wxString CertClass::NotBeforeString() {
	return not_before_str;
}

wxString CertClass::NotAfterString() {
	return not_after_str;
}

wxString CertClass::FingerPrintSHA256_HumanReadable() {
	return fp_sha_256_human;
}

wxString CertClass::FingerPrintSHA256_FileFriendly() {
	return fp_sha_256_fs;
}

bool CertClass::LoadPEMFile(const char path[]) {
	printf("Loading file: %s\n", path);
	return LoadCert(FILE2X509(path));
}

bool CertClass::LoadPEMString(const char data[]) {	
	return LoadCert(PEM2X509(data));
}

time_t asn_time2time_t(ASN1_TIME *asn_time) {
	int days, seconds;
	ASN1_TIME *ref;
	ref = ASN1_TIME_set(NULL, 0);
	ASN1_TIME_diff(&days, &seconds, ref, asn_time);
	return (long int) days*24*3600 + (long int) seconds;
}

wxString time_t2iso8601(time_t the_time) {
	char buf[999];
	struct tm* tm_info;
	tm_info = gmtime(&the_time);
	strftime(buf, 26, "%d/%m/%Y %H:%M:%S", tm_info);
	return wxString(buf);
}

bool CertClass::LoadCert(X509 *new_cert) {
	bool ok = true;
	if (new_cert == NULL) {
		return false;
	}

	cert = new_cert;

	ok &= Subject.FromCert(cert, ENTITY_SUBJECT);
	ok &= Issuer.FromCert(cert, ENTITY_ISSUER);

	// Get dates
	ASN1_TIME *asn_not_before, *asn_not_after;
	asn_not_before = X509_getm_notBefore(cert);
	asn_not_after = X509_getm_notAfter(cert);
	
	not_before = asn_time2time_t(asn_not_before);
	not_after = asn_time2time_t(asn_not_after);

	not_before_str = time_t2iso8601(not_before);
	not_after_str = time_t2iso8601(not_after);

	// Get fingerprint
	unsigned char buf[SHA256_RAW_LEN];
	unsigned int len;
	const EVP_MD *digest = EVP_sha256();
	int rc = X509_digest(cert, digest, buf, &len);
	if (rc == 0 || len != SHA256_RAW_LEN) {
		cout << "Failed to get certificate fingerprint. X509_digest return code: " << rc << " len = " << len << endl;
		return false;
	}
	// Hex encode it
	char buf_hex[3];
	fp_sha_256_human = "";
	for (size_t i=0; i < len; i++) {
		sprintf(buf_hex, "%02X", buf[i]);
		if (i != 0) {
			fp_sha_256_human.Append(":");
		}
		fp_sha_256_human.Append(buf_hex);
	}
	fp_sha_256_fs = "";
	for (size_t i=0; i < len; i++) {
		sprintf(buf_hex, "%02x", buf[i]);
		fp_sha_256_fs.Append(buf_hex);
	}

	return ok;
}

bool CertClass::SaveCert(wxString dir) {
	// Get path
	wxFileName path = dir;
	path.SetFullName(FingerPrintSHA256_FileFriendly() + ".cert.pem");
	wxLogDebug("Saving cert to %s", path.GetFullPath());

	// Open file
	FILE *file = fopen(path.GetFullPath().c_str(), "w");
	if (file == NULL) {
		wxLogDebug("Failed to open file for writing: %s", path.GetFullPath());
		return false;
	}

	// Actually save stuff
	int bytes = PEM_write_X509(file, cert);
	if (bytes <= 0) {
		wxLogDebug("Failed to write one or more bytes: %s", path.GetFullPath());
		return false;
	}

	// Finish
	fclose(file);
	return true;
}

X509* CertClass::_getX509() {
	return cert;
}