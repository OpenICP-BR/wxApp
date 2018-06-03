#include "PKCS12Class.h"
#include "CAStoreClass.h"
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/cms.h>
#include <openssl/x509.h>
#include <openssl/pkcs12.h>

EntityInfoClass PKCS12Class::Subject() {
	return cert.Subject;
}

EntityInfoClass PKCS12Class::Issuer() {
	return cert.Issuer;
}

CertClass PKCS12Class::Cert() {
	return cert;
}

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

void PKCS12Class::SetPassword(wxString pass) {
	password = pass;
}

int PKCS12Class::Unlock(wxString pass) {
	const char *c_pass = pass.mb_str();
	int len = pass.Len();
	X509 *x509_cert;

	if (p12 == NULL) {
		cout << "PKCS12Class::Unlock: .p12 file was not loaded" << endl;
		return PKCS12_UNLOCK_ERR_FILE_NOT_LOADED;
	}
	if (!PKCS12_verify_mac(p12, c_pass, len)) {
		cout << "PKCS12Class::Unlock: Wrong password" << endl;
		return PKCS12_UNLOCK_ERR_WRONG_PASSWORD;
	}
	if (!PKCS12_parse(p12, c_pass, &key_pair, &x509_cert, &ca_stack)) {
		cout << "PKCS12Class::Unlock: Failed to parse" << endl;
		return PKCS12_UNLOCK_ERR_FAILED_TO_PARSE;
	}

	cert.LoadCert(x509_cert);
	SetPassword(pass);
	return OK;
}

bool PKCS12Class::SaveKeylessCert(wxString dir) {
	return cert.SaveCert(dir);
}

bool PKCS12Class::SaveEncryptedP12(wxString dir) {
	// Get path
	wxFileName path = dir;
	path.SetFullName(cert.FingerPrintSHA256_FileFriendly() + ".p12");
	wxLogDebug("Saving pkcs12 to %s", path.GetFullPath());

	// Open file
	FILE *file = fopen(path.GetFullPath().c_str(), "w");
	if (file == NULL) {
		wxLogDebug("Failed to open file for writing: %s", path.GetFullPath());
		return false;
	}

	// Actually save stuff
	int bytes = i2d_PKCS12_fp(file, p12);
	if (bytes <= 0) {
		wxLogDebug("Failed to write one or more bytes: %s", path.GetFullPath());
		return false;
	}

	// Finish
	fclose(file);
	return true;
}

wxString PKCS12Class::NotBeforeString() {
	return cert.NotBeforeString();
}

wxString PKCS12Class::NotAfterString() {
	return cert.NotAfterString();
}

wxString PKCS12Class::FingerPrintSHA256_FileFriendly() {
	return cert.FingerPrintSHA256_FileFriendly();
}

wxString PKCS12Class::FingerPrintSHA256_HumanReadable() {
	return cert.FingerPrintSHA256_HumanReadable();
}

int PKCS12Class::SignFile(wxString path) {
	wxString nothing;
	return SignFile(path, nothing);
}

int PKCS12Class::SignFile(wxString input, wxString &err_msg) {
	wxString verify_err_msg, output;
	BIO *bio_in=NULL, *bio_out=NULL;
	CMS_ContentInfo *cms=NULL;
	bool first_signature=false;
	unsigned int cms_flags = CMS_PARTIAL | CMS_DETACHED;

	cout << "Attempting to sign file " << input << endl;
	output = input + ".p7s";

	// Verify certificate and get full chain
	STACK_OF(X509) *full_chain = NULL;
	if (!CAStore.Verify(cert, verify_err_msg, full_chain)) {
		err_msg = wxT("Certificado inválido. Motivo: ");
		err_msg += verify_err_msg;
		RETURN_AND_PRINT(PKCS12_SIGN_ERR_INVALID_CERT);
	}

	// Does output exist?
	first_signature = (access(output.mb_str(), F_OK) == -1);		

	// Generate CMS
	if (first_signature) {
		// Create new CMS structure
		cms = CMS_ContentInfo_new();
		if (cms == NULL || !CMS_SignedData_init(cms)) {
			print_openssl_err();
			err_msg = wxT("Erro desconhecido ao preparar assiantura");
			RETURN_AND_PRINT(ERR_UNKOWN);
		}
		// Configure CMS
		CMS_set_detached(cms, true);
	} else {
		// Open input (previous signature)
		bio_in = BIO_new_file(output.mb_str(), "r");
		if (bio_in == NULL) {
			cout << "File not writable: " << output << endl;
			print_openssl_err();
			err_msg = wxT("Impossível abrir arquivo de assinatura");
			RETURN_AND_PRINT(PKCS12_SIGN_ERR_INPUT_NOT_ALLOWED);
		}
		// Parse previous signature
		if (!d2i_CMS_bio(bio_in, &cms)) {
			cout << "File not parsable: " << output << endl;
			print_openssl_err();
			err_msg = wxT("Impossível entender arquivo de assinatura");
			RETURN_AND_PRINT(PKCS12_SIGN_ERR_FAILED_TO_LOAD_SIGNATURE);
		}
		CMS_SignedData_init(cms);
		BIO_free(bio_in);
	}

	// Open input (content file)
	bio_in = BIO_new_file(input.mb_str(), "r");
	if (bio_in == NULL) {
		cout << "File not found: " << input << endl;
		err_msg = wxT("Arquivo não encontrado");
		RETURN_AND_PRINT(PKCS12_SIGN_ERR_INPUT_NOT_ALLOWED);
	}

	// Sign!
	CMS_SignerInfo *sig;
	sig = CMS_add1_signer(cms, cert._getX509(), key_pair, EVP_sha512(), cms_flags);
	if (sig == NULL) {
		err_msg = wxT("Falha ao adicionar assinatura (1)");
		print_openssl_err();
		RETURN_AND_PRINT(PKCS12_SIGN_ERR_FAILED_TO_APPEND_SIGNATURE);
	}
	if (!CMS_SignerInfo_sign(sig)) {
		err_msg = wxT("Falha ao adicionar assinatura (2)");
		print_openssl_err();
		RETURN_AND_PRINT(PKCS12_SIGN_ERR_FAILED_TO_APPEND_SIGNATURE);
	}

	// Add certificates
	for (int i = 0; i < sk_X509_num(full_chain); i++) {
		X509 *x = sk_X509_value(full_chain, i);
		if (!CMS_add1_cert(cms, x)) {
			print_openssl_err();
			cout << "Got error when appending certificate. Level: " << i << endl;
			err_msg = wxT("Erro desconhecido");
			RETURN_AND_PRINT(ERR_UNKOWN);
		}
	}

	// Open output
	bio_out = BIO_new_file(output.mb_str(), "w");
	if (bio_out == NULL) {
		cout << "File not writable: " << output << endl;
		print_openssl_err();
		err_msg = wxT("Impossível criar arquivo de assinatura");
		RETURN_AND_PRINT(PKCS12_SIGN_ERR_OUTPUT_NOT_ALLOWED);
	}

	// Finalize
	// if (!CMS_dataFinal(cms, bio_in)) {
	// 	err_msg = wxT("Falha ao finalizar assinatura");
	// 	print_openssl_err();
	// 	RETURN_AND_PRINT(PKCS12_SIGN_ERR_FAILED_TO_APPEND_SIGNATURE);
	// }
	if (!CMS_final(cms, bio_in, NULL, cms_flags)) {
		err_msg = wxT("Falha ao finalizar assinatura");
		print_openssl_err();
		RETURN_AND_PRINT(PKCS12_SIGN_ERR_FAILED_TO_APPEND_SIGNATURE);
	}

	// Write output
	int err = i2d_CMS_bio(bio_out, cms);
	if (err == 0) {
		print_openssl_err();
		cout << "Got error when writing CMS: " << err << endl;
		err_msg = wxT("Erro desconhecido ao escrever assiantura");
		RETURN_AND_PRINT(ERR_UNKOWN);
	}
	if (BIO_flush(bio_out) != 1) {
		print_openssl_err();
		cout << "Got error when flushing CMS" << endl;
		err_msg = wxT("Erro desconhecido ao escrever assiantura");
		RETURN_AND_PRINT(ERR_UNKOWN);
	}
	BIO_free(bio_out);
	CMS_ContentInfo_free(cms);

	cout << "Signature saved on " << output << endl;
	err_msg = wxT("OK");
	RETURN_AND_PRINT(OK);
}

PKCS12Class::~PKCS12Class () {
}