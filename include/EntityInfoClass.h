#pragma once
#include <openssl/x509.h>
#include "Common.h"

enum ENTITY_ENUM {
	ENTITY_SUBJECT = 1,
	ENTITY_ISSUER = 2
};

class EntityInfoClass {
protected:
	wxString country, state, locality;
	wxString organization, organization_unit;
	wxString common_name, email;
	wxString doc_id;
	wxString one_line;
	x509_hash hash;
	wxString hash_string;
public:
	EntityInfoClass();
	wxString Country();
	wxString State();
	wxString Locality();
	wxString Organization();
	wxString OrganizationUnit();
	wxString CommonName();
	wxString Email();
	wxString DocID();
	wxString OneLine();
	wxString HashString();
	x509_hash Hash();
	bool FromCert(X509 *cert, ENTITY_ENUM entity_type);
	// bool FromCert(X509 **cert, ENTITY_ENUM entity_type);
	~EntityInfoClass();
};