#pragma once
#include <openssl/x509.h>
#include "common.h"

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
	unsigned long hash;
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
	wxString Oneline();
	wxString HashString();
	unsigned long Hash();
	bool FromCert(X509 *cert, ENTITY_ENUM entity_type);
	// bool FromCert(X509 **cert, ENTITY_ENUM entity_type);
	~EntityInfoClass();
};