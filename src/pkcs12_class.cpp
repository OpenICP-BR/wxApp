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
	int len = pass.Len(), pos;
	char buf[999];
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

	// Read subject
	X509_NAME *xname;
	xname = X509_get_subject_name(cert);
	X509_NAME_oneline(xname, buf, 999);
	subject.one_line = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_countryName, buf, 999);
	subject.country = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_stateOrProvinceName, buf, 999);
	subject.state = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_localityName, buf, 999);
	subject.locality = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_organizationName, buf, 999);
	subject.organization = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_organizationalUnitName, buf, 999);
	subject.organization_unit = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_commonName, buf, 999);
	subject.common_name = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_pkcs9_emailAddress, buf, 999);
	subject.email = wxString(buf);
	cout << "PKCS12Class::Unlock: read subject" << endl;
	
	// Read issuer
	xname = X509_get_issuer_name(cert);
	X509_NAME_oneline(xname, buf, 999);
	issuer.one_line = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_countryName, buf, 999);
	issuer.country = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_stateOrProvinceName, buf, 999);
	issuer.state = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_localityName, buf, 999);
	issuer.locality = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_organizationName, buf, 999);
	issuer.organization = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_organizationalUnitName, buf, 999);
	issuer.organization_unit = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_commonName, buf, 999);
	issuer.common_name = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_pkcs9_emailAddress, buf, 999);
	issuer.email = wxString(buf);
	cout << "PKCS12Class::Unlock: read issuer" << endl;

	pos = subject.common_name.Find(":");
	subject.common_name = subject.common_name.BeforeLast(':', &subject.doc_id);
	if (subject.doc_id.Len() == 11) {
		// Fix CPF
		wxString fmt, id = subject.doc_id;
		fmt = id.SubString(0, 2) + '.' + id.SubString(3, 5) + '.' + id.SubString(6, 8) + '-' + id.SubString(9, 10);
		subject.doc_id = fmt;
	} else if (subject.doc_id.Len() == 14) {
		// Fix CNPJ
		wxString fmt, id = subject.doc_id;
		fmt = id.SubString(0, 1) + '.' + id.SubString(2, 4) + '.' + id.SubString(5, 7) + '/' + id.SubString(8, 11) + '-' + id.SubString(12, 13);
		subject.doc_id = fmt;
	}

	BIO_free(bmem);
	return OK;
}

bool PKCS12Class::IsValid () {
	return false;
}

PKCS12Class::~PKCS12Class () {
}