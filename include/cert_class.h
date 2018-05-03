#pragma once
#include "common.h"
#include <openssl/x509.h>
#include <openssl/pem.h>

// Sub = Subject, Iss = Issuer
struct CertSubIssInfo {
	wxString country, state, locality;
	wxString organization, organization_unit;
	wxString common_name, email;
	wxString doc_id;
	wxString one_line;
	unsigned long hash;
	wxString hash_str;
};

class CertClass {
protected:
	wxString name, email, doc_id, subject_hash, issuer_hash;
	wxString pem_data;
	X509 *cert;
public:
	CertClass();
	bool LoadPEMStr(const char buf[]);
	bool LoadPEMFile(const char path[]);
	wxString Name();
	wxString Email();
	wxString DocID();
	wxString SubjectHash();
	wxString IssuerHash();
	~CertClass();
};

bool read_x509_subiss_core(CertSubIssInfo &subiss, X509_NAME *xname);
bool read_x509_subject(CertSubIssInfo &subject, X509 *cert);
bool read_x509_issuer(CertSubIssInfo &issuer, X509 *cert);