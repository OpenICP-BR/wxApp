#include "cert_class.h"

CertClass::CertClass() {
}

CertClass::~CertClass() {
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

	return parseCert();
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
	
	return parseCert();
}

bool CertClass::parseCert() {
	return false;
}