#include "certs_panel.h"
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/pkcs12.h>

bool CertsPanelClass::LoadCert(wxString cert_path) {
	FILE *fptr;
	const char *c_path;

	std::cout << cert_path << std::endl;
	c_path = cert_path.mb_str();
	fptr = fopen(c_path, "r");
	if (fptr == NULL) {
		wxMessageBox(wxT("Falha ao abrir o arquivo .p12"), wxT("Erro"), wxICON_ERROR|wxOK);
		printf("Failed to open file %s\n", c_path);
		return false;
	}
	new_p12 = d2i_PKCS12_fp(fptr, NULL);
	printf("new_p12 = %p\n", new_p12);
	fclose(fptr);
	if (new_p12 == NULL) {
		wxMessageBox(wxT("Falha ao decodificar o arquivo .p12"), wxT("Erro"), wxICON_ERROR|wxOK);
		printf("Failed to decode file %s\n", c_path);
		return false;
	}

	return true;
}

bool CertsPanelClass::UnlockCert(wxString pass) {
	const char *c_pass = pass.mb_str();
	int len = pass.Len();

	if (!PKCS12_verify_mac(new_p12, c_pass, len)) {
		wxMessageBox(wxT("Senha errada para o arquivo .p12"), wxT("Erro"), wxICON_ERROR|wxOK);
		return false;
	}
	if (!PKCS12_parse(new_p12, c_pass, &new_key_pair, &new_cert, &new_ca)) {
		wxMessageBox(wxT("Erro ao decodificar arquivo .p12 (usando senha)"), wxT("Erro"), wxICON_ERROR|wxOK);
		return false;
	}

	char buf[999];
	printf("Issuer: %s \n", X509_NAME_oneline(X509_get_issuer_name(new_cert), buf, 999));
	printf("Subject: %s \n", X509_NAME_oneline(X509_get_subject_name(new_cert), buf, 999));
	X509_NAME_get_text_by_NID(X509_get_subject_name(new_cert), NID_commonName, buf, 999);
	printf("Subject CN: %s \n", buf);


	return true;
}