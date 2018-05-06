#include "pkcs12_class.h"
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/x509.h>
#include <openssl/pkcs12.h>

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

int PKCS12Class::Unlock(wxString pass) {
	const char *c_pass = pass.mb_str();
	int len = pass.Len();
	BIO *bmem = NULL;
	BUF_MEM *bptr;

	if (p12 == NULL) {
		cout << "PKCS12Class::Unlock: .p12 file was not loaded" << endl;
		return 1; // Wrong password
	}
	if (!PKCS12_verify_mac(p12, c_pass, len)) {
		cout << "PKCS12Class::Unlock: Wrong password" << endl;
		return 2; // Wrong password
	}
	if (!PKCS12_parse(p12, c_pass, &key_pair, &cert, &ca_stack)) {
		cout << "PKCS12Class::Unlock: Failed to parse" << endl;
		return 3; // Failed to parse
	}

	bmem = BIO_new(BIO_s_mem());
	if (bmem == NULL) {
		cout << "PKCS12Class::Unlock - Failed to allocate memory" << endl;
        return 4; // Failed to allocate memory
    }
    cout << "PKCS12Class::Unlock: allocated bmem" << endl;

	// Get dates
	ASN1_TIME *not_before, *not_after;
	not_before = X509_get_notBefore(cert);
	not_after = X509_get_notAfter(cert);

	ASN1_TIME_print(bmem, not_before);
	BIO_get_mem_ptr(bmem, &bptr);
	not_before_str = wxString(bptr->data, bptr->length);

	ASN1_TIME_print(bmem, not_after);
	BIO_get_mem_ptr(bmem, &bptr);
	not_after_str = wxString(bptr->data, bptr->length);
	cout << "PKCS12Class::Unlock: read dates" << endl;

	// Read subject and issuer
	Subject.FromCert(cert, ENTITY_SUBJECT);
	Issuer.FromCert(cert, ENTITY_ISSUER);

	BIO_free(bmem);
	return OK;
}

bool PKCS12Class::IsValid () {
	return false;
}

PKCS12Class::~PKCS12Class () {
}