#include <time.h>
#include "cert_class.h"

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
	ASN1_TIME *asn_not_before, *asn_not_after;
	asn_not_before = X509_get_notBefore(new_cert);
	asn_not_after = X509_get_notAfter(new_cert);
	
	not_before = asn_time2time_t(asn_not_before);
	not_after = asn_time2time_t(asn_not_after);

	not_before_str = time_t2iso8601(not_before);
	not_after_str = time_t2iso8601(not_after);

	return ok;
}