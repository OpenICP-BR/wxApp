#include "certs_panel.h"
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/pkcs12.h>

bool CertsPanelClass::LoadCert(wxString cert_path) {
	PKCS12 *p12;
	X509 *cert;
	STACK_OF(X509) *ca = NULL;
	FILE *fptr;
	const char *c_path;

	std::cout << cert_path << std::endl;
	c_path = cert_path.mb_str();
	fptr = fopen(c_path, "r");
	if (fptr == NULL) {
		printf("Failed to open file %s\n", c_path);
		return false;
	}
	p12 = d2i_PKCS12_fp(fptr, NULL);
	printf("p12 = %p\n", p12);
	fclose(fptr);
	if (p12 == NULL) {
		printf("Failed to decode file %s\n", c_path);
		return false;
	}

	return true;
}