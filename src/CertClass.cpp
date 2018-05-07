#include <time.h>
#include "CertClass.h"

CertClass::CertClass() {
}

CertClass::~CertClass() {
}

wxString CertClass::NotBeforeString() {
	return not_before_str;
}

wxString CertClass::NotAfterString() {
	return not_after_str;
}

wxString CertClass::FingerPrintSHA256() {
	return fp_sha_256;
}

bool CertClass::LoadPEMFile(const char path[]) {
	printf("Loading file: %s\n", path);
	FILE *fp;
	fp = fopen(path, "r");
	if (fp == NULL) {
		printf("Certificate not found: %s\n", path);
		return false;
	}
	cert = PEM_read_X509(fp, NULL, NULL, NULL);
	fclose(fp);
	if (cert == NULL) {
		printf("Failed to load certificate: %s\n", path);
		return false;
	}

	return LoadCert(cert);
}

bool CertClass::LoadPEMString(const char data[]) {
	BIO *bmem;
	bmem = BIO_new_mem_buf(data, -1);
	cert = PEM_read_bio_X509(bmem, NULL, NULL, NULL);
	if (cert == NULL) {
		printf("Failed to load certificate from PEM: %s\n", data);
		BIO_free(bmem);
		return false;
	}
	BIO_free(bmem);
	
	return LoadCert(cert);
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
	strftime(buf, 26, "%Y-%m-%d %H:%M:%S+00:00", tm_info);
	return wxString(buf);
}

bool CertClass::LoadCert(X509 *new_cert) {
	bool ok = true;

	ok &= Subject.FromCert(new_cert, ENTITY_SUBJECT);
	ok &= Issuer.FromCert(new_cert, ENTITY_ISSUER);

	// Get dates
	cout << "hi5" << endl;
	ASN1_TIME *asn_not_before, *asn_not_after;
	cout << "hi6" << endl;
	asn_not_before = X509_getm_notBefore(new_cert);
	cout << "hi7" << endl;
	asn_not_after = X509_getm_notAfter(new_cert);
	cout << "hi8" << endl;
	
	not_before = asn_time2time_t(asn_not_before);
	cout << "hi9" << endl;
	not_after = asn_time2time_t(asn_not_after);
	cout << "hi10" << endl;

	not_before_str = time_t2iso8601(not_before);
	cout << "hi11" << endl;
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
	fp_sha_256 = "";
	for (size_t i=0; i < len; i++) {
		sprintf(buf_hex, "%02X", buf[i]);
		if (i != 0) {
			fp_sha_256.Append(":");
		}
		fp_sha_256.Append(buf_hex);
	}
	cout << fp_sha_256 << endl;


	return ok;
}