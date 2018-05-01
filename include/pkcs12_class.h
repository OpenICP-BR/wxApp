#include "common.h"
#include <ctime>
#include <openssl/pkcs12.h>

struct CertSubIssInfo {
	wxString country, state, locality;
	wxString organization, organization_unit;
	wxString common_name, email;
	wxString doc_id;
	wxString one_line;
};

class PKCS12Class {
protected:
	PKCS12 *p12;
	STACK_OF(X509) *ca_stack = NULL;
	EVP_PKEY *key_pair;
	X509 *cert;
public:
	time_t not_before_t, not_after_t;
	wxString not_before_str, not_after_str;
	CertSubIssInfo subject, issuer;
	int LoadFromFile(wxString path);
	int Unlock(wxString pass);
	~PKCS12Class();
};