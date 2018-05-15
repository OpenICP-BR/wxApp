#include "CAStoreClass.h"
#include "EntityInfoClass.h"
#include "CAStoreClass-Data.h"
#include <wx/dir.h>

CAStoreClass CAStore;

CAStoreClass::CAStoreClass() {
	// Create X509_STORE_CTX
	store = X509_STORE_new();
	if (store == NULL) {
		wxLogDebug("Failed to create X509_STORE_CTX.");
		return;
	}

	// Add root certificates
	addCA(PEM2X509(icp_raiz_v1_pem));
	addCA(PEM2X509(icp_raiz_v2_pem));
	addCA(PEM2X509(icp_raiz_v5_pem));
	#ifdef USE_FAKE_ICP_ROOT
	addCA(PEM2X509(icp_fake_raiz_pem));
	#endif
}

bool CAStoreClass::addCA(X509 *cert) {
	if (cert == NULL) {
		return false;
	}
	if (X509_STORE_add_cert(store, cert) == 0) {
		return false;
	}

	X509_NAME *xname;
	char buf[999];

	xname = X509_get_subject_name(cert);
	X509_NAME_oneline(xname, buf, 999);
	wxLogDebug("Added CA: %s", buf);

	return true;
}

bool CAStoreClass::AddCA_PEM(const char data[]) {
	return AddCA(PEM2X509(data));
}

bool CAStoreClass::AddAllCAsFromDir(wxString dir_path) {
	int total_counter=0;
	int counter=-999;
	wxString filename;
	wxFileName dir_as_file;

	wxLogDebug("Loading all CAs from %s", dir_path);
	dir_as_file.Assign(dir_path);
	dir_as_file.MakeAbsolute();

	if (!dir_as_file.DirExists()) {
		return false;
	}

	wxDir dir(dir_as_file.GetFullPath());

	while (counter != 0) {
		counter = 0;

		wxLogDebug("New round of looking for certificates in %s", dir.GetName());
		bool cont = dir.GetFirst(&filename);
		while (cont) {
			wxString full_path = dir.GetNameWithSep()+filename;
			if (AddCA(FILE2X509(full_path.mb_str()))) {
				counter++;
				total_counter++;
			}
			cont = dir.GetNext(&filename);
		}
	}
	wxLogDebug("Finished adding %d CAs from: %s", total_counter, dir.GetName());
	return true;
}

bool CAStoreClass::Verify(X509 *cert) {
	int error_int, error_depth;
	wxString error_string;
	CertClass error_cert;
	return Verify(cert, error_int, error_string, error_depth, error_cert);
}

bool CAStoreClass::Verify(CertClass cert) {
	return Verify(cert._getX509());
}

bool CAStoreClass::Verify(CertClass cert, int &error_int, wxString &error_string, int &error_depth, CertClass &error_cert) {
	return Verify(cert._getX509(), error_int, error_string, error_depth, error_cert);
}

bool CAStoreClass::Verify(X509 *cert, int &error_int, wxString &error_string, int &error_depth, CertClass &error_cert) {
	if (cert == NULL) {
		return false;
	}
	X509_STORE_CTX *ctx = X509_STORE_CTX_new();
	if (ctx == NULL) {
		wxLogDebug("Failed to create X509_STORE_CTX");
		return false;
	}
	if (X509_STORE_CTX_init(ctx, store, cert, NULL) != 1) {
		wxLogDebug("Failed to initialize X509_STORE_CTX");
		X509_STORE_CTX_free(ctx);
		return false;
	}
	int rc = X509_verify_cert(ctx);
	X509_STORE_CTX_free(ctx);
	if (rc == 1) {
		return true;
	} else {
		error_int = X509_STORE_CTX_get_error(ctx);
		error_depth = X509_STORE_CTX_get_error_depth(ctx);
		error_cert = CertClass(X509_STORE_CTX_get_current_cert(ctx));
		switch (error_int) {
			case X509_V_OK:
				error_string = "Certificado válido. (X509_V_OK)";
				break;
			case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
				error_string = "Certificado do emissor não foi encontrado. (X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT)";
				break;
			case X509_V_ERR_UNABLE_TO_GET_CRL:
				error_string = "Falha ao obter a lista de certificados revogados. (X509_V_ERR_UNABLE_TO_GET_CRL)";
				break;
			case X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE:
				error_string = "Falha ao ler a assinatura do certificado. (X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE)";
				break;
			case X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE:
				error_string = "Falha ao ler a assinatura da lista de certificados revogados. (X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE)";
				break;
			case X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY:
				error_string = "Falha ao decodificar chave pública do emissor. (X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY)";
				break;
			case X509_V_ERR_CERT_SIGNATURE_FAILURE:
				error_string = "A assinatura do certificado é inválida. (X509_V_ERR_CERT_SIGNATURE_FAILURE)";
				break;
			case X509_V_ERR_CRL_SIGNATURE_FAILURE:
				error_string = "A assinatura da lista de certificados revogados é inválida. (X509_V_ERR_CRL_SIGNATURE_FAILURE)";
				break;
			case X509_V_ERR_CERT_NOT_YET_VALID:
				error_string = "O certificado ainda não é válido. Tente mais tarde. (X509_V_ERR_CERT_NOT_YET_VALID)";
				break;
			case X509_V_ERR_CERT_HAS_EXPIRED:
				error_string = "O certificado expirou. (X509_V_ERR_CERT_HAS_EXPIRED)";
				break;
			case X509_V_ERR_CRL_NOT_YET_VALID:
				error_string = "A lista de certificados revogados ainda não é válida. (X509_V_ERR_CRL_NOT_YET_VALID)";
				break;
			case X509_V_ERR_CRL_HAS_EXPIRED:
				error_string = "A lista de certificados revogados expirou. (X509_V_ERR_CRL_HAS_EXPIRED)";
				break;
			case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
				error_string = "Tempo de início de validade mal formatado. (X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD)";
				break;
			case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
				error_string = "Tempo de término de validade mal formatado. (X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD)";
				break;
			case X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD:
				error_string = "Tempo da última atualização da lista de certificados revogados mal formatado. (X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD)";
				break;
			case X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD:
				error_string = "Tempo da próxima atualização da lista de certificados revogados mal formatado. (X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD)";
				break;
			case X509_V_ERR_OUT_OF_MEM:
				error_string = "Memória insuficeinte para validar o certificado. (X509_V_ERR_OUT_OF_MEM)";
				break;
			case X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT:
				error_string = "Certificado auto assinado não confiável. (X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT)";
				break;
			case X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN:
				error_string = "Cadeia de certificados contém certificado auto assinado não confiável. (X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN)";
				break;
			case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
				error_string = "Emissor do certificado não encontrado. Atualize a lista de autoridades certificadoras. (X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY)";
				break;
			case X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE:
				error_string = "Falha ao verificar a assinatura do certificado. (X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE)";
				break;
			case X509_V_ERR_CERT_CHAIN_TOO_LONG:
				error_string = "Cadeia de certificados é longa demais. (X509_V_ERR_CERT_CHAIN_TOO_LONG)";
				break;
			case X509_V_ERR_CERT_REVOKED:
				error_string = "Certificado revogado. (X509_V_ERR_CERT_REVOKED)";
				break;
			case X509_V_ERR_INVALID_CA:
				error_string = "Autoridade certificadora é inválida. (X509_V_ERR_INVALID_CA)";
				break;
			case X509_V_ERR_PATH_LENGTH_EXCEEDED:
				error_string = "Caminho longo demais. (X509_V_ERR_PATH_LENGTH_EXCEEDED)";
				break;
			case X509_V_ERR_INVALID_PURPOSE:
				error_string = "Certificado não está autorizado para esse propósito. (X509_V_ERR_INVALID_PURPOSE)";
				break;
			case X509_V_ERR_CERT_UNTRUSTED:
				error_string = "Certificado não confiável para esse propósito. (X509_V_ERR_CERT_UNTRUSTED)";
				break;
			case X509_V_ERR_CERT_REJECTED:
				error_string = "Certificado rejeitado para esse propósito. (X509_V_ERR_CERT_REJECTED)";
				break;
			case X509_V_ERR_SUBJECT_ISSUER_MISMATCH:
				error_string = "Dados de sujeito e emissor do certificado não conferem. (X509_V_ERR_SUBJECT_ISSUER_MISMATCH)";
				break;
			case X509_V_ERR_AKID_SKID_MISMATCH:
				error_string = "Autoridade e chave de sujeito do certificado não conferem. (X509_V_ERR_AKID_SKID_MISMATCH)";
				break;
			case X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH:
				error_string = "Número de série do certificado do emissor não confere com o número de série local. (X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH)";
				break;
			case X509_V_ERR_KEYUSAGE_NO_CERTSIGN:
				error_string = "Certificado não permite a assinatura de outros certificados. (X509_V_ERR_KEYUSAGE_NO_CERTSIGN)";
				break;
			case X509_V_ERR_INVALID_EXTENSION:
				error_string = "Extensões de certificados inválidas ou inconsistentes. (X509_V_ERR_INVALID_EXTENSION)";
				break;
			case X509_V_ERR_INVALID_POLICY_EXTENSION:
				error_string = "Extensão de política ausente. (X509_V_ERR_INVALID_POLICY_EXTENSION)";
				break;
			case X509_V_ERR_NO_EXPLICIT_POLICY:
				error_string = "Política ausente. (X509_V_ERR_NO_EXPLICIT_POLICY)";
				break;
			case X509_V_ERR_DIFFERENT_CRL_SCOPE:
				error_string = "Certificado não está no escopo da lista de certificados revogado. (X509_V_ERR_DIFFERENT_CRL_SCOPE)";
				break;
			case X509_V_ERR_UNSUPPORTED_EXTENSION_FEATURE:
				error_string = "Extensão de certificado não suportada. (X509_V_ERR_UNSUPPORTED_EXTENSION_FEATURE)";
				break;
			case X509_V_ERR_PERMITTED_VIOLATION:
				error_string = "Violação de sub-árvore perimitida. (X509_V_ERR_PERMITTED_VIOLATION)";
				break;
			case X509_V_ERR_EXCLUDED_VIOLATION:
				error_string = "Violação de sub-árvore excluída. (X509_V_ERR_EXCLUDED_VIOLATION)";
				break;
			case X509_V_ERR_SUBTREE_MINMAX:
				error_string = "O certificado contém uma extensão de campo mínimo ou máximo. Isso não é suportado. (X509_V_ERR_SUBTREE_MINMAX)";
				break;
			case X509_V_ERR_UNSUPPORTED_CONSTRAINT_TYPE:
				error_string = "Restrição de nome não suportada. (X509_V_ERR_UNSUPPORTED_CONSTRAINT_TYPE)";
				break;
			case X509_V_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX:
				error_string = "Sintáxe de restrição de nome inválida. (X509_V_ERR_UNSUPPORTED_CONSTRAINT_SYNTAX)";
				break;
			case X509_V_ERR_CRL_PATH_VALIDATION_ERROR:
				error_string = "Falha ao verificar a lista de certificados revogados. (X509_V_ERR_CRL_PATH_VALIDATION_ERROR)";
				break;
			case X509_V_ERR_APPLICATION_VERIFICATION:
				error_string = "Falha de verificação específica de aplicação. (X509_V_ERR_APPLICATION_VERIFICATION)";
				break;
			default:
				error_string = "Erro desconhecido :(";
				break;
		}
		return false;
	}
}

bool CAStoreClass::AddCA(X509 *cert) {
	if (Verify(cert)) {
		return addCA(cert);
	} else {
		EntityInfoClass sub;
		sub.FromCert(cert, ENTITY_SUBJECT);
		wxLogDebug("Invalid CA: %s", sub.OneLine());
		return false;
	}
}

CAStoreClass::~CAStoreClass() {
	X509_STORE_free(store);
}