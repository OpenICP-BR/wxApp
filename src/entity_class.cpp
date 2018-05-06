#include "entity_class.h"

EntityInfoClass::EntityInfoClass() {
}

EntityInfoClass::~EntityInfoClass() {
}

wxString EntityInfoClass::Country () {
	return country;
}

wxString EntityInfoClass::State () {
	return state;
}

wxString EntityInfoClass::Locality () {
	return locality;
}

wxString EntityInfoClass::Organization () {
	return organization;
}

wxString EntityInfoClass::OrganizationUnit () {
	return organization_unit;
}

wxString EntityInfoClass::CommonName () {
	return common_name;
}

wxString EntityInfoClass::Email () {
	return email;
}

wxString EntityInfoClass::DocID () {
	return doc_id;
}

wxString EntityInfoClass::OneLine () {
	return one_line;
}

wxString EntityInfoClass::HashString () {
	return hash_string;
}

unsigned long EntityInfoClass::Hash () {
	return hash;
}

bool EntityInfoClass::FromCert (X509 *cert, ENTITY_ENUM entity_type) {
	char buf[999];
	X509_NAME *xname;

	// Check what to read
	if (entity_type == ENTITY_SUBJECT) {
		xname = X509_get_subject_name(cert);
		hash = X509_subject_name_hash(cert);
	} else if (entity_type == ENTITY_ISSUER) {
		xname = X509_get_issuer_name(cert);
		hash = X509_issuer_name_hash(cert);
	} else {
		return false;
	}

	// Read and convert
	sprintf(buf, "%08lx", hash);
	hash_string = wxString::FromUTF8(buf);

	buf[0] = '\0';
	X509_NAME_oneline(xname, buf, 999);
	one_line = wxString::FromUTF8(buf);

	buf[0] = '\0';
	X509_NAME_get_text_by_NID(xname, NID_countryName, buf, 999);
	country = wxString::FromUTF8(buf);

	buf[0] = '\0';
	X509_NAME_get_text_by_NID(xname, NID_stateOrProvinceName, buf, 999);
	state = wxString::FromUTF8(buf);

	buf[0] = '\0';
	X509_NAME_get_text_by_NID(xname, NID_localityName, buf, 999);
	locality = wxString::FromUTF8(buf);

	buf[0] = '\0';
	X509_NAME_get_text_by_NID(xname, NID_organizationName, buf, 999);
	organization = wxString::FromUTF8(buf);

	buf[0] = '\0';
	X509_NAME_get_text_by_NID(xname, NID_organizationalUnitName, buf, 999);
	organization_unit = wxString::FromUTF8(buf);

	buf[0] = '\0';
	X509_NAME_get_text_by_NID(xname, NID_commonName, buf, 999);
	common_name = wxString::FromUTF8(buf);

	buf[0] = '\0';
	X509_NAME_get_text_by_NID(xname, NID_pkcs9_emailAddress, buf, 999);
	email = wxString::FromUTF8(buf);


	// Add doc id
	int pos = common_name.Find(":");
	if (pos != wxNOT_FOUND) {
		common_name = common_name.BeforeLast(':', &doc_id);
		if (doc_id.Len() == 11) {
			// Fix CPF
			wxString fmt, id = doc_id;
			fmt = id.SubString(0, 2) + '.' + id.SubString(3, 5) + '.' + id.SubString(6, 8) + '-' + id.SubString(9, 10);
			doc_id = fmt;
		} else if (doc_id.Len() == 14) {
			// Fix CNPJ
			wxString fmt, id = doc_id;
			fmt = id.SubString(0, 1) + '.' + id.SubString(2, 4) + '.' + id.SubString(5, 7) + '/' + id.SubString(8, 11) + '-' + id.SubString(12, 13);
			doc_id = fmt;
		}
	} else {
		doc_id = wxString::FromUTF8("---n\xC3\xA3o consta---");
	}

	return true;
}