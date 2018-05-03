#include "cert_class.h"

CertClass::CertClass() {
}

CertClass::~CertClass() {
}

bool read_x509_subiss_core(CertSubIssInfo &subiss, X509_NAME *xname) {
	char buf[999];
	X509_NAME_oneline(xname, buf, 999);
	subiss.one_line = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_countryName, buf, 999);
	subiss.country = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_stateOrProvinceName, buf, 999);
	subiss.state = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_localityName, buf, 999);
	subiss.locality = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_organizationName, buf, 999);
	subiss.organization = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_organizationalUnitName, buf, 999);
	subiss.organization_unit = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_commonName, buf, 999);
	subiss.common_name = wxString(buf);
	X509_NAME_get_text_by_NID(xname, NID_pkcs9_emailAddress, buf, 999);
	subiss.email = wxString(buf);

	return true;
}

bool read_x509_subject(CertSubIssInfo &subject, X509 *cert) {
	char buf[999];
	read_x509_subiss_core(subject, X509_get_subject_name(cert));
	subject.hash = X509_subject_name_hash(cert);
	sprintf(buf, "%08lx", subject.hash);
	subject.hash_str = wxString(buf);

	int pos = subject.common_name.Find(":");
	if (pos != wxNOT_FOUND) {
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
	} else {
		subject.doc_id = wxT("---não consta---");
	}
	return true;
}

bool read_x509_issuer(CertSubIssInfo &issuer, X509 *cert) {
	char buf[999];
	read_x509_subiss_core(issuer, X509_get_issuer_name(cert));
	issuer.hash = X509_issuer_name_hash(cert);
	sprintf(buf, "%08lx", issuer.hash);
	issuer.hash_str = wxString(buf);
	return true;
}

bool CertClass::LoadPEMFile(const char path[]) {
	printf("Loading file: %s\n", path);
	FILE *fp;
	fp = fopen(path, "r");
	cert = PEM_read_X509(fp, NULL, NULL, NULL);
	if (cert == NULL) {
		printf("Failed to load certificate: %s\n", path);
		return false;
	}
	fclose(fp);

	return true;
}

wxString CertClass::Name() {
	return name;
}

wxString CertClass::Email() {
	return email;
}

wxString CertClass::DocID() {
	return doc_id;
}

wxString CertClass::SubjectHash() {
	return subject_hash;
}

wxString CertClass::IssuerHash() {
	return issuer_hash;
}
